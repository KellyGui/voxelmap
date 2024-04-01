# voxelmap
This repository is to build a 3D grid map from point clouds file(in .las format).
## Build
### Pure C++
To build in C++ version, you need to modify the CMakeLists.txt by comment the setting about Pybind11.
```$ mkdir build
   $ cd build
   $ cmake ..
   $ make  ```
### Build with Pybind11
Since it need the support of python interpreter, we recommend you to build it with g++ command by setting all needed including directories and linked libraries
