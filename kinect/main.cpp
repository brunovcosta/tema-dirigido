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
#include<signal.h>

using namespace cv;
using namespace std;

#include "myFileLogger.cpp"
#include "levelCurves.cpp"

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
		
		namedWindow("MyWindow", WND_PROP_FULLSCREEN);
		setWindowProperty("MyWindow", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
		imshow("MyWindow", levelCurves(raw_image));
	
	}
	destroyWindow("MyWindow");
	
	//Finaliza o Libfreenect2--------------------------------------------------------------------
	dev->stop();
	dev->close();
	
	return 0;
}
