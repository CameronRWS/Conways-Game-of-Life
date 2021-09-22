# COMS 327 - Project 1 Part A
This part of the project is the infrastructure for the sand painting project.

## Features Implemented

1. Initialize a 1D Cellular Automata (1DCA)
2. Set the value of a specific cell in the 1DCA
3. Print a 1DCA
4. Demos all 3 previously mentioned features per the assignment requirements.

## Known Errors and Issues

The input validation for set1DCACell only checks for negative values of the passed in index. Future parts of this project will allow for much better input validation.

## Usage (How to Execute)

Run this command to build the project.
```sh
make
```
Run this command to run the project.
```sh
./odca.out
```
Run this command to clean the project (remove *.o and *.out files).
```sh
make clean
```
