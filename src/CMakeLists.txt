FIND_PACKAGE(VTK REQUIRED)
INCLUDE_DIRECTORIES( ${VTK_INCLUDE_DIRS}  )

# 增加PCL库的依赖
set(PCL_DIR "/usr/lib/x86_64-linux-gnu/cmake/pcl/PCLConfig.cmake")
FIND_PACKAGE( PCL REQUIRED )

# 添加头文件和库文件
INCLUDE_DIRECTORIES( ${PCL_INCLUDE_DIRS}  )
# LINK_LIBRARIES( ${PCL_LIBRARY_DIRS} )
ADD_DEFINITIONS( ${PCL_DEFINITIONS} )
message(STATUS "PCL_DIR = ${PCL_LIBRARY_DIRS}")
message(STATUS "PCL_INCLUDE_DIRS = ${PCL_INCLUDE_DIRS}")

set(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall  -Wl,--copy-dt-needed-entries")

#pybind11
find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11)
INCLUDE_DIRECTORIES(
    ${pybind11_INCLUDE_DIRS}
)
# octomap
FIND_PACKAGE( octomap  CONFIG  REQUIRED )
#INCLUDE_DIRECTORIES( ${OCTOMAP_INCLUDE_DIRS} 

if(octomap_FOUND)
    INCLUDE_DIRECTORIES( ${OCTOMAP_INCLUDE_DIRS} )
else(octomap_FOUND)
    message(FATAL_ERROR ”octomap library not found”)
endif(octomap_FOUND)

# find_package(GDAL  REQUIRED)
# if(GDAL_FOUND)
#     INCLUDE_DIRECTORIES(${GDAL_INCLUDE_DIRS})
# else(GDAL_FOUND)
#     message(FATAL_ERROR ”GDAL library not found”)
# endif(GDAL_FOUND)


#liblas
FIND_PACKAGE( libLAS REQUIRED)
INCLUDE_DIRECTORIES( ${LIBLAS_INCLUDE_DIRS} )

#boost
# find_package(Boost 1.82 REQUIRED
#              COMPONENTS system filesystem thread)
# include_directories(${Boost_INCLUDE_DIRS})

# include_directories("/usr/include")
# link_directories("/usr/lib/x86_64-linux-gnu/")



# ADD_EXECUTABLE( map  voxelmap.cpp )
# TARGET_LINK_LIBRARIES( map
#     las
#     ${PCL_LIBRARIES}
#     ${VTK_LIBRARIES}
#     ${OCTOMAP_LIBRARIES})

# 创建 C++ 模块
add_library(voxelmap MODULE voxelmap.cpp)
TARGET_LINK_LIBRARIES(voxelmap
   pybind11::module
   las
   ${PCL_LIBRARIES}
   ${VTK_LIBRARIES}
   ${OCTOMAP_LIBRARIES}
    # ${Boost_LIBRARIES}
   )