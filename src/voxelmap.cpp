#include "map.hpp"
#include "utils.hpp"
#include<chrono>
#include <pybind11/pybind11.h>
#include <liblas/liblas.hpp>
#include <cmath>
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


VoxelMap::VoxelMap(std::string &map_file, double resolution,double x, double y, double z,int zone)
{
    tree = new octomap::OcTree(resolution); // 设置八叉树的分辨率
    center(0)= x;
    center(1) = y;
    center(2) = z;
    utm_zone = zone;

    // 从文件加载地图数据
    if (!tree->readBinary(map_file)) {
        std::cerr << "Failed to read octomap file: " << map_file << std::endl;
        return;
    }
}

bool VoxelMap::isInPolygon(Point2d &p, vector<Point2d> &polygon)
{
    int ncross = 0; // 记录与射线相交的边的数量
    int ncount = polygon.size();

    for (int i = 0; i < ncount; i++) { // 遍历多边形的每条边
        Point2d p1 = polygon[i]; // 当前边的起点
        Point2d p2 = polygon[(i + 1) % ncount]; // 当前边的终点，% ncount 是为了处理最后一条边与第一条边相连的情况

        if (p1.y == p2.y) // 如果边平行于射线，则跳过（射线不会与该边相交）
            continue;
        if (p.y < min(p1.y, p2.y)) // 如果射线在边的上方，则跳过
            continue;
        if (p.y >= max(p1.y, p2.y)) // 如果射线在边的下方，则跳过
            continue;

        double x = (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x; // 计算射线与边的交点的 x 坐标
        if (x > p.x) // 如果交点在射线右侧，则增加交点数量
            ncross++; // 只统计单边交点
    }

    return (ncross % 2 == 1); // 如果交点数量为奇数，则点在多边形内；否则在外部
}

void VoxelMap::updateMap(std::string &sub, std::vector<Point2d> &polygon, int zone)
{
    //locate area
    //traverse all leafnode
    for (octomap::OcTree::leaf_iterator it = tree->begin_leafs(); it != tree->end_leafs(); ++it) {
        // 获取节点的坐标和值
        octomap::point3d node = it.getCoordinate();
        double x = it.getX()+center(0);
        double y = it.getY()+center(1);
        double z = it.getZ()+center(2);
        Point2d p; 
        p.x=x;p.y=y;

        if(isInPolygon(p,polygon))
        {
            tree->deleteNode(node);
        }
    }
    addMap(sub,zone);


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
            double x =p.GetX()+flag*ZONE_DIST-center(0);
            double y = p.GetY()-center(1);
            // 将点云里的点插入到octomap中
            if(sqrt(pow(x,2)+pow(y,2))<=3000){
                octomap::point3d tmpp =  octomap::point3d(x,y, p.GetZ());
                tree->updateNode( tmpp, true );
            }
        }

    }
    else{
        while (reader.ReadNextPoint())
        {
            liblas::Point const& p = reader.GetPoint();
            // 将点云里的点插入到octomap中
            double x = p.GetX()-center(0);
            double y =  p.GetY()-center(1);
            if(sqrt(pow(x,2)+pow(y,2))<=3000){
                octomap::point3d tmpp =  octomap::point3d(x,y, p.GetZ());
                tree->updateNode( tmpp, true );
            }
            
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

void VoxelMap::octomap2pcd(std::string &pcd_file)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr occupied_nodes(new pcl::PointCloud<pcl::PointXYZ>());
    liblas::Header header;
    std::ofstream ofs(pcd_file, ios::out | ios::binary);
    liblas::Writer writer(ofs, header);
 
    for(octomap::OcTree::leaf_iterator it = tree->begin_leafs(), end = tree->end_leafs();it != end; ++it){
        liblas::Point point(&header);
        double x = it.getX()+center(0);
        double y = it.getY()+center(1);
        double z = it.getZ()+center(2);
        point.SetCoordinates(x,y,z);
        writer.WritePoint(point);
    }
    // occupied_nodes->header.frame_id = "map";
    // pcl::io::savePCDFileASCII(pcd_file, *occupied_nodes);
}

PYBIND11_MODULE(libvoxelmap,m){
    py::class_<VoxelMap>(m,"VoxelMap")
                        .def(py::init<const int&, const double &, const double &, const double &,const int&>())
                        .def("addMap", &VoxelMap::addMap)
                        .def("saveMap", &VoxelMap::saveMap)
                        .def("updateMap", &VoxelMap::updateMap);
}

int main()
{
    std::cout<<"test"<<std::endl;
    auto beforeTime = std::chrono::steady_clock::now();     
    // VoxelMap *cmap = new VoxelMap(2, 506831.6881012073 , 3184794.9087399053,300.31,51);
    // cmap->initMap(8);
    // vector<string> files;
    // get_need_file("/data/3Dresults/11d7e2b0-cbc1-49ab-ade1-fdbfa96288d5",files,".las");
    // // files.push_back("/server-w/3DPogress/ea007f52-aee9-421a-a096-7c46aec8dcbb/5da669db-8835-4a92-abcf-d679a267f8db_rect.las");
    // // files.push_back("/server-w/3DPogress/9ef16123-576d-4219-9d4b-a49fff724372/1acf3379-ba91-41cd-8764-31eb9ea5e465_rect.las");
    // // files.push_back("/server-w/3DPogress/9fd13eca-c138-423c-8e3a-5075d2afbb73/28fa05f8-11a6-461d-b577-845e3536d811_rect.las");
    // int count=0;
    // for(auto f : files){
    //     cmap->addMap(f,50);
        
    //     count++;
    //     std::cout<<f<<endl;
    // }
    string source = "/data/3Dresults/830ca390-39ea-4c8b-8e2a-5b80b0b1638d/830ca390-39ea-4c8b-8e2a-5b80b0b1638d.bt";
    std::string src_pc = "/data/3Dresults/830ca390-39ea-4c8b-8e2a-5b80b0b1638d/0afcee6f-5c97-4e9b-a56a-6332b59b2e84/448dbcec-8329-409b-9370-74e6da27d56b_rect.las";

    string output = "/data/3Dresults/830ca390-39ea-4c8b-8e2a-5b80b0b1638d/830ca390-39ea-4c8b-8e2a-5b80b0b1638d_new.bt";
    string newlas = "/data/3Dresults/830ca390-39ea-4c8b-8e2a-5b80b0b1638d/0afcee6f-5c97-4e9b-a56a-6332b59b2e84/0afcee6f-5c97-4e9b-a56a-6332b59b2e84-georeferenced_model-crop.las";

    string pcd_file = "/data/3Dresults/830ca390-39ea-4c8b-8e2a-5b80b0b1638d/0afcee6f-5c97-4e9b-a56a-6332b59b2e84/0afcee6f-5c97-4e9b-a56a-6332b59b2e84.las";
    
    std::vector<Point2d> area{{667128.9375,31859614.5},{667228.9375,3185914.5},{667228.937,3186014.5},{667128.9375,3186014.5}};
    VoxelMap *cmap = new VoxelMap(2,666214.50165395 , 3185982.7673171624,123.07,50);
    cmap->addMap(newlas,50);
    // cmap->updateMap(newlas,area,50);
    // cmap->saveMap(output);
    cmap->octomap2pcd(pcd_file);
    auto afterTime = std::chrono::steady_clock::now();
    double duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
    std::cout<<duration_second<<std::endl;
    return 0;
}