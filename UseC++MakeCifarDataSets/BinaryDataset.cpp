#include "BinaryDataset.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void BinaDataset::images2BinaryFile(
	std::string filefolder,
	std::vector<std::string> & img_list,
	std::vector<int> & img_labels,
	std::string filename)
{
	const int size_list = img_list.size();

	FILE *fp = fopen(filename.c_str(),"wb");
	if (fp == NULL)
	{
		cout << "open error" << endl;
		fclose(fp);
		return;
	}

	for (int idx = 0; idx < size_list; ++idx)
	{
		std::string currentPath = filefolder + "\\";
		currentPath += img_list[idx];
		mat2Binary(currentPath,img_labels[idx],fp);
#if 1
		cout << "image" << idx+1 << "saved." <<endl;
#endif
	}
	fclose(fp);
}
	

void BinaDataset::mat2Binary(
	std::string& image_file,
	int label,
	FILE *& fp)
{
	cv::Mat image = cv::imread(image_file,IMREAD_UNCHANGED);
	if(!image.data)
	{
		cout << "image" << getFileName(image_file) << "load failed!" << endl;
	}
	else
	{
		if (image.channels() == 1)
		{
			cv::cvColor(image,image,CV_GRAY2RGB);
		}
		else
		{
			cv::cvColor(image,image,cv_BGR2RGB);
		}

		cv::Mat image_reshaped;

		cv::resize(image,image_reshaped,cv::Size(_iWidth,_iHeight),CV_INTER_LINEAR);
		convertMat2Bin(image_reshaped,label,fp);

	}
}
	
void BinaDataset::convertMat2Bin(
	cv::Mat& image,
	int label,
	FILE *& fp)
{
	fwrite(&label,sizeof(char),1,fp);
	int pixelCount = image.rows * image.cols;
	char * pData = (char*)image.data;

	for (int i = 0; i < pixelCount; i++)
	{
		fwrite(&pData[i*3], sizeof(char),1,fp); //R
	}

	for (int i = 0; i < pixelCount; i++)
	{
		fwrite(&pData[i*3+1], sizeof(char),1,fp); //G
	}
	for (int i = 0; i < pixelCount; i++)
	{
		fwrite(&pData[i*3+2], sizeof(char),1,fp); //B
	}
//	delete pData;


}
	
//cv::Mat imageReshape(cv::Mat& input){}
	
std::string BinaDataset::getFileName(std::string & filename)
{
	int iBeginIndex = filename.find_last_of("\\") + 1;
	int iEndIndex = filename.lenght();

	return filename.substr(iBeginIndex,iEndIndex,-iBeginIndex);
}
	
std::vector<std::string> BinaDataset::getFileLists(std::string file_folder)
{
	file_folder += "/*.*";
	const char * mystr = file_folder.c_str();
	std::vector<std::string> flist;
	std::string lineStr;
	std::vector<std::string> extendName;
	extendName.push_back("jpg");
	extendName.push_back("JPG");
	extendName.push_back("bmp");
	extendName.push_back("png");
	extendName.push_back("gif");

	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	wchar_t fn[1000];
	mbstowcs(fn,mystr,999);
	file = FindFirstFile(fn,&fileData);
	FindNextFile(file,&fileData);
	while(FindNextFile(file,&fileData))
	{
		wcstombs(line,(const wchar_t*)fileData.cFileName,259);
		lineStr = line;
		//remove the files which are not images
		for (int i = 0; i < 4; i++)
		{
			if (lineStr.find(extendName[i])<999)
			{
				flist.push_back(lineStr);
				break;
			}
		}
	}

	return flist;

}
