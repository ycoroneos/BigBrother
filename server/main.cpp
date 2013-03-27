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
///////////
pthread_t listener;
///////////

extern "C" void *thread_func(void* arg)
{
    static_cast<SocketServer *>(arg)->waitmessage();
}


int main()
{
    Mat frame;
    std::vector<int> param=std::vector<int>(2);
    param[0]=CV_IMWRITE_JPEG_QUALITY;
    param[1]= 95;
    char input[10];
    VideoCapture cap(0);
    SocketServer comms("5555");
    //pthread_create(&listener, NULL, thread_func, &comms);
    sleep(2);
    while(strncmp(input, "bye", 3)!=0)
    {
        comms.receiveMessage(input, 10);
        //std::cout << input << std::endl;
        if (strncmp(input, "image", 5)==0)
        {
            cap >> frame;
            std::vector<unsigned char> buf;
            imencode(".jpg", frame, buf, param);
            if (comms.sendcompressedframe(buf)<0)
            {
                std::cout << "lost connection to client or send error\n";
                //comms.Listen();
            }
        }
        memset(input, '0', 10);
    }
    //pthread_join(listener, NULL);
    std::cout << "I quit nicely :)\n";
    return 1;
}
