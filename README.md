# ProyectoParalelo

## Main file - Google Maps Locations
g++ main.cpp -fopenmp -o main
./main

## Tests for correctness of algorithm
g++ tests.cpp -fopenmp -o tests
./tests


## Tests for optimization algorithm
g++ optimization.cpp -fopenmp -o opt
./opt < input.txt