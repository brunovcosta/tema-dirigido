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
	
	dev->setColorFrameListener(&listener);
	dev->setIrAndDepthFrameListener(&listener);
	dev->start();

	Mat raw_image,final_image;
	//namedWindow("MyWindow", WND_PROP_FULLSCREEN);
	//setWindowProperty("MyWindow", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	
	listener.waitForNewFrame(frames);
	libfreenect2::Frame *depth; 
	depth = frames[libfreenect2::Frame::Depth];
	raw_image=Mat(depth->height, depth->width, CV_32FC1, depth->data)/10;

	Point center,diff;
	while (waitKey(33) & 0xFF!=27){
		listener.waitForNewFrame(frames);
		depth = frames[libfreenect2::Frame::Depth];
		resize(raw_image,raw_image,Size(depth->width,depth->height));
		absdiff(raw_image,Mat(depth->height, depth->width, CV_32FC1, depth->data)/10,final_image);
		//threshold(final_image,final_image,1,255,THRESH_BINARY);
		
		//erode(final_image,final_image,Mat::ones(5,5,CV_32FC1));
		morphologyEx(final_image,final_image,MORPH_OPEN,Mat::ones(5,5,CV_32FC1));
		Moments mm = moments(final_image);
		if(mm.m00>500){
			diff = (Point(mm.m10/mm.m00, mm.m01/mm.m00)+diff-center)/2;
			center=Point(mm.m10/mm.m00, mm.m01/mm.m00);
		}else{
			diff = Point(0,0);
		}
		cvtColor(final_image,final_image,CV_GRAY2RGB);
		circle(final_image, center, 5, Scalar(0,0,128), -1);
		line(final_image, center,center+diff, Scalar(0,128,0), 3);

		raw_image=Mat(depth->height, depth->width, CV_32FC1, depth->data)/10;
		
		listener.release(frames);
		//final_image = levelCurves(raw_image);	
		imshow("MyWindow", final_image);
	}
	destroyWindow("MyWindow");
	raw_image.release();
	final_image.release();
	
	dev->stop();
	dev->close();
	
	return 0;
}
