# SAV Open Playground

## Overview

SAV Open Playground is a comprehensive project designed to simulate and test Source Address Validation (SAV) mechanisms in a controlled environment. The project includes multiple components such as SAV agents, control planes, data planes, and various testing tools to ensure the effectiveness and efficiency of SAV implementations.

## Project Structure

The project is organized into several directories, each serving a specific purpose:

- `sav_agent/`: Contains the source code for the SAV agent module, responsible for interacting with SAV apps and managing SAV rules.
- `sav_control/`: Includes scripts and configurations for Controlling an experiment.
- `sav_router/`: Contains the router implementation based on [BIRD Daemon Project](https://bird.network.cz/) and related configurations, including protocol definitions and filter instructions.

## Key Components

### SAV Agent

The SAV agent module is responsible for interacting with SAV apps, generating SAV rules, and managing event buffers. It provides interfaces for SAV apps to fetch required information and send messages to other agents.

### Control Plane

The control plane manages the overall experiment setup, configuration generation, and distribution. It includes scripts for monitoring resource usage, managing containers, and running experiments.

### Data Plane

The data plane handles the application of SAV rules using tools like iptables and traffic control. It includes classes for managing IP tables and access control lists.

### Router

The router implementation includes protocol definitions, filter instructions, and various utilities for managing routing protocols. It supports multiple protocols such as BGP, OSPF, and RIP. The implementation is based on the [BIRD Daemon Project](https://bird.network.cz/).

## Getting Started

### Prerequisites

- Python 3.x
- Docker
- iptables
- dstat

### Usage
1. define your own topo for the experiment and place them into `sav_control/basic_configs`
2. run the experiment using `python3 {SAV_PLAYGROUND}/sav_control/sav_control_master.py -e {your_config_file without .json}`

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
