# miniRT - My first RayTracer with miniLibX

## Description
miniRT is a school project aimed at generating images using the Raytracing protocol. The program creates computer-generated images that represent scenes from specific angles and positions, defined by simple geometric objects, and each with its own lighting system.

## Features
- Use of miniLibX for window management.
- Support for simple geometric objects: plane, sphere, and cylinder.
- Ability to resize objects' unique properties.
- Application of translation and rotation transformations to objects, lights, and cameras.
- Light management including spot brightness, hard shadows, and ambiance lighting.
- Display of the image in a window with fluid window management.
- Ability to read scene descriptions from a file.

## Installation
1. Clone the repository:
   ```bash
   git clone <repository_url>
   ```
2. Compile the project using the provided Makefile:
   ```bash
   cd miniRT
   make
   ```
3. Execute the program with a scene description file:
   ```bash
   ./miniRT <scene_file.rt>
   ```

## Usage
- The program takes a scene description file as input with the .rt extension.
- Each element in the scene can be separated by one or more line breaks and spaces.
- Misconfigurations in the scene file will cause the program to exit with an error message.

## Example
```
A 0.2 255,255,255
C -50,0,20 0,0,0 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

## Saving Image
To save the generated image as a PPM file, use the `-S` option followed by the filename:
```bash
./miniRT <scene_file.rt> -S <filename.ppm>
```

## Credits
This project is part of the curriculum at 42 Mulhouse.
