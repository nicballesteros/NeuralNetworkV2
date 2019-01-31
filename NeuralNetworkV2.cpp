// NeuralNetworkV2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Nic Ballesteros

#include "pch.h"
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>

#define LOG(x) std::cout << x << std::endl;

/* Read all files */

int ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void ReadMNIST_File(std::string filename, int NumberOfImages, int DataOfAnImage, std::vector<std::vector<double>> &arr)
{
	arr.resize(NumberOfImages, std::vector<double>(DataOfAnImage));
	std::ifstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		LOG(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);

		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);

		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);

		for (int i = 0; i < number_of_images; ++i)
		{
			for (int r = 0; r < n_rows; ++r)
			{
				for (int c = 0; c < n_cols; ++c)
				{
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					arr[i][(n_rows*r) + c] = (double)temp;
				}
			}
		}
	}
	else {
		std::cout << "Images file could not be opened" << std::endl;
	}
}

void readMNIST_Label(std::string filename, std::vector<double> &vec)
{
	std::ifstream file(filename, std::ios::binary);

	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;

		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);

		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);

		for (int i = 0; i < number_of_images; ++i)
		{
			unsigned char temp = 0;

			file.read((char*)&temp, sizeof(temp));

			vec.push_back((double)temp);
		}
	}
}

/* a sigmoid function */

double sigmoid(double x) {
	double result = 0.0;

	result = 1 / (1 + exp(-x));

	return result;
}

int main()
{
	srand(time(0));

	int numberOfRows = 4;
	int numberOfInputNodes = 784;
	int numberOfRowTwo = 16;
	int numberOfRowThree = 16;
	int numberOfOutputs = 10;

	/* initialize a size array */
	std::vector<int> numberOfNodesInRow;

	numberOfNodesInRow.push_back(numberOfInputNodes);
	numberOfNodesInRow.push_back(numberOfRowTwo);
	numberOfNodesInRow.push_back(numberOfRowThree);
	numberOfNodesInRow.push_back(numberOfOutputs);

	/* a vector to hold all the weight matrixes */
	std::vector<Eigen::MatrixXd> weightMatrixes(numberOfRows - 1);

	double randomExtrema = 10.0;

	for (int i = 0; i < (numberOfRows - 1); i++) {
		Eigen::MatrixXd s = Eigen::MatrixXd::Random(numberOfNodesInRow[i],numberOfNodesInRow[i + 1]);
		
		s *= randomExtrema;

		weightMatrixes[i] = s;
	}

	/* an array to hold all the bias vectors */

	std::vector<Eigen::VectorXd> biasVectors(numberOfRows);

	for (int i = 0; i < numberOfRows; i++) {
		biasVectors[i] = Eigen::VectorXd::Random(numberOfNodesInRow[i]);

		biasVectors[i] *= randomExtrema;
	}

	/* an array to hold all activataion vectors*/

	std::vector<Eigen::VectorXd> activationVectors(numberOfRows);

	for (int i = 0; i < numberOfRows; i++) {
		activationVectors[i] = Eigen::VectorXd::Zero(numberOfNodesInRow[i]);
	}

	/* load file */

	std::vector<std::vector<double>> allImages;

	std::string MNIST_fileDir = "train\\train-images.idx3-ubyte";
	std::string MNIST_labelDir = "train\\train-labels.idx1-ubyte";
	
	int numberOfImages = 60000;
	int numberOfPixels = 784;

	ReadMNIST_File(MNIST_fileDir, numberOfImages, numberOfPixels, allImages);
	/* load labels */

	std::vector<double> labels;

	readMNIST_Label(MNIST_labelDir, labels);

	/*
	for (int i = 0; i < numberOfRows; i++) {
		LOG(weightMatrixes[i]);
	}*/




	/*
	Eigen::Matrix3d s;
	s = Eigen::Matrix3d::Random();


	s *= 10;

	std::cout << s << std::endl;*/

	//std::cout << s.size() << std::endl;
	
}
