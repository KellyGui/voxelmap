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


struct Point2d{
    double x;
    double y;
};

class VoxelMap{
public:
    octomap::OcTree* tree;
    octomap::point3d center;
    int utm_zone;
    // octomap::Pointcloud cloud;

public:
    VoxelMap(double resolution, double x, double y, double z, int zone);
    VoxelMap(std::string &map, double resolution,double x, double y, double z,int zone);
    ~VoxelMap(){ delete tree;}
    void addMap(std::string &pc_file, int zone);
    void saveMap(std::string &output_file);
    void insertPointcloud(pcl::PointCloud<pcl::PointXYZ>::Ptr pc,octomap::Pointcloud &cloud);
    void updateMap( std::string &sub, std::vector<Point2d> &polygon, int zone);
    bool isInPolygon(Point2d &p, std::vector<Point2d> &polygon);

    void octomap2pcd(std::string &pcd_file);
};
