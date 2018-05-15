//g++ decawaveDriver.cpp -std=c++11 -lserial decawave.cpp


#include "decawave.h"

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include <serial/serial.h>

int main(){
  Decawave piTag;
  //if error, may need a delay?
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  piTag.updateSamples();
  coordinate tagPos= piTag.getPos();
  std::cout<<std::endl<<" "<<tagPos.x<<" "<<tagPos.y<<" "<<std::endl;
  return 0;
}
