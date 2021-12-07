# COMS 327 - Project 2 Part B
This part of the project is an implementation of Conway's Game of Life displayed on a graphics window with the ability for user interaction.

## Features Implemented

1. CellularAutomaton (CA) class implementation for storing, displaying, and modifying a cellular automaton.
2. GraphicsClient (GC) class implementation for easily communicating with a graphics window.
3. GCMessage class implementation for storing and modifying messages sent to the graphics client from the graphics window.
4. CAGraphicsSimulator class implementation for simulating a cellular automaton on a graphics window as well as allowing for user interaction.
5. casimulator main method for initializing a CA and GC then simulating the CA graphically.

## Known Errors and Issues

- If the file selected to load is not a cellular automaton (CA) then a blank CA is loaded.

## Usage (How to Execute)

Run this command to build the project.
```sh
make
```
Run this command to run the project.
```sh
./gol <text file path to CA definition (string)>
```
You can also use this command to run the project with a predefined CA.
```sh
make run
```
Run this command to clean the project (remove *.o and executable files).
```sh
make clean
```
