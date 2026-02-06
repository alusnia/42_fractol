🌀 Fract-olFract-ol is a graphical exploration project developed at 42 School. It renders mathematically complex fractal sets (Mandelbrot, Julia) in real-time using the MiniLibX library.
  Unlike standard command-line tools, this version features a fully interactive guide that helps you configure the visualization exactly how you want it before the window opens.

🚀 FeaturesInteractive Configuration:

  1. A step-by-step CLI menu to select the fractal type, iteration depth, and starting parameters.
  2. Infinite Zoom: Deep zoom capabilities using the mouse wheel (zooms towards the cursor).
  3. Panning: Move around the coordinate system using arrow keys.
  4. Dynamic Colors: Toggle color modes instantly with the keyboard.
  5. Data Export: Click on the Mandelbrot set to output precise coordinates to the terminal.

🖥️ UsageThis program is designed to be self-explanatory. You do not need to memorize command-line flags.

  1. Run the executable: ./fractol
  2. Follow the on-screen instructions:The program will guide you through the setup process, asking for:

     Fractal type (Mandelbrot, Julia, etc.)
     Max iterations (quality/depth)
     Specific coordinates (for Julia sets)
     
🎮 ControlsOnce the graphical window is open, use the following controls to navigate the fractal:

    Scroll Wheel       - Zoom In / Zoom Out (at cursor position)
    Arrow Keys         - Move the view (Pan)
    [ G ]              - Color Shift Mode (Change color palette)
    Left Mouse Button  - Export Coordinates (Print logic to terminal - Mandelbrot only)
    [ ESC ] or ( X )   - Close the program
    
  🛠️ Installation
  Clone the repository:
    git clone <repository_url>
Compile the project:
    make - (This will automatically compile the MiniLibX library and necessary dependencies).
    
Enjoy the math!
