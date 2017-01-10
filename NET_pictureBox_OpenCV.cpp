///////////////////////////////////////////////////////////////
//How to get Opencv Mat image into .NET Framework pictureBox.//
///////////////////////////////////////////////////////////////

//First,you should Mat convert to CV_32S.

Mat src = Mat(x,y,CV_32S);//
//OR
cvtcolor(src,dst,CV_32S);

//Function to convert image.

void DrawCVImage(System::Windows::Forms::Control^ control, cv::Mat& colorImage)
{
	System::Drawing::Graphics^ graphics = control->CreateGraphics();
	System::IntPtr ptr(colorImage.ptr());
	System::Drawing::Bitmap^ b
		= gcnew System::Drawing::Bitmap(colorImage.cols, colorImage.rows, colorImage.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
	System::Drawing::RectangleF rect(0, 0, control->Width, control->Height);
	graphics->DrawImage(b, rect);
	delete graphics;
}

//code to exchange.

DrawCVImage(pictureBox1,dst);
