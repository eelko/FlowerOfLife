#pragma once

#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

#include "json.hpp"
using json = nlohmann::json;

#include <Magick++.h>


void writeJsonToDisk(json& myJason, const char* filename){
    std::ofstream out(filename);
    out << myJason.dump(3);
    out.close();
}

cv::Mat jsonToMat(nlohmann::json& myJson, cv::Scalar color = cv::Scalar(255,255,255)){
    cv::Mat displayMat(512, 512, CV_32FC3, cv::Scalar(0,0,0));
    int v_pos = 25;
    for (auto it = myJson.begin(); it != myJson.end(); ++it)
    {
        std::string line = it.key() + " =  " + to_string(it.value());
        cv::putText(displayMat, line, cv::Point(5,v_pos), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, color, 1);
        v_pos +=25;
    }
    return displayMat;
}

class InputParser{
    public:
        InputParser (int &argc,const char * argv[]){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};


inline bool readImageFromDisk(cv::Mat& inputImage, std::string imageFileName){

    if(imageFileName.empty())
        return false;

    inputImage = cv::imread(imageFileName,cv::IMREAD_ANYDEPTH | cv::IMREAD_COLOR);

    if( !inputImage.data )
        return false;

    LOG(INFO) <<"read " << imageFileName << " from disk..." << std::endl;
    return true;
}

std::string remove_extension(const std::string& filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot); 
}

//Note that this function does not copy the data. If the magik image is released before you use the Mat image, result is SEGFAULT
Magick::Image Mat2Magick(cv::Mat& src)
{
   Magick::Image mgk(src.cols, src.rows, "BGR", Magick::CharPixel, (char *)src.data);
   return mgk;
}