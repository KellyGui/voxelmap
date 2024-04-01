#pragma once
#include <iostream>
#include <assert.h>
//octomap 
#include <octomap/octomap.h>
//pcl
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/visualization/cloud_viewer.h>
#include <vtk-9.1/LSDynaMetaData.h>


class VoxelMap{
public:
    octomap::OcTree* tree;
    octomap::point3d center;
    int utm_zone;
    // octomap::Pointcloud cloud;

public:
    VoxelMap(double resolution, double x, double y, double z, int zone);
    ~VoxelMap(){}
    void addMap(std::string &pc_file, int zone);
    void saveMap(std::string &output_file);
    void insertPointcloud(pcl::PointCloud<pcl::PointXYZ>::Ptr pc,octomap::Pointcloud &cloud);
};


// g++ -v -std=c++14  -O0 -Wall -shared -fPIC $(python3 -m pybind11 --includes)  /home/a62/GMP/voxelMap/projects/voxelMap/src/voxelmap.cpp -o ../../bin/voxelmap$(python3-config --extension-suffix) -I/usr/include/vtk-9.1 -I/usr/include/eigen3  -I/usr/include/pcl-1.12 -I/home/a62/GMP/voxelMap/projects/voxelMap/include  -Wl,-rpath,/usr/local/lib:/home/a62/anaconda3/files/envs/cv2/lib /usr/lib/x86_64-linux-gnu/libpcl_apps.so /usr/lib/x86_64-linux-gnu/libpcl_outofcore.so /usr/lib/x86_64-linux-gnu/libpcl_people.so -lOpenNI /usr/lib/x86_64-linux-gnu/libusb-1.0.so -lOpenNI2 /usr/lib/x86_64-linux-gnu/libusb-1.0.so /usr/lib/x86_64-linux-gnu/libflann_cpp.so /usr/local/lib/liboctomap.so /usr/local/lib/liboctomath.so /usr/lib/x86_64-linux-gnu/libpcl_surface.so /usr/lib/x86_64-linux-gnu/libpcl_keypoints.so /usr/lib/x86_64-linux-gnu/libpcl_tracking.so /usr/lib/x86_64-linux-gnu/libpcl_recognition.so /usr/lib/x86_64-linux-gnu/libpcl_registration.so /usr/lib/x86_64-linux-gnu/libpcl_stereo.so /usr/lib/x86_64-linux-gnu/libpcl_segmentation.so /usr/lib/x86_64-linux-gnu/libpcl_features.so /usr/lib/x86_64-linux-gnu/libpcl_filters.so /usr/lib/x86_64-linux-gnu/libpcl_sample_consensus.so /usr/lib/x86_64-linux-gnu/libpcl_ml.so /usr/lib/x86_64-linux-gnu/libpcl_visualization.so /usr/lib/x86_64-linux-gnu/libpcl_search.so /usr/lib/x86_64-linux-gnu/libpcl_kdtree.so /usr/lib/x86_64-linux-gnu/libpcl_io.so /usr/lib/x86_64-linux-gnu/libpcl_octree.so -lpng -lz -lOpenNI /usr/lib/x86_64-linux-gnu/libusb-1.0.so -lOpenNI2 /usr/lib/x86_64-linux-gnu/libvtkChartsCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkInteractionImage-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOGeometry-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libjsoncpp.so /usr/lib/x86_64-linux-gnu/libvtkIOPLY-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingLOD-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkViewsContext2D-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkViewsCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkGUISupportQt-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkInteractionWidgets-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersModeling-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkInteractionStyle-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersExtraction-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOLegacy-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingAnnotation-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingContext2D-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingFreeType-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libfreetype.so /usr/lib/x86_64-linux-gnu/libvtkImagingSources-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkIOImage-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkImagingCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingOpenGL2-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingUI-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkRenderingCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonColor-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersGeometry-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersSources-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersGeneral-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonComputationalGeometry-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkFiltersCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonExecutionModel-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonDataModel-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonMisc-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonTransforms-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkCommonMath-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libvtkkissfft-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libGLEW.so /usr/lib/x86_64-linux-gnu/libX11.so /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.15.3 /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3 /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3 /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3 /usr/lib/x86_64-linux-gnu/libvtkCommonCore-9.1.so.9.1.0 /usr/lib/x86_64-linux-gnu/libtbb.so.12.5 /usr/lib/x86_64-linux-gnu/libvtksys-9.1.so.9.1.0 -ldl /usr/lib/x86_64-linux-gnu/libpcl_common.so /home/a62/anaconda3/files/envs/cv2/lib/libboost_system.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_filesystem.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_atomic.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_date_time.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_iostreams.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libboost_serialization.so.1.82.0 /home/a62/anaconda3/files/envs/cv2/lib/libqhull_r.so.8.0.2 -lm