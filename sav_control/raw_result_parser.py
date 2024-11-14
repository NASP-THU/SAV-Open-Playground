import os
import json

def procedure_1(f):
    out_name = f.replace("raw_result.txt", "parsed_result.csv")
    if os.path.exists(out_name):
        return
    
    ret = {}
    data = open(f, "r").read()
    data = data.split("')")
    while "" in data:
        data.remove("")
    for i in data:

        if len(i) < 1000:
            continue
        i = i.strip()
        data = i
        break

    while not data.startswith("{"):
        data = data[1:]
    while not data.endswith("}"):
        data = data[:-1]
    data = json.loads(data)
    del data["container_metric"]
    host_metric = data["host_metric"]
    host_data = host_metric["data"].split("\n")
    # input(host_metric["data"])
    dsk = host_data[0].split("dsk")
    dsk = [i[1:i.index('-')] for i in dsk if i.startswith("/")]
    headings = host_data[1].split("|")
    dsk_heading_index = 2
    net_heading_index = 3
    dsk_heading = headings[dsk_heading_index].split()
    for index in range(len(dsk)):
        dsk_heading[2*index] = dsk[index] + "_"+dsk_heading[2*index]
        dsk_heading[(2*index)+1] = dsk[index] + "_"+dsk_heading[(2*index)+1]
    dsk_heading = " ".join(dsk_heading)
    headings[dsk_heading_index] = dsk_heading
    net = host_data[0].split("net")
    net = [i[1:i.index('-')].strip() for i in net if i.startswith("/")]
    net_heading = headings[net_heading_index].split()
    for index in range(len(net)):
        net_heading[2*index] = net[index] + "_"+net_heading[2*index]
        net_heading[(2*index)+1] = net[index] + "_"+net_heading[(2*index)+1]
    net_heading = " ".join(net_heading)
    headings = "|".join(headings)
    while "|" in headings:
        headings = headings.replace("|", " ")
    headings = headings.split()

    host_data = host_data[2:]
    resources = []
    mem0 = None
    while "" in host_data:
        host_data.remove("")

    for l in host_data:
        while "|" in l:
            l = l.replace("|", " ")
        while ":" in l:
            l = l.replace(":", " ")
        l = l.split()
        l = dict(zip(headings, l))
        memory_use = unify_unit(l["used"])
        if mem0 is None:
            mem0 = memory_use
        cpu_usage = (100 - float(l["idl"]))/100
        disk_rw_sum = 0
        net_rw_sum = 0
        # input(l)
        for k in l:
            if k.endswith("_read"):
                disk_rw_sum += unify_unit(l[k], "M")
            elif k.endswith("writ:"):
                disk_rw_sum += unify_unit(l[k], "M")
            elif k.endswith("send"):
                net_rw_sum += unify_unit(l[k], "M")
            elif k.endswith("recv"):
                net_rw_sum += unify_unit(l[k], "M")
        if float(l["stl"]) > 0:
            input(l)
        row = [cpu_usage, max(memory_use-mem0, 0), disk_rw_sum, net_rw_sum]
        resources.append(row)
    ret["container_number"] = data["container_number"]
    ret["link_number"]=data["link_number"]
    ret["container_start_time"]=data["container_start_time"]
    ret["link_start_time"]=data["link_start_time"]
    ret["resources"] = resources
    ret["cpu_mem_start_dt"] = data["host_metric"]["start_dt"]
    ret["cpu_mem_stop_dt"] = data["host_metric"]["stop_dt"]
    ret["first_stable"] = data["initial_fib_stable_data"]
    ret["second_stable"] = data["fib_stable_data"]
    ret["final_fib"] = data["fib_table_data"]
    out_name = f.replace("raw_result.txt", "parsed_result.json")
    max_value = (max(ret["resources"], key=lambda x: x[0])[0],  # CPU
                 max(ret["resources"], key=lambda x: x[1])[1],  # MEM
                 max(ret["resources"], key=lambda x: x[2])[2],  # disk
                 max(ret["resources"], key=lambda x: x[3])[3],  # net
                 max(ret["first_stable"].values()),  # first_stable
                 max(ret["second_stable"].values())  # second_stable
                 )
    max_values[f] = max_value
    json.dump(ret, open(out_name, "w"), indent=2)
    out_name = f.replace("raw_result.txt", "parsed_result.csv")
    f = open(out_name, "w")
    f.write(
        "cpu_usage,memory_usage,disk_rw_sum,net_rw_sum,device")
    f.write(",first_stable,second_stable,container_num,container_time,link_num,link_time\n")
    devs = ret["first_stable"].keys()
    devs = list(map(lambda x: int(x[1:]), devs))
    devs = sorted(devs)
    temp_lines = []
    for i in devs:
        k = f"r{i}"
        line = f"{k},{ret['first_stable'][k]},"
        if k in ret["second_stable"]:
            line +=str(ret['second_stable'][k])
        temp_lines.append(line)
    temp_lines[0] +=f",{ret['container_number']}"
    temp_lines[0] +=f",{ret['container_start_time']}"
    temp_lines[0] +=f",{ret['link_number']}"
    temp_lines[0] +=f",{ret['link_start_time']}"
    if len(temp_lines)>len(ret["resources"]):
        input("length error")
    for i in ret["resources"]:
        if i[1] > 0.05:
            if len(temp_lines)>0:
                merege_line = f"{i[0]},{i[1]},{i[2]},{i[3]},{temp_lines[0]}\n"
                f.write(merege_line)
                temp_lines = temp_lines[1:]
            else:
                f.write(f"{i[0]},{i[1]},{i[2]},{i[3]}\n")
    f.close()
def unify_unit(input_str, out='G'):
    # we use B here
    if input_str.endswith('M'):
        value = float(input_str[:-1])*1024*1024
    elif input_str.endswith('G'):
        value = float(input_str[:-1])*1024*1024*1024
    elif input_str.endswith('b'):
        value = float(input_str[:-1])/8
    elif input_str.endswith('k'):
        value = float(input_str[:-1])*1024
    else:
        if input_str.isdigit():
            value = int(input_str)*1024
        else:
            input(input_str)

    if out == 'G':
        return float(value/(1024*1024*1024))
    elif out == 'M':
        return float(value/(1024*1024))
    else:
        input(out)


fils = os.listdir()
files = [i for i in fils if "raw_result.txt" in i]
max_values = {}
for f in files:
    print(f"{f} done")
