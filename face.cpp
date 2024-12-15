#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

string frontface = "haarcascade_frontalface_default.xml";
CascadeClassifier faceCascade;

int main() 
{
	VideoCapture capture = VideoCapture(0);
	faceCascade.load(frontface);
	Mat camera, gray, mosaic;
	int mosaic_level = 15;
	vector<Rect>faces;
	while (capture.read(camera)){
		if (waitKey(10) == 27){
			break; //key:Esc
		}
		cvtColor(camera, gray, COLOR_BGR2GRAY);
		faceCascade.detectMultiScale(gray, faces);
		if (faces.size() > 0){
			for (int i = 0; i < faces.size(); i++){
				int x = faces[i].tl().x;
				int y = faces[i].tl().y;
				int width = faces[i].width;
				int height = faces[i].height;

				mosaic = camera(Range(y, y + height), Range(x, x + width));
				resize(mosaic, mosaic, Size(mosaic.rows / mosaic_level, mosaic.cols / mosaic_level), INTER_LINEAR);
				resize(mosaic, mosaic, Size(width, height), INTER_NEAREST);
				mosaic.copyTo(camera(Range(y, y + height), Range(x, x + width)));
			}
		}
		imshow("test", camera);
		//imshow("test2", mosaic);
	}
	return 0;
}