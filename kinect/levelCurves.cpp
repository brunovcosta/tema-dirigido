Mat levelCurves(Mat raw_image){
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
		return final_image;
}
