// This is the REAL "hello world" for CUDA!
// It takes the string "Hello ", prints it, then passes it to CUDA
// with an array of offsets. Then the offsets are added in parallel
// to produce the string "World!"
// By Ingemar Ragnemalm 2010

// nvcc hello-world.cu -L /usr/local/cuda/lib -lcudart -o hello-world

#include <stdio.h>
#include <GraphMol/GraphMol.h>
namespace RDCuda {
    
    void helloworld();
    void hellomol(RDKit::ROMol &mol);
}
