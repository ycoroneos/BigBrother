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
    VideoCapture cap(0);
    SocketServer comms("5555");
    pthread_create(&listener, NULL, thread_func, &comms);
    //namedWindow("feed", 1);
    sleep(2);
    while(comms.bye==false)
    {
        if (comms.sendnow==true)
        {
            cap >> frame;
            std::vector<unsigned char> buf;
            std::vector<int> param=std::vector<int>(2);
            param[0]=CV_IMWRITE_JPEG_QUALITY;
            param[1]= 95;
            imencode(".jpg", frame, buf, param);
            comms.sendcompressedframe(buf);
            //comms.sendframe(frame.rows, frame.cols, frame.type(), (char*)frame.data);
            comms.sendnow=false;
            std::cout << "sent data\n";
            //std::cout << strlen((char*)frame.data) << std::endl << (char*)frame.data << std::endl;
            //imshow("feed", Mat(frame.rows, frame.cols, frame.type(), (char*)frame.data));
            //waitKey(20);
        }
    }
    pthread_join(listener, NULL);
    return 1;
}
