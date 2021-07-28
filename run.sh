#!/bin/bash

#SBATCH --job-name=matrix_mult # nombre del job
#SBATCH -c 4 #numero de cores
#SBATCH --mem-per-cpu=32gb #tamano de memoria del job en ejecucion

./main
