#include "NavX.h"
//#include <TimeStamp.h>
#include <iostream>
#include "DeadReckoning.h"
#include <stdio.h>
#include <stdlib.h>
//#include <AHRS.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <signal.h>

volatile sig_atomic_t sflag = 0;

void handle_sig(int sig)
{
    sflag = 1;
}


int main(int argc, char *argv[]) {
    std::cout << "Program Executing\n";
    signal(SIGINT, handle_sig);
    
    NavX com = NavX("/dev/ttyACM0");
    //AHRS com = AHRS("/dev/ttyACM0");
    
    printf("Initializing\n\n");


    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    std::cout << "|  Yaw  |  Roll  |  Pitch  |  Time  |" << std::endl;

    while( 1 == 1){
        std::cout << std::fixed << std::setprecision(5) << com.GetYaw() << "      " << com.GetRoll() << "   " << com.GetPitch() << "     " << com.GetLastSensorTimestamp() << '\r' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(125));
        if(sflag){
            sflag = 0;
            com.Close();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
    
    }
    printf("\nExit Caught... Closing device.\n");

    return 0;
}
