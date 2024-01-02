# Mandelbrot Set Visualization

## Description
This project visualizes the Mandelbrot set using two different programming environments: p5.js (JavaScript) for web-based interaction and SDL (C) for desktop application. Users can zoom and pan to explore different areas of the Mandelbrot set.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [Credits](#credits)
- [License](#license)

## Installation

### For p5.js (Web version)
1. Ensure you have a modern web browser installed.
2. Clone the repository or download the files.
3. Open `index.html` in your browser to start exploring the Mandelbrot set.

### For SDL (Desktop version)
1. Ensure SDL2 is installed on your system. Visit [SDL's official site](https://www.libsdl.org/download-2.0.php) for installation instructions.
2. Compile the C program with an appropriate compiler for your system. For example, using gcc you might use:
   ```bash
   gcc mandelbrot.c -o mandelbrot -lSDL2
   
## Usage 

### p5.js (Web version)
- Use your mouse wheel to zoom in and out.
- Click and drag to pan around.

### SDL (Desktop version)
- Use `q` to zoom in and `z` to zoom out.
- Use `w`, `a`, `s`, `d` to pan around.
- Close the window to exit.

## Features
- Real-time Mandelbrot set rendering.
- Zoom and pan functionality to explore different parts of the set.
- Two different implementations: Web-based using p5.js and a desktop application using SDL.

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the LICENSE.md file for details.
