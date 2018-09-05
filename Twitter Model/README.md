# CS104 HW 8 - Alex Volcy

## Problem 0: Update Function Defs 

Functions were updated.

## Problem 1: Updated Heap

## The problems will be compiled as a whole, see problem 4 for the details

### Known Issues & Assumptions Made

I have a valgrind error, where it gets mad that in heap.h i call trickleUp with it->second. It was resolved when it used keyToLocation[old] but by fixing the error, it lead to an incorrect trending. So i left the error in there. Assumed we didn't have to submit our test files for heap, but just the .h file.

## Problem 2: Hashtags

## The problems will be compiled as a whole, see problem 4 for the details

### Known Issues & Assumptions Made

No Known Issues.

## Problem 3: Hash Function

## Compiling This Part

The problems will be compiled as a whole, see problem 4 for the details

### Known Issues & Assumptions Made

No Known Issues.

## Problem 4: Users and Passwords

## Compiling The Project

```
make
./twitter twitter.dat

```

### Known Issues & Assumptions Made

No Known Issues.

## Extra Credit: Splay Trees

## Compiling the splay tree
```
g++ -g -Wall name_of_test_file -o name_of_executable
./name_of_executable

note: splayTest.cpp is my test file if you'd like to use it

```


### Known Issues & Assumptions Made

I did not implement the splay tree into my twitter. But it is able to have nodes inserted and splayed. For the get and [] functions, it was unclear in the instructions how we were supposed to handle the case of someone trying to access a key that didn't exist. For my implementation, i created a dummy node to return to have warnings go away, but if you do try to access a non-existant key, it will segfault.
