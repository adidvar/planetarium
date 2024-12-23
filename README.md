# Planetarium

A 2D gravity simulation program that utilizes the Boost and SFML libraries to model gravitational interactions. This program is designed to simulate the laws of gravity in a two-dimensional space, enabling users to experiment with various scenarios and observe the effects of gravitational forces.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Screenshots](#screenshots)
- [License](#license)
## Installation
Installation for Windows

1. Clone the repository: `git clone https://github.com/adidvar/planetarium.git`
2. Navigate to the project directory: `cd planetarium`
3. Install dependencies using Conan: `conan install . --output-folder=build -s build_type=Release`
4. Create a build directory: `mkdir build && cd build`
5. Generate build files using CMake: `cmake -S .. --preset conan-default``
6. Build the program: `cmake --build . --config Release`
7. Install the program: `cmake --install .`

## Usage
After building the program, you can run it from the command line:

```bash
./planetarium
Load simulation from *.oldsystem files and start it using ENTER + "start {speed}" command.
```

## Screenshots
![Screenshot 1](assets/screenshot1.png)
![Screenshot 2](assets/screenshot2.png)
![Screenshot 3](assets/screenshot3.png)

## License
This project is licensed under the GNU General Public License v3.0 (GPL-3.0). See the LICENSE file for more details.
