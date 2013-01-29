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
    while(comms.bye==false)
    {
      if (comms.sendnow==true)
      {
        cap >> frame;
        comms.sendraw(&frame, sizeof(frame));
        comms.sendnow=false;
      }
    }
    pthread_join(listener, NULL);
    return 1;
}
