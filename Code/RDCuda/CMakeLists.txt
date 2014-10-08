
rdkit_cuda_library(RDCudaLib hello-world.cu LINK_LIBRARIES GraphMol)
SET_TARGET_PROPERTIES(RDCudaLib PROPERTIES COMPILE_FLAGS "-fPIC")
rdkit_headers(hello-world.h DEST RDCuda)

add_subdirectory(Wrap)