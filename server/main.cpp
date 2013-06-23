#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Communications.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

using namespace cv;
int main()
{
    Mat frame;
    std::vector<int> param=std::vector<int>(2);
    param[0]=CV_IMWRITE_JPEG_QUALITY;
    param[1]= 95;
    char input[10];
    VideoCapture cap(0);
    SocketServer comms("5555");
    sleep(2);
    while(1)
    {
        comms.receiveMessage(input, 10);
        //std::cout << input << std::endl;
        if (strncmp(input, "image", 5)==0)
        {
            cap >> frame;
            //std::cout << "going to send image...\n";
            std::vector<unsigned char> buf;
            imencode(".jpg", frame, buf, param);
            if (comms.sendcompressedframe(buf)<0)
            {
                std::cout << "lost connection to client or send error\n";
            }
            //std::cout << "image sent!\n";
        }
        else if (strncmp(input, "bye", 3)==0)
        {
          std::cout << "exiting\n";
          break;
        }
        memset(input, '0', 10);
    }
    std::cout << "I quit nicely :)\n";
    return 1;
}
