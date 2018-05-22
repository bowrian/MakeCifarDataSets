#ifndef BINARY_DATASET_H
#define BINARY_DATASET_H
#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "cv.h"
#include "highgui.h"

using namespace std;
using namespace cv;

class BinaDataset
{
public:
	BinaDataset()
	{
		—iHeight = 32;
		_iWidth  = 32;
	}
	~BinaDataset(){}

public:

	void images2BinaryFile(std::string filefolder,std::vector<std::string> & img_list,std::vector<int> & img_labels,std::string filename);
	void mat2Binary(std::string& image_file,int label,FILE *& fp);
	void convertMat2Bin(cv::Mat& image,int label,FILE *& fp);
	//cv::Mat imageReshape(cv::Mat& input);
	std::string getFileName(std::string & filename);
	std::vector<std::string> getFileLists(std::string file_folder);

public:
	int _iHeight;
	int _iWidth;
	
};

#endif //BINARY_DATASET_H