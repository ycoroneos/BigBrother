#include <iostream>
#include <vector>
#include "Communications.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;


int main(int argc, char* argv[])
{
    SocketClient remote("localhost", "5555");
    //namedWindow("feed", 1);
    int i=0;
    while (i<4)
    {
        int data_size=0;
        unsigned char* data;
        Mat frame;
        remote.getRawFrameData("image", data, &data_size);
        //std::cout << rows << " " << cols << " " << type <<  " " << data << std::endl;
        std::cout << data << std::endl;
        std::vector<unsigned char> tbuf(data, data+data_size);
        frame=imdecode(Mat(tbuf), CV_LOAD_IMAGE_COLOR); //Mat constructor takes std::vector<uchar>
        if (!frame.data)
        {
          std::cout << "invalid image\n";
        }
        else
        {
          std::cout << "recieved data\n";
        }
        //getchar();
        //imshow("feed", frame);
        //waitKey(20);
        sleep(2);
        //getchar();
        ++i;
    }
    remote.sendmessage("bye");
    return 0;
}
