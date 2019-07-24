/**
 * figure baseclass
 */
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>

using namespace std;

class Figure
{
protected: 
    cv::Point _origin = cv::Point(0,0);
    double _size = 1;
    double _x = 0;
    double _y = 0;
    cv::Scalar _color = cv::Scalar(0,0,0);
    int _thickness = 1;
    int _lineType = cv::LINE_8;
    bool _dot = false;
public:

    Figure(double x, double y, double size, cv::Point origin, cv::Scalar color, int thickness, int lineType):_x(x), _y(y), _size(size), _origin(origin),_color(color),_thickness(thickness),_lineType(lineType){}
    virtual ~Figure(){};
    virtual void draw(cv::Mat& destination) = 0;
    virtual void setCenterDot(bool dot){
        _dot = dot;
    }

};

class Circle : public Figure
{
    public:

    Circle(double x, double y, double size, cv::Point origin, cv::Scalar color = cv::Scalar(0,0,0), int thickness = 1, int lineType = cv::LINE_8):Figure(x,y,size,origin,color,thickness,lineType){}
    void draw(cv::Mat& destination){
        cv::Point pos(_origin.x + _x, _origin.y - _y);
        cv::circle(destination,pos,_size,_color,_thickness, _lineType);
        if(_dot){
            cv::circle(destination,pos,1,_color,_thickness*-1, _lineType);
        }
    }
};



class Drawing
{
    protected:
    cv::Mat _drawing;
    cv::Point _origin;
    std::vector<std::shared_ptr<Figure>> _figures;
    int _unit;
    cv::Scalar _color = cv::Scalar(0,0,0);
    int _thickness = 1;
    int _lineType = cv::LINE_8;
    bool _dot = false;

    public:
    Drawing(cv::Mat img, cv::Point origin, int unit = 10):_origin(origin),_unit(unit){
        _drawing = img;
    }
    void draw(){
        for (auto figure : _figures) {
            figure->draw(_drawing);
        }
    }
    virtual void setColor(cv::Scalar color){
        _color = color;
    }
    virtual void setCenterDot(bool dot){
        _dot = dot;
    }
    void createCircle(double x, double y, double size){
        std::shared_ptr<Circle> circle = std::make_shared<Circle>(_unit*x,_unit*y,_unit*size,_origin,_color,_thickness,_lineType);
        if(_dot){
            circle->setCenterDot(true);
        }
        _figures.push_back(circle);
    }
    

};


    // virtual void setPos(double x, double y){
    //     _x = x;
    //     _y = y;
    //     }
    // virtual void setOrigin(cv::Point origin){
    //     _origin=origin;
    //     }
    // virtual void setSize(double size){
    //     _size=size;
    // }