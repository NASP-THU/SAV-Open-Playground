# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: agent_msg.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0f\x61gent_msg.proto\x12\tagnet_msg\"/\n\x08\x41gentMsg\x12\x11\n\tsender_id\x18\x01 \x01(\t\x12\x10\n\x08json_str\x18\x02 \x01(\t2?\n\tAgentLink\x12\x32\n\x06Simple\x12\x13.agnet_msg.AgentMsg\x1a\x13.agnet_msg.AgentMsgb\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'agent_msg_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _AGENTMSG._serialized_start=30
  _AGENTMSG._serialized_end=77
  _AGENTLINK._serialized_start=79
  _AGENTLINK._serialized_end=142
# @@protoc_insertion_point(module_scope)
