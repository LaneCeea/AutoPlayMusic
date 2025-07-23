# AutoPlayMusic

A simple C++ application that randomly plays MP3 files from a music directory with random cooldown periods between songs.

## Overview

A lightweight music player that randomly plays MP3 files with smart cooldown periods between songs. Built with C++17 and uses the [miniaudio](https://github.com/mackron/miniaudio) library for audio playback.

## Features

- **Random playback** - No predictable order, just pure randomness
- **Smart cooldown** - Random 5-10 minute breaks between songs
- **Simple setup** - Just drop your MP3s in a music folder
- **Lightweight** - Minimal dependencies and resource usage
- **Timestamped** - Shows when each song starts playing

## Build Instructions

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler (tested with MSVC and MinGW-W64 on Windows)

### Building
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The executable will be created in the build directory.

## Usage

1. Create a `music` folder in the project root directory (The program will automatically find the `music` folder by searching upward from the executable location.)

2. Add your MP3 files to the `music` folder

3. Run the executable from anywhere in the project

The program will:
- List all MP3 files it found
- Display timestamps when playing each song
- Play songs randomly with 5-10 minute breaks between them
- Run indefinitely until you stop it (Ctrl+C)

## Notes

- Only tested on Windows
- Only supports MP3 files
- Make sure your music folder has at least one MP3 file!