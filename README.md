# voxelmap
This repository is to build a 3D grid map from point clouds file(in .las format).
## Build
### Pure C++
To build in C++ version, you need to modify the CMakeLists.txt by comment the setting about Pybind11.
```$ mkdir build
   $ cd build
   $ cmake ..
   $ make  ```
