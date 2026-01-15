# Planet Donut - 2D Resource Gathering Simulation

A C++ simulation of autonomous robot fleets on a toroidal planet, featuring resource prospecting, mining, and transportation with real-time GUI visualization.

## Overview

Planet Donut is a 2D simulation where multiple bases deploy fleets of specialized robots to locate resource deposits (gisements), mine them, and transport resources back to base. The simulation takes place on a toroidal surface (donut-shaped planet), meaning objects that exit one edge reappear on the opposite side.

This project was developed as part of the EPFL ICC (Introduction to C++) course.

## Features

- **Toroidal Geometry**: Wrap-around world with proper distance calculations
- **Multiple Robot Types**: Four specialized robot classes with distinct behaviors
- **Real-time Visualization**: GTKmm-based GUI with Cairo graphics
- **File I/O**: Save and load simulation states
- **Robot Connectivity**: Communication network between robots and bases
- **Resource Management**: Mining, transport, and base resource tracking

## Robot Types

| Type | Symbol | Function | Max Distance |
|------|--------|----------|--------------|
| **Prospection** | X | Explores and locates resource deposits | 10,000 km |
| **Forage** (Mining) | + | Extracts resources from deposits | 1,420 km |
| **Transport** | □ | Carries resources back to base | 5,000 km |
| **Communication** | ))) | Maintains relay network | 1,420 km |

## Repository Structure

```
planet-donut-simulation/
├── src/
│   ├── projet.cc        # Main entry point
│   ├── simulation.cc    # Simulation logic and file I/O
│   ├── base.cc          # Base station management
│   ├── robot.cc         # Robot classes implementation
│   ├── gisement.cc      # Resource deposit handling
│   ├── geomod.cc        # Toroidal geometry calculations
│   ├── gui.cc           # GTKmm GUI implementation
│   ├── graphic.cc       # Cairo drawing functions
│   └── message.cc       # Error message generation
├── include/
│   ├── simulation.h
│   ├── base.h
│   ├── robot.h
│   ├── gisement.h
│   ├── geomod.h
│   ├── gui.h
│   ├── graphic.h
│   ├── graphic_gui.h
│   ├── constantes.h     # Simulation constants
│   └── message.h
├── docs/
│   └── Rendu 3 rapport prog.pdf  # Project report (French)
├── Makefile
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Requirements

### Dependencies

- **C++11** compatible compiler (g++ recommended)
- **GTKmm 3.0** - C++ interface for GTK+
- **pkg-config** - For library configuration

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get install build-essential libgtkmm-3.0-dev pkg-config
```

**macOS (Homebrew):**
```bash
brew install gtkmm3 pkg-config
```

**Fedora:**
```bash
sudo dnf install gcc-c++ gtkmm30-devel pkg-config
```

## Building

### Using Make

```bash
make
```

### Using CMake

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

### Running the Simulation

```bash
./projet [simulation_file]
```

- Without arguments: Opens with empty simulation
- With file argument: Loads the specified simulation file

### GUI Controls

| Button | Function |
|--------|----------|
| **Open** | Load simulation from file |
| **Save** | Save current simulation state |
| **Start/Stop** | Toggle continuous simulation |
| **Step** | Execute single simulation step |
| **Toggle Link** | Show/hide robot communication links |
| **Toggle Range** | Show/hide robot communication ranges |

### Keyboard Shortcuts

- `s` - Start/Stop simulation
- `1` - Single step

## Simulation File Format

Simulation files are plain text with the following structure:

```
# Gisements (Resource Deposits)
<number_of_deposits>
<x> <y> <radius> <resources>
...

# Bases
<number_of_bases>
<x> <y> <resources> <nbP> <nbF> <nbT> <nbC>
  <robot_data>
  ...
```

### Example

```
# Gisements
2
100 200 75 5000
-300 150 100 8000

# Bases
1
0 0 1000 2 1 1 1
  1 0 0 0 100 200 false false true 100 200 75 5000
  2 0 0 0 100 200 false
  3 0 0 0 0 0 false false
  4 0 0 0 0 0 false
```

## Simulation Constants

| Constant | Value | Description |
|----------|-------|-------------|
| `dim_max` | 1000 km | World dimension (±1000) |
| `rayon_min` | 50 km | Minimum deposit radius |
| `rayon_max` | 150 km | Maximum deposit radius |
| `rayon_comm` | 300 km | Robot communication range |
| `deltaD` | 5 km | Movement step per tick |
| `iniR` | 1000 kt | Initial base resources |
| `finR` | 10000 kt | Target resources for victory |

## Architecture

### Class Hierarchy

```
Robot (base class)
├── RobotProspection  - Resource discovery
├── RobotForage       - Resource extraction
├── RobotTransport    - Resource transport
└── RobotCommunication - Network relay
```

### Key Modules

- **geomod**: Toroidal geometry calculations (distance, intersection, point equivalence)
- **simulation**: File parsing, simulation loop, robot coordination
- **base**: Robot management, resource tracking, connectivity
- **gui**: GTKmm window, event handling, drawing coordination

## Documentation

Detailed project documentation is available in French in `docs/Rendu 3 rapport prog.pdf`.

## License

MIT License

Copyright (c) 2021 Daniel Abraham Elmaleh, Imane Jennane

See [LICENSE](LICENSE) for details.

## Authors

- **Daniel Abraham Elmaleh** (SCIPER: 311287)
- **Imane Jennane** (SCIPER: 310900)

EPFL - School of Computer and Communication Sciences
ICC Course Project, May 2021

## Acknowledgments

This project was developed as part of the Introduction to C++ (ICC) course at EPFL, under the guidance of the ICC teaching staff.
