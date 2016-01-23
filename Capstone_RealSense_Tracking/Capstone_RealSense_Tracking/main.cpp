/*
2015-2016 Intel-Cornell Cup Competition
UMass Lowell Spring 2016 Engineering Capstone Project
Intel RealSense R200 3D Camera
RSSDK API paired with OpenCV 3.0.0 API

Team: Andrew Cantwell
	  Mike Connors
	  Matt Derman
	  Mike Meyerdirk
	  Derrick Wakanya
 */

#include "pxcsensemanager.h"
#include <pxcsensemanager.h>	// RealSense API
#include <opencv2\opencv.hpp>	// OpenCV API
#include <iostream>

/* F u n c t i o n  P r o t o t y p e s */
cv::Mat PXCImage2CVMat(PXCImage *pxcImage, PXCImage::PixelFormat format);

int main(int argc, char* argv[]){

	cv::Size frameSize = cv::Size(640, 480);
	float frameRate = 60;

	// Create OpenCV windows to display streams
	cv::namedWindow("IR Stream", cv::WINDOW_NORMAL);
	cv::namedWindow("RGB Stream", cv::WINDOW_NORMAL);
	cv::namedWindow("Depth Stream", cv::WINDOW_NORMAL);

	cv::Mat frameIR = cv::Mat::zeros(frameSize, CV_8UC1);
	cv::Mat frameColor = cv::Mat::zeros(frameSize, CV_8UC3);
	cv::Mat frameDepth = cv::Mat::zeros(frameSize, CV_8UC1);

	// Initialize RealSense Manager
	PXCSenseManager *pxcSenseManager = PXCSenseManager::CreateInstance();

	// Enable the different streams to be used
	pxcSenseManager->EnableStream(PXCCapture::STREAM_TYPE_IR, frameSize.width, frameSize.height, frameRate);
	pxcSenseManager->EnableStream(PXCCapture::STREAM_TYPE_COLOR, frameSize.width, frameSize.height, frameRate);
	pxcSenseManager->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, frameSize.width, frameSize.height, frameRate);

	// Initialize the pipeline
	pxcSenseManager->Init();

	bool running = true;
	
	while (running){

		//Acquire all frames from the R200
		pxcSenseManager->AcquireFrame();
		PXCCapture::Sample *sample = pxcSenseManager->QuerySample();

		// Convert each frame into an OpenCV Image
		frameIR = PXCImage2CVMat(sample->ir, PXCImage::PIXEL_FORMAT_Y8);
		frameColor = PXCImage2CVMat(sample->color, PXCImage::PIXEL_FORMAT_RGB24);
		PXCImage2CVMat(sample->depth, PXCImage::PIXEL_FORMAT_DEPTH_F32).convertTo(frameDepth, CV_8UC1);

		// Display images
		cv::imshow("IR", frameIR);
		cv::imshow("Color", frameColor);
		cv::imshow("Depth", frameDepth);

		// Check for user input -- (ESC) key is 27 in ASCII
		int key = cv::waitKey(1);
		if (key == 27)
			running = false;

		// Release the memory from the frames
		pxcSenseManager->ReleaseFrame();
	}

	// Release the memory from the RealSense Manager
	pxcSenseManager->Release();

	return 0;
}

/* F u n c t i o n  D e f i n i t i o n s */
cv::Mat PXCImage2CVMat(PXCImage *pxcImage, PXCImage::PixelFormat format){

	PXCImage::ImageData data;
	pxcImage->AcquireAccess(PXCImage::ACCESS_READ, format, &data);

	int width = pxcImage->QueryInfo().width;
	int height = pxcImage->QueryInfo().height;

	if (!format)
		format = pxcImage->QueryInfo().format;

	int type;

	if (format == PXCImage::PIXEL_FORMAT_Y8)
		type = CV_8UC1;
	else if (format == PXCImage::PIXEL_FORMAT_RGB24)
		type = CV_8UC3;
	else if (format == PXCImage::PIXEL_FORMAT_DEPTH_F32)
		type = CV_32FC1;

	cv::Mat ocvImage = cv::Mat(cv::Size(width, height), type, data.planes[0]);

	pxcImage->ReleaseAccess(&data);
	
	return ocvImage;
}