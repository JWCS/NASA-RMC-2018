#include <iostream>
#include <math.h>
#include <cstdlib>
#include <sweep/sweep.hpp>
#include <fstream>
#include <string>

struct coordinates {
  double angle;
  double distance;
  std::int32_t signal_strength;
};



//Controls the LIDAR
class LIDAR{ //: LidarParent
  public:
  sweep::sweep device;
  LIDAR(std::string filelocation);
  ~LIDAR();
  //void setTranslation(double lx, double ly, double lz);
  //void setRotation(double rx, double ry, double rz);
  void scan();
  std::vector<coordinates> getScan();//contains the conversion
};

/*
struct scan {
  std::vector<coordinates> coordinate;
};
*/
