# feup-cpar
##Parallel implementation of the The Sieve of Erastosthenes algorithm

#####Setup OpenMP
1. This site was built using [Youtube](https://www.youtube.com/watch?v=QIMAu_o_5V8)
2. WordPress [Tutorial](https://likymice.wordpress.com/2015/03/13/install-open-mpi-in-ubuntu-14-04-13-10/)

#####How to run

> mpic++ -std=c++11 -o sieve.out sieve.cpp
> mpirun -np 1 sieve.out