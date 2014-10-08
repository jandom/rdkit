rdkit_python_extension(cuda
                       cuda.cpp
                       DEST CUDA
                       LINK_LIBRARIES RDCudaLib GraphMol)

