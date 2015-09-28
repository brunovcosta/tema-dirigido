Mat s_image, v_image;
Mat hsv_image;
Mat trunked_image;
Mat colored_image;
Mat canny_image;
vector<Vec4i> hierarchy;
vector<Mat> channels;
int i;
Mat levelCurves(Mat raw_image){
	// hue vai de 0 ~ 180, e nao de 0 ~ 255-----------------------
	//	medianBlur(raw_image,raw_image,9);
	raw_image.convertTo(raw_image,CV_8U);
	resize(raw_image, raw_image, Size(1280, 768));
	normalize(raw_image, raw_image, 0, 255, NORM_MINMAX, CV_8UC1);
	double delta_height = 10;
	trunked_image = raw_image/delta_height;
	trunked_image=trunked_image*delta_height;  // trunca os pixels
	
	s_image = v_image = Mat::ones(raw_image.rows, raw_image.cols, CV_8U);
	s_image = s_image*255,
	v_image = v_image*255;
	//---------------------------------------------------------------------------
	// Empilha canais----------------
	channels.push_back(raw_image);
	channels.push_back(s_image);
	channels.push_back(v_image);
		
	merge(channels, hsv_image);
	//-------------------------------
	// Converte as cores HSV para RGB--------------
	cvtColor(hsv_image, colored_image, CV_HSV2RGB);
	//show(colored_image);
	//---------------------------------------------
	// Aplica detector de bordas canny-----
	Canny(trunked_image, canny_image, 1, 0);
	// show(canny_image);
	//-------------------------------------
	// Encontra os contornos, RETR_TREE -> organiza os contornos em arvore----------------------------
	vector<vector<Point> > contours;
	findContours(canny_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//------------------------------------------------------------------------------------------------
	// Desenha os contornos------------------------------------------------------
	for(i = 0; i < contours.size(); i++)
		drawContours(colored_image, contours, i, Scalar(0, 0, 0), 1, 8, hierarchy);
	
	hierarchy.clear();
	channels.clear();
	raw_image.release();
	trunked_image.release();
	s_image.release();
	v_image.release();
	hsv_image.release();
	canny_image.release();
	return colored_image;
}
