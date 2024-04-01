#include "map.hpp"
#include "utils.hpp"
#include<chrono>
#include <pybind11/pybind11.h>
#include <liblas/liblas.hpp>
#define ZONE_DIST 667170.4784 
namespace py = pybind11;

VoxelMap::VoxelMap(double resolution, double x, double y, double z, int zone)//:tree(NULL)
{
    tree = new octomap::OcTree(resolution);
    center(0)= x;
    center(1) = y;
    center(2) = z;
    utm_zone = zone;
}


void VoxelMap::addMap(std::string &pc_file, int zone)
{
    // pcl::PointCloud<pcl::PointXYZ>::Ptr tmp_cloud  = pcl::PointCloud<pcl::PointXYZ>::Ptr (new pcl::PointCloud<pcl::PointXYZ>);
    // pcl::io::loadPCDFile<pcl::PointXYZ> (pc_file, *tmp_cloud);
    std::ifstream ifs;
    ifs.open(pc_file, std::ios::in | std::ios::binary);
    liblas::ReaderFactory f;
    liblas::Reader reader = f.CreateWithStream(ifs);
    // *cloud += *tmp_cloud;
    // int size = tmp_cloud->points.size();
    octomap::Pointcloud cloud;

    if(utm_zone!=zone)
    {
        int flag =1;
        if(utm_zone>zone)
            flag=-1;
        while(reader.ReadNextPoint())
        {
            liblas::Point const& p = reader.GetPoint();
            // 将点云里的点插入到octomap中
            octomap::point3d tmpp =  octomap::point3d(p.GetX()+flag*ZONE_DIST-center(0), p.GetY()-center(1), p.GetZ()-center(2));
            tree->updateNode( tmpp, true );
        }

    }
    else{
        while (reader.ReadNextPoint())
        {
            liblas::Point const& p = reader.GetPoint();
            // 将点云里的点插入到octomap中
            octomap::point3d tmpp =  octomap::point3d(p.GetX()-center(0), p.GetY()-center(1), p.GetZ()-center(2));
            tree->updateNode( tmpp, true );
        }

    }

   
    // insertPointcloud(tmp_cloud,cloud);
    // tree->insertPointCloud(cloud,center);
    // 更新octomap
    tree->updateInnerOccupancy();

}

void VoxelMap::saveMap(std::string &output_file)
{
    tree->writeBinary(output_file);
}

void VoxelMap::insertPointcloud(pcl::PointCloud<pcl::PointXYZ>::Ptr pc, octomap::Pointcloud &cloud)
{
    for(auto p: pc->points)
    {
        double x = p.x-center.x();
        double y =  p.y-center.y();
        double z = p.z-center.z();
        // double x = p.x;
        // double y = p.y;
        // double z = p.z;
        // cloud.push_back(x,y,z);
        tree->updateNode( octomap::point3d(x,y,z), true );
    }
    int size = cloud.size();
}

PYBIND11_MODULE(voxelmap,m){
    py::class_<VoxelMap>(m,"VoxelMap")
                        .def(py::init<const int&, const double &, const double &, const double &,const int&>())
                        .def("addMap", &VoxelMap::addMap)
                        .def("saveMap", &VoxelMap::saveMap);
}

int main()
{
    std::cout<<"test"<<std::endl;
    auto beforeTime = std::chrono::steady_clock::now();     
    VoxelMap *cmap = new VoxelMap(8, 240871.4783728265,3509535.5836132346,38.28,50);
    // cmap->initMap(8);
    vector<string> files;
    get_need_file("/home/a62/GMP/voxelMap/wuxi",files,".pcd");
    int count=0;
    for(auto f : files){
        
	
        cmap->addMap(f,50);
        
        count++;
        std::cout<<f<<endl;
      
        // if(count==1) break;

    }
    string output = "/home/a62/GMP/voxelMap/projects/voxelMap/build/wuxi.bt";
    cmap->saveMap(output);
    auto afterTime = std::chrono::steady_clock::now();
    double duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    std::cout<<duration_second<<std::endl;
    return 0;
}