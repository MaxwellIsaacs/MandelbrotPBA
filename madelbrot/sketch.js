// globals for zoom and pan
let zoom = 1;
let offsetX = 0;
let offsetY = 0;

/*
* @brief sets up canvas and drawing settings
* @return void
*/
function setup() {
  createCanvas(700, 700); // size of canvas
  pixelDensity(1); // handle high res displays
  noLoop(); // static image, no continuous redrawing
}

/*
* @brief draws mandelbrot set, adjusting for zoom and pan
* @return void
*/
function draw() {
  loadPixels(); // loads pixel array for manipulation

  // max iterations for mandelbrot calc
  const maxIterations = 100;

  // adjust these for zooming and shifting
  const w = 4 / zoom; // adjusted width for zoom
  const h = (w * height) / width; // adjusted height for aspect ratio
  const xMin = -w / 2 + offsetX; // x offset
  const yMin = -h / 2 + offsetY; // y offset

  // iterate over every pixel
  for (let x = 0; x < width; x++) {
    for (let y = 0; y < height; y++) {
      // scale pixel coordinate to mandelbrot coord
      let a = map(x, 0, width, xMin, xMin + w);
      let b = map(y, 0, height, yMin, yMin + h);
      const ca = a; // constant a for mandelbrot calc
      const cb = b; // constant b for mandelbrot calc
      let n = 0; // iteration counter

      // mandelbrot calculation
      while (n < maxIterations) {
        const aa = a * a - b * b; // real component
        const bb = 2 * a * b; // imaginary component
        a = aa + ca; // iterate real part
        b = bb + cb; // iterate imag part
        if (abs(a + b) > 16) {
          break; // escapes if it's not in the set
        }
        n++;
      }

      // coloring based on iterations
      let bright = map(n, 0, maxIterations, 0, 255);
      if (n === maxIterations) {
        bright = 0; // in set, make it black
      }

      // set pixel color
      const pix = (x + y * width) * 4;
      pixels[pix + 0] = bright; // red
      pixels[pix + 1] = bright; // green
      pixels[pix + 2] = bright; // blue
      pixels[pix + 3] = 255; // alpha
    }
  }
  updatePixels(); // update canvas with pixel array
}

/*
* @brief handles dragging for panning
* @params event (mouse wheel data)
* @return void
*/
function mouseWheel(event) {
  // update zoom based on wheel data
  zoom *= event.delta < 0 ? 1.1 : 0.9;
  redraw(); // redraw the mandelbrot with new zoom
}
