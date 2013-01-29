#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cvblob/cvblob.h"
#include "Communications.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
using namespace cv;

extern "C" void *thread_func(void* arg);

class Ballfinder
{
private:
    //variables
    bool show;
    bool send;
    VideoCapture cap;
    Mat frame, HSV;
    std::map<cvb::CvLabel, cvb::CvBlob*>::iterator iter;
    SocketServer* comms;
    pthread_t listener;

    //functions
    string convertInt(int number);
public:
    //variables
    Scalar greenmin=Scalar(80/2, 104, 0);
    Scalar greenmax=Scalar(158/2,255,255);
    Scalar redmin[2]={Scalar(340,151,0), Scalar(0,151,0)};
    Scalar redmax[2]={Scalar(360,255,255), Scalar(10, 255, 255)};
    int areafilter=500;
    //functions
    Ballfinder(int camera, string portnum, bool show_video);
    ~Ballfinder();
    void findballs();
    void show_raw_video();
    void initserver(string port);
    void runserver();
};
