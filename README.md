# q3tod3_map
Convert Quake 1, 2, & 3 map files to Doom 3 and Quake 4 map files from the command prompt or terminal

## Usage
### CLI
```bash
# Specify input and optional output name
q3tod3_map.exe input.map output.map

# Specify only the input name to create a file called converted_input.map
q3tod4_map.exe input.map
```

### GUI
- Open `q3tod3_map_gui.exe`
- Click the `Add` button
- Select the map files you want to convert
- Click the `Convert` button
- Each file will be stored next to the original file with `converted_` appended to the name

## Building

### Windows
- Open `q3tod3_map.pro` in Visual Studio 2022 using [Qt VS Tools](https://doc.qt.io/qtvstools/qtvstools-getting-started.html)

   **OR**

- Open `q3tod3_map.pro` in Qt Creator

### Linux
- Open `q3tod3_map.pro` in Qt Creator

### Command Line

```bash
qmake6 -o build
cd build
make
```

### Binaries
- CLI: `build/src/cli/q3tod3_map.exe`
- GUI: `build/src/gui/q3tod3_map_gui.exe`

## Credits
**motorsep** - q3tod3_map creator

**Sour Dani** - q3tod4_map_gui creator and q3tod3_map (core and cli) modifications

### Special thanks
**craftablescience** - For CMake help and inspiration from MareTF CLI
