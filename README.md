# SMART HOME MANAGEMENT PLATFORM

## Motivation
New technologies, mobile devices, the Internet of Things (IoT), and big data are rapidly creating a world with levels of connectivity and access to data never seen before. The intelligence derived from such data can bring unprecedented visibility and optimization to building operations.
The ability to collect data from environmental sensors such as HVAC lighting, fire safety and other sources combined with the ability to extract, aggregate, analyze, and make decisions based on that data - makes a building a "smart building".

## Project Description
SmartBuilding is a next generation platform written in C++ for managing IoT enhanced smart building. The platform serves as the controller and integration hub for modules, devices, controllers and sensors that will enable efficient and comfortable operation of the building.

The system includes the following components:

* A central hub, which is a server application serving as a host for software agents (below). It provides an efficient mechanism to receive events from sensors and dispatch these events to relevant controllers.
* Software agents, mediating communication with the external hardware devices. These devices can act either as sensors - monitoring and measuring a physical phenomena - or as controllers - executing an operation, usually affecting the environment.

Sensor agents generate events which will be routed to the controller agents interested in acting upon them. Generated events contain at least: the event type, the event location, a timestamp and a data payload. All events can be saved to a log file or log database. See diagrams/ for a detailed overview of the system's flow.

## Setup Locally
To get started, make sure you have Docker Engine and Docker Compose installed on your system. Instructions on how to install Docker Engine on your system can be found [here](https://docs.docker.com/engine/install/) and on how to install Docker Compose [here](https://docs.docker.com/compose/install/).

Next, clone this repository, navigate in your terminal to the docker directory, and spin up the app by running `sudo docker compose up -d`. 

## Events Tracking
In case all events are saved in a file, you can monitor them by running `sudo cat /var/lib/docker/volumes/docker_mySmartHome/_data/log.txt`.

In case all events are saved in a database... TBD.

## Adding Agents
An agent is the software entity loaded by the server to represent an actual device. Each agent is implemented as a dynamic object (.SO) and will implement and expose the required interfaces in order to communicate with the server. All agents will be loaded at system startup according to a configuration file, and will communicate with their respective driver using a network protocol or through any other IPC mechanism.