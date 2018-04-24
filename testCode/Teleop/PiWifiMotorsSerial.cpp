// Runs the motors on the Pi with Telecomm
// Receives commands from Wifi
// Sends to arduino using Telecomm

#include <string>
#include <vector>

#include "serial/serial.h"

#include "Telecomm.h"
//#include "Formatter.hpp"

int main(){
  // Initialize classes
  // Telecomm
  Telecomm comm("192.168.1.50",5001,5001);
  comm.setFailureAction(false);
  comm.setBlockingTime(0,0);
  if(comm.status() != 0){
    printf("Error: %s\n", comm.verboseStatus().c_str());
    return comm.status();
  }
  
  /* // Formatter
  val_fmt motor_fmt = {
    "Motors", // string data_t
    '!', // Arbitrary symbol
    3, // Number of bytes/chars to send
    0, // Min_val (sending)
    200, // Max_val (sending)
    100, // Offset
    100
  };
  Formatter fmt = Formatter({motor_fmt});
*/
  // Serial
  std::string port = "/dev/ttyACM0"; // could be something else
  serial::Serial arduino(port, 9600);

  // Loop
  while(1){
    comm.update();

    // Assume Arduino keeps track of states & just updates, but pi should keep track too
    if(comm.recvAvail()){
      std::string msg = comm.recv();
      if(arduino.isOpen()){
        arduino.write(msg);
      }
    }

    while(comm.isCommClosed()){
      printf("Rebooting Connection\n");
      comm.reboot();
    }
  }
  return 0;
}
