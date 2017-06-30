// using to show view focus program.
#include <string>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include <random>
#include<vector>
#include<windows.h> 
using namespace cv;
using namespace std;
 
string regular_pool[2] = { "random", "normal" };
string color_pool[3] = { "red", "green", "blue" };
int num_pool[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
string shape_pool[2] = { "rectangle", "circle" };

void start_display(string cavas, const Mat& bg, string regular, string color, int num, string shape,int waittime,Mat& cartton);

void show_highlight(string cavas, const Mat& bg, int x, int y, string color, string shape, int size,Mat& bg_tmp,Mat& cartoon);

int main(int argc, char* argv[])
{
	string imgpath = "../a.jpg";
	Mat img_cartoon = imread(imgpath);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	cv::namedWindow("bg", CV_WINDOW_FULLSCREEN);
	cv::moveWindow("bg", 0, 0);
	Mat background_cavas = Mat::zeros(cy-40, cx, CV_8UC3);
	string regular = "random";
	string color = "red";
	string shape = "img";
	int waittime = 500;
	start_display("bg", background_cavas, regular, color, 4, shape, waittime,img_cartoon);

	return 0;
}

void start_display(string cavas, const Mat& bg, string regular, string color, int num, string shape,int waittime,Mat& cartoon)
{
	int W = bg.cols;
	int H = bg.rows;
	static int highlight_id = 0;
	int hl_x;
	int hl_y;
	//obtain the highlight position -- grid[x][y] ,where then display a color shape
	if (regular == "random")
	{
		while (1)
		{
			highlight_id = rand() % (num*num);
			hl_y = highlight_id / num;
			hl_x = highlight_id%num;

			int size = min(W / num, H / num);
			int x = W / (num * 2) + hl_x*W / num;
			int y = H / (num * 2) + hl_y*H / num;
			Mat bg_tmp;
			show_highlight(cavas, bg, x, y, color, shape, size,bg_tmp,cartoon);
			imshow(cavas, bg_tmp);			
			char a = waitKey(waittime);
			if (a == 'q')
			{
				break;
			}
		}

	}
	else if (regular == "normal")
	{
		while (1)
		{
			highlight_id %= (num*num);
			hl_y = highlight_id / num;
			hl_x = highlight_id%num;
			highlight_id++;

			int size = min(W / num, H / num);
			int x = W / (num * 2) + hl_x*W / num;
			int y = H / (num * 2) + hl_y*H / num;
			Mat bg_tmp;
			show_highlight(cavas, bg, x, y, color, shape, size, bg_tmp,cartoon);
			imshow(cavas, bg_tmp);
			//Sleep(10);
			char a = waitKey(waittime);

			if (a == 'q')
			{
				break;
			}
		}
	}

}

void show_highlight(string cavas, const Mat& bg, int x, int y, string color, string shape, int size,Mat& bg_tmp,Mat& cartoon)
{
	bg_tmp = bg.clone();
	Scalar cl;
	if (color == "red")
	{
		cl = Scalar(0, 0, 255);
	}
	else if (color == "green")
	{
		cl = Scalar(0, 255, 0);
	}
	else if (color == "blue")
	{
		cl = Scalar(255, 0, 0);
	}

	if (shape == "rectangle")
	{
		Rect r(x - size / 2, y - size / 2, size, size);
		rectangle(bg_tmp, r, cl, -1, 8, 0);

		//imshow("bg", bg);
	//	waitKey(10);
	}
	else if (shape == "circle")
	{
		circle(bg_tmp, Point(x, y), size / 2, cl, -1, 8, 0);
	}
	else if (shape == "img")
	{
		Rect r(x - size / 2, y - size / 2, size, size);
		resize(cartoon, cartoon, Size(size, size));
		cartoon.copyTo(bg_tmp(r));
	}


}
