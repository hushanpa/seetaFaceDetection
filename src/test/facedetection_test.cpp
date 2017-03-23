/*
*
* This file is part of the open-source SeetaFace engine, which includes three modules:
* SeetaFace Detection, SeetaFace Alignment, and SeetaFace Identification.
*
* This file is an example of how to use SeetaFace engine for face detection, the
* face detection method described in the following paper:
*
*
*   Funnel-structured cascade for multi-view face detection with alignment awareness,
*   Shuzhe Wu, Meina Kan, Zhenliang He, Shiguang Shan, Xilin Chen.
*   In Neurocomputing (under review)
*
*
* Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
* Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
*
* The codes are mainly developed by Shuzhe Wu (a Ph.D supervised by Prof. Shiguang Shan)
*
* As an open-source face recognition engine: you can redistribute SeetaFace source codes
* and/or modify it under the terms of the BSD 2-Clause License.
*
* You should have received a copy of the BSD 2-Clause License along with the software.
* If not, see < https://opensource.org/licenses/BSD-2-Clause>.
*
* Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems.
*
* Note: the above information must be kept whenever or wherever the codes are used.
*
*/
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <WinSock.h>
 
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;

#include "face_detection.h"

using namespace std;

////////////////////////////////////////////////
#if (defined(__WIN32__) || defined(_WIN32)) && !defined(IMN_PIM)
// For Windoze, we need to implement our own gettimeofday()
#if !defined(_WIN32_WCE)
#include <sys/timeb.h>
#endif
int gettimeofday(struct timeval* tp, int* /*tz*/) {
#if defined(_WIN32_WCE)
	/* FILETIME of Jan 1 1970 00:00:00. */
	static const unsigned __int64 epoch = 116444736000000000LL;
	FILETIME file_time;
	SYSTEMTIME system_time;
	ULARGE_INTEGER ularge;
	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;
	tp->tv_sec = (long)((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
#else
	static LARGE_INTEGER tickFrequency, epochOffset;
	// For our first call, use "ftime()", so that we get a time with a proper epoch.
	// For subsequent calls, use "QueryPerformanceCount()", because it's more fine-grain.
	static bool isFirstCall = true;
	LARGE_INTEGER tickNow;
	QueryPerformanceCounter(&tickNow);
	if (isFirstCall) {
		struct timeb tb;
		ftime(&tb);
		tp->tv_sec = tb.time;
		tp->tv_usec = 1000 * tb.millitm;
		// Also get our counter frequency:
		QueryPerformanceFrequency(&tickFrequency);
		// And compute an offset to add to subsequent counter times, so we get a proper epoch:
		epochOffset.QuadPart
			= tb.time*tickFrequency.QuadPart + (tb.millitm*tickFrequency.QuadPart) / 1000 - tickNow.QuadPart;
		isFirstCall = false; // for next time
	}
	else {
		// Adjust our counter time so that we get a proper epoch:
		tickNow.QuadPart += epochOffset.QuadPart;
		tp->tv_sec = (long)(tickNow.QuadPart / tickFrequency.QuadPart);
		tp->tv_usec = (long)(((tickNow.QuadPart % tickFrequency.QuadPart) * 1000000L) / tickFrequency.QuadPart);
	}
#endif
	return 0;
}
#endif



#if 1
int main(int argc, char** argv) {
	/*
	if (argc < 3) {
		cout << "Usage: " << argv[0]
			<< " image_path model_path"
			<< endl;
		return -1;
	}
	*/


	const char* img_path = "..\\..\\data\\0_1_1.jpg";		//argv[1];
	seeta::FaceDetection detector("..\\..\\model\\seeta_fd_frontal_v1.0.bin");		//(argv[2]);

	detector.SetMinFaceSize(40);
	//detector.SetMaxFaceSize(200);
	detector.SetScoreThresh(2.f);
	detector.SetImagePyramidScaleFactor(0.6f);
	detector.SetWindowStep(4, 4);

	cv::Mat img = cv::imread(img_path, cv::IMREAD_UNCHANGED);
	cv::Mat img_gray;

	if (img.channels() != 1)
		cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	else
		img_gray = img;
	cv::Mat img_scale;
	cv::resize(img_gray, img_scale, cv::Size(640, 480));

	seeta::ImageData img_data;
	img_data.data = img_scale.data;
	img_data.width = img_scale.cols;
	img_data.height = img_scale.rows;
	img_data.num_channels = 1;

	struct timeval tpstart, tpend;
	float timeuse;
	gettimeofday(&tpstart, NULL);

	

	long t0 = cv::getTickCount();
	cout << "1"<< endl;
	std::vector<seeta::FaceInfo> faces = detector.Detect(img_data);
	cout << "2"<< endl;
	long t1 = cv::getTickCount();
	double secs = (t1 - t0) / cv::getTickFrequency();
	cout << cv::getTickFrequency() << endl;
	gettimeofday(&tpend, NULL);
	timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
	timeuse /= 1000000;
	printf("Used Time:%f\n ", timeuse);

	cout << "Detections takes " << secs << " seconds " << endl;
#ifdef USE_OPENMP
	cout << "OpenMP is used." << endl;
#else
	cout << "OpenMP is not used. " << endl;
#endif

#ifdef USE_SSE
	cout << "SSE is used." << endl;
#else
	cout << "SSE is not used." << endl;
#endif

	cout << "Image size (wxh): " << img_data.width << "x"
		<< img_data.height << endl;

	cv::Rect face_rect;
	int32_t num_face = static_cast<int32_t>(faces.size());

	for (int32_t i = 0; i < num_face; i++) {
		double scale = img.rows*1.0 / img_scale.rows;
		face_rect.x = cvRound(faces[i].bbox.x*scale);
		face_rect.y = cvRound(faces[i].bbox.y*scale);
		face_rect.width = cvRound(faces[i].bbox.width*scale);
		face_rect.height = cvRound(faces[i].bbox.height*scale);
		cv::rectangle(img, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);
		
		face_rect.x = faces[i].bbox.x;
		face_rect.y = faces[i].bbox.y;
		face_rect.width = faces[i].bbox.width;
		face_rect.height = faces[i].bbox.height;
		cv::rectangle(img_scale, face_rect, CV_RGB(255, 255, 255), 2, 8, 0);
	}

	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image", img);
	cv::namedWindow("detect image", cv::WINDOW_AUTOSIZE);
	cv::imshow("detect image", img_scale);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

#else

int main(int argc, char** argv) {

	
	seeta::FaceDetection detector("..\\..\\model\\seeta_fd_frontal_v1.0.bin");		//(argv[2]);

	detector.SetMinFaceSize(40);
	detector.SetMaxFaceSize(200);
	detector.SetScoreThresh(2.f);
	detector.SetImagePyramidScaleFactor(0.6f);
	detector.SetWindowStep(4, 4);

	cv::Mat img;
	cv::Mat img_gray;
	cv::Mat img_scale;
	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("detect image", cv::WINDOW_AUTOSIZE);

	VideoCapture capture("../../../2.flv");
	if (!capture.isOpened())	return -1;
	while (1)
	{
		capture.read(img);
		if (img.empty())
		{
			continue;
		}
		if (img.channels() != 1)
			cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
		else
			img_gray = img;

		cv::resize(img_gray, img_scale, cv::Size(640,480));

		seeta::ImageData img_data;
		img_data.data = img_scale.data;
		img_data.width = img_scale.cols;
		img_data.height = img_scale.rows;
		img_data.num_channels = 1;


		long t0 = cv::getTickCount();
		std::vector<seeta::FaceInfo> faces = detector.Detect(img_data);
		long t1 = cv::getTickCount();
		double secs = (t1 - t0) / cv::getTickFrequency();
		int msecs = (int)(secs * 1000);
		cout << "Detections takes " << msecs << " ms " << endl;
#ifdef USE_OPENMP
		cout << "OpenMP is used." << endl;
#else
		cout << "OpenMP is not used. " << endl;
#endif

#ifdef USE_SSE
		cout << "SSE is used." << endl;
#else
		cout << "SSE is not used." << endl;
#endif

		cout << "Image size (wxh): " << img_data.width << "x"
			<< img_data.height << endl;

		cv::Rect face_rect;
		int32_t num_face = static_cast<int32_t>(faces.size());

		for (int32_t i = 0; i < num_face; i++) {
			double scale = img.rows*1.0 / img_scale.rows;
			face_rect.x = cvRound(faces[i].bbox.x*scale);
			face_rect.y = cvRound(faces[i].bbox.y*scale);
			face_rect.width = cvRound(faces[i].bbox.width*scale);
			face_rect.height = cvRound(faces[i].bbox.height*scale);
			cv::rectangle(img, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);

			face_rect.x = faces[i].bbox.x;
			face_rect.y = faces[i].bbox.y;
			face_rect.width = faces[i].bbox.width;
			face_rect.height = faces[i].bbox.height;
			cv::rectangle(img_scale, face_rect, CV_RGB(255, 255, 255), 2, 8, 0);
		}


		cv::imshow("input image", img);
		cv::imshow("detect image", img_scale);
		

		cv::waitKey(1);
	}

	
	cv::destroyAllWindows();
}


#endif