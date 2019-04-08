# See-Saw Simulator

Trevor Kling
8 April 2019
CPSC 380: Operating Systems

## Introduction

Simulates a physical see-saw being used by two individuals using multithreading.

## Specification

The program is written in C++ using the POSIX pthreads library.  A semaphore is used to maintain synchronization across the two threads, each of which is given one person on the see-saw to simulate.  The program runs for 10 iterations of up-down motion of the see-saw, outputting its datat to the command line one every second of simulation.

## Known Issues
None.

## Sources
None.
