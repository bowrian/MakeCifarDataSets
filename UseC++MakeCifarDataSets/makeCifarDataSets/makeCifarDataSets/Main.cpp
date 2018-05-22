#include "BinaryDataset.h"
#include <iostream>
#include <string.h>

using namespace std;

void main(int argc, char const *argv[])
{
	string filefolder = "C:\\Users\\pengl\\Documents\\MakeCifarDataSets\\UseC++MakeCifarDataSets\\datasets\\train";
	BinaDataset binData;
	std::vector<string> fileLists = binData.getFileLists(filefolder); //load file name

	const int size_list = fileLists.size();
	cout << "image count" << size_list << endl;
	std::vector<int> image_labels(size_list,0);  //generator labels, here are all 0
	string binfile = "C:\\Users\\pengl\\Desktop\\data\\data_batch_1";
	binData.images2BinaryFile(filefolder,fileLists,image_labels,binfile);
}