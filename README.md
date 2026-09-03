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
- Open `CMakeLists.txt` in Visual Studio 2022 using [Qt VS Tools](https://doc.qt.io/qtvstools/qtvstools-getting-started.html) and [C++ CMake tools for Windows](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)

   **OR**

- Open `CMakeLists.txt` in Qt Creator

### Linux
- Open `CMakeLists.txt` in Qt Creator

### Command Line

```bash
cmake -G "Ninja" -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=staging
ninja install -C build
```

### Binaries
- CLI: `staging/bin/q3tod3_map.exe`
- GUI: `staging/bin/q3tod3_map_gui.exe`
- Lbraries: `staging/bin` + `staging/plugins`
- Translations (unused): `staging/translations`

## Credits
**motorsep** - q3tod3_map creator

**Sour Dani** - q3tod4_map_gui creator and q3tod3_map (core and cli) modifications

### Special thanks
**craftablescience** - For CMake help and inspiration from MareTF CLI
