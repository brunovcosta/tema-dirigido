#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include<signal.h>

using namespace cv;
using namespace std;

#include "myFileLogger.cpp"

int main(int argc, char* argv[]){
	//Inicia a libfreenect2--------------------------------------------------
	libfreenect2::Freenect2 freenect2;
	libfreenect2::Freenect2Device *dev = 0;
	libfreenect2::PacketPipeline *pipeline = 0;

	if(freenect2.enumerateDevices() == 0){
	    std::cout << "no device connected!" << std::endl;
  		return -1;
	}
	std::string serial = freenect2.getDefaultDeviceSerialNumber();

	pipeline = new libfreenect2::OpenGLPacketPipeline();//CpuPacketPipeline();
    dev = freenect2.openDevice(serial, pipeline);
	
	libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color | libfreenect2::Frame::Ir | libfreenect2::Frame::Depth);
	libfreenect2::FrameMap frames;
	libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4);
	
	dev->setColorFrameListener(&listener);
	dev->setIrAndDepthFrameListener(&listener);
	dev->start();
    
	while (waitKey(33) & 0xFF!=27){
		listener.waitForNewFrame(frames);
		libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
		
		// Carrega imagem-------------------------------------------------------
		Mat raw_image;
		raw_image=cv::Mat(depth->height, depth->width, CV_32FC1, depth->data)/10;
		resize(raw_image, raw_image, Size(1366, 768)); // Redimensiona a imagem
		//show(raw_image);
		//----------------------------------------------------------------------

		// hue vai de 0 ~ 180, e nao de 0 ~ 255-----------------------
		Mat scaled_image = raw_image;
		double delta_height = 10;
		scaled_image.convertTo(scaled_image,CV_8U);
		scaled_image = scaled_image/delta_height;  // trunca os pixels
		scaled_image = scaled_image*delta_height; // trunca os pixels
		//show(scaled_image);
		//------------------------------------------------------------

		// Canais de saturacao e intensidade maximos---------------------------------
		Mat s_image, v_image;
		s_image = v_image = Mat::ones(scaled_image.rows, scaled_image.cols, CV_8U);
		s_image = s_image*255,
		v_image = v_image*255;
		//---------------------------------------------------------------------------

		// Empilha canais----------------
		vector<Mat> channels;
		channels.push_back(scaled_image);
		channels.push_back(s_image);
		channels.push_back(v_image);
			
		Mat hsv_image;
		merge(channels, hsv_image);
		//-------------------------------

		// Converte as cores HSV para RGB--------------
		Mat colored_image;
		cvtColor(hsv_image, colored_image, CV_HSV2RGB);
		//show(colored_image);
		//---------------------------------------------

		// Aplica detector de bordas canny-----
		Mat canny_image;
		Canny(scaled_image, canny_image, 1, 1);
		// show(canny_image);
		//-------------------------------------

		// Encontra os contornos, RETR_TREE -> organiza os contornos em arvore----------------------------
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(canny_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		//------------------------------------------------------------------------------------------------

		// Desenha os contornos------------------------------------------------------
		Mat final_image = colored_image;
		for(int i = 0; i < contours.size(); i++)
			drawContours(final_image, contours, i, Scalar(0, 0, 0), 1, 8, hierarchy);

		namedWindow("MyWindow", WND_PROP_FULLSCREEN);
		setWindowProperty("MyWindow", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
		imshow("MyWindow", final_image);
	
	}
	destroyWindow("MyWindow");
	
	 fprintf(stderr, "Time: %.3f\n", (double)clock()/CLOCKS_PER_SEC);
	//Finaliza o Libfreenect2--------------------------------------------------------------------
	dev->stop();
	dev->close();
	
	return 0;
}
