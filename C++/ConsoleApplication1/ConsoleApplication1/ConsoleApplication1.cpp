#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 1000;
int ratio = 3;
int const max_ratio = 50;
int kernel_size = 5;
int const max_kernel_size = 10;
int blur_size = 3;
int max_blur = 100;
char* window_name = "Edge Map";
float const scaling_factor = 1.0;

/**
* @function CannyThreshold
* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
*/
void CannyThreshold(int, void*)
{
	/// Reduce noise with a kernel 3x3
	blur(src_gray, detected_edges, Size(blur_size, blur_size));

	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);
}

void reduceColorSpace() { //http://answers.opencv.org/question/27808/how-can-you-use-k-means-clustering-to-posterize-an-image-using-c/rows
	Mat toUse(src.size(), src.type());
	blur(src, toUse, Size(4, 4));

	Mat samples(src.rows * src.cols, 3, CV_32F); //Resize from (1920)*(1080)*(3) -> (1920*1080) * 3

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			for (int z = 0; z < 3; z++) {
				samples.at<float>(y * src.cols + x, z) = toUse.at<Vec3b>(y, x)[z];
			}
		}
	}

	int totalClusters = 3;
	int attempts = 5;
	Mat labels;
	Mat centers;
	kmeans(samples, totalClusters, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 100, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

	Mat out(src.size(), src.type());

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			int whichCluster = labels.at<int>(y * src.cols + x, 0);
			out.at<Vec3b>(y, x)[0] = centers.at<float>(whichCluster, 0);
			out.at<Vec3b>(y, x)[1] = centers.at<float>(whichCluster, 1);
			out.at<Vec3b>(y, x)[2] = centers.at<float>(whichCluster, 2);
		}
	}

	imshow("clustered image", out);
	//waitKey(0);
}

void process(int, void*) {
	//CannyThreshold(0, 0);
	reduceColorSpace();
}

/** @function main */
int main(int argc, char** argv)
{
	std::cout << "Running" << std::endl;
	waitKey(0);
	/// Load an image
	//src = imread("scenery_20smaller.jpg");
	src = imread("scenery.jpg");
	Mat resized(Size(scaling_factor * src.cols, scaling_factor * src.rows), src.type());
	resize(src, resized, resized.size(), 0, 0, INTER_LINEAR);
	src = resized;

	if (!src.data)
	{
		return -1;
	}

	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create a window
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, process);
	createTrackbar("Ratio:", window_name, &ratio, max_ratio, process);
	createTrackbar("Kernel Size:", window_name, &kernel_size, max_kernel_size, process);
	createTrackbar("Blur Size:", window_name, &blur_size, max_blur, process);

	/// Show the image
	process(0, 0);

	/// Wait until user exit program by pressing a key
	waitKey(0);

	return 0;
}