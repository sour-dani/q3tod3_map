# q3tod3_map
Convert Quake 1-3 map files to Doom 3 and Quake 4 map files from the command prompt or terminal

## Usage
`q3tod3_map.exe q3.map d3.map`
*Specifying an output name is optional* and will output a map with `converted_` appended to the file name.

## Building

### Windows
Compile the `q3to3d_map.sln` file in Visual Studio 2022 and or MSVC2022

### Linux
Compile in `gcc` via `g++ q3to3d_map.cpp -o q3to3d_map`