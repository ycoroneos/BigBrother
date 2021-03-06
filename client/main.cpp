#include <iostream>
#include <vector>
#include "Communications.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace cv;


const std::string currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}


int main(int argc, char* argv[])
{
    SocketClient remote("oce.mit.edu", "5555");
    //namedWindow("feed", 1);
    int invalid_count=0;
    while (invalid_count<=3)
    {
        int data_size=0;
        Mat frame;
        //remote.waitForPing();
        std::vector<unsigned int>buffer=remote.getRawFrameData("image");
        //std::cout << buffer.size() << std::endl;
        if (buffer.size()>0)
          frame=imdecode(Mat(buffer), CV_LOAD_IMAGE_COLOR); //Mat constructor takes std::vector<uchar>
        if (!frame.data)
        {
          std::cout << "invalid image\n";
          ++invalid_count;
        }
        else
        {
      //    imshow("feed", frame);
          imwrite("../../../images/image-"+currentDateTime()+".jpg", frame);
          invalid_count=0;
        }
        //waitKey(1);
	sleep(5);
    }
    remote.sendmessage("bye");
    std::cout << "lost connection... probably\n";
    return 0;
}
