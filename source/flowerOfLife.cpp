// created by Eelko van Breda, Free Software

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <memory>

#include "figure.hpp"


int main(int argc, const char * argv[]) {
    cv::Mat img(800,800,CV_8UC3,cv::Scalar(255,255,255));
    cv::Point origin(img.cols/2,img.rows/2);

    cv::Scalar red = cv::Scalar(0,0,255);
    cv::Scalar blue = cv::Scalar(255,0,0);
    cv::Scalar green = cv::Scalar(0,255,0);

    Drawing drawing(img, origin, 150);
    //center circle
    drawing.setColor(red);
    drawing.setCenterDot(true);
    
    drawing.createCircle(0,     0,      1);
    //first round
    drawing.setColor(blue);
    drawing.createCircle(0,     1,      1);
    drawing.createCircle(0.866, 0.5,    1); //cos(30) = 0.866
    drawing.createCircle(0.866, -0.5,   1);
    drawing.createCircle(0,     -1,     1);
    drawing.createCircle(-0.866, -0.5,  1);
    drawing.createCircle(-0.866, 0.5,   1);
    //second round
    drawing.setColor(green);
    drawing.createCircle(-1.732, 0,      1); //vesica picis = sqrt(3)

    drawing.draw();

    cv::imshow( "Drawing" ,img);
    cv::waitKey(0);


    cv::destroyWindow("Drawing");

    return 0;
};

