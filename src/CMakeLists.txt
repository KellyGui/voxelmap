FIND_PACKAGE(VTK REQUIRED)
INCLUDE_DIRECTORIES( ${VTK_INCLUDE_DIRS}  )

# 增加PCL库的依赖
set(PCL_DIR "/usr/lib/x86_64-linux-gnu/cmake/pcl/PCLConfig.cmake")
FIND_PACKAGE( PCL REQUIRED )

#liblas
FIND_PACKAGE( libLAS REQUIRED)
INCLUDE_DIRECTORIES( ${LIBLAS_INCLUDE_DIRS} )

# 添加头文件和库文件
INCLUDE_DIRECTORIES( ${PCL_INCLUDE_DIRS}  )
# LINK_LIBRARIES( ${PCL_LIBRARY_DIRS} )
ADD_DEFINITIONS( ${PCL_DEFINITIONS} )
message(STATUS "PCL_DIR = ${PCL_LIBRARY_DIRS}")
message(STATUS "PCL_INCLUDE_DIRS = ${PCL_INCLUDE_DIRS}")

set(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall  -Wl,--copy-dt-needed-entries")

#python interpreter
include_directories("/usr/include/python3.10")
link_directories("/home/a62/anaconda3/files/pkgs/python-3.9.18-h955ad1f_0/lib")
#pybind11
find_package(pybind11 REQUIRED)
# octomap
FIND_PACKAGE( octomap  CONFIG  REQUIRED )
#INCLUDE_DIRECTORIES( ${OCTOMAP_INCLUDE_DIRS} )

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



# find_package(Tiff  REQUIRED)


include_directories("/usr/include")
link_directories("/usr/lib/x86_64-linux-gnu/")
# if(Tiff_FOUND)
#     INCLUDE_DIRECTORIES(${LIBTIFF_INCLUDE_DIRS})
#     message(TIFF_VERSION)
# else(Tiff_FOUND)
#     message(FATAL_ERROR ”Tiff library not found”)
# endif(Tiff_FOUND)


ADD_EXECUTABLE( map  voxelmap.cpp )
TARGET_LINK_LIBRARIES( map
    las
    ${PCL_LIBRARIES}
    ${VTK_LIBRARIES}
    ${OCTOMAP_LIBRARIES})

# 创建 C++ 模块
pybind11_add_module(pymap voxelmap.cpp)
# target_link_libraries(pymap
#    ${PCL_LIBRARIES}
#    ${VTK_LIBRARIES}
#    ${OCTOMAP_LIBRARIES}

#    )
# g++ -v -std=c++14  -O0 -Wall -shared -fPIC $(python3 -m pybind11 --includes)  /home/a62/GMP/voxelMap/projects/voxelMap/src/voxelmap.cpp -o ../../bin/voxelmap$(python3-config --extension-suffix) -I/usr/include/vtk-9.1 -I/usr/include/eigen3  -I/usr/include/pcl-1.12 -I/home/a62/GMP/voxelMap/projects/voxelMap/include  -Wl,-rpath,/usr/local/lib:/home/a62/anaconda3/files/envs/cv2/lib /usr/lib/x86_64-linux-gnu/libpcl_apps.so /usr/lib/x86_64-linux-gnu/libpcl_outofcore.so /usr/lib/x86_64-linux-gnu/libpcl_people.so -lOpenNI /usr/lib/x86_64-linux-gnu/libusb-1.0.so -lOpenNI2 /usr/lib/x86_64-linux-gnu/libusb-1.0.so /usr/lib/x86_64-linux-gnu/libflann_cpp.so /usr/local/lib/liboctomap.so /usr/local/lib/liboctomath.so /usr/lib/x86_64-linux-gnu/libpcl_surface.so /usr/lib/x86_64-linux-gnu/libpcl_keypoints.so /usr/lib/x86_64-linux-gnu/libpcl_tracking.so /usr/lib/x86_64-linux-gnu/libpcl_recognition.so /usr/lib/x86_64-linux-gnu/libpcl_registration.so /usr/lib/x86_64-linux-gnu/libpcl_stereo.so /usr/lib/x86_64-linux-gnu/libpcl_segmentation.so /usr/lib/x86_64-linux-gnu/libpcl_features.so /usr/lib/x86_64-linux-gnu/libpcl_filters.so /usr/lib/x86_64-linux-gnu/libpcl_sample_consensus.so /usr/lib/x86_64-linux-gnu/libpcl_ml.so /usr/lib/x86_64-linux-gnu/libpcl_visualization.so /usr/lib/x86_64-linux-gnu/libpcl_search.so /usr/lib/x86_64-linux-gnu/libpcl_kdtree.so /usr/lib/x86_64-linux-gnu/libpcl_io.so /usr/lib/x86_64-linux-gnu/libpcl_octree.so -lpng -lz -lOpenNI /usr/lib/x86_64-linux-gnu/libusb-1.0.so -lOpenNI2 /usr/lib/x86_64-linux-gnu/libvtkChartsCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkInteractionImage-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOGeometry-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libjsoncpp.so /usr/lib/x86_64-linux-gnu/libvtkIOPLY-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingLOD-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkViewsContext2D-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkViewsCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkGUISupportQt-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkInteractionWidgets-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersModeling-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkInteractionStyle-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersExtraction-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOLegacy-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingAnnotation-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingContext2D-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingFreeType-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libfreetype.so /usr/lib/x86_64-linux-gnu/libvtkImagingSources-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOImage-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkImagingCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingOpenGL2-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingUI-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonColor-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersGeometry-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersSources-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersGeneral-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonComputationalGeometry-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonExecutionModel-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonDataModel-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonMisc-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonTransforms-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonMath-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkkissfft-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libGLEW.so /usr/lib/x86_64-linux-gnu/libX11.so /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.15.3 /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3 /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3 /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3 /usr/lib/x86_64-linux-gnu/libvtkCommonCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libtbb.so.12.5 /usr/lib/x86_64-linux-gnu/libvtksys-9.1.so.9.1.0 -ldl /usr/lib/x86_64-linux-gnu/libpcl_common.so /home/a62/anaconda3/files/envs/cv2/lib/libboost_system.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_filesystem.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_atomic.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_date_time.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_iostreams.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_serialization.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libqhull_r.so.8.0.2 -lm