#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void MatCut();

int main(void)
{
	MatCut();

    return 0;

}

void MatCut()
{
	Mat main_img = imread("sample_gang.jpg", IMREAD_GRAYSCALE);//이미지 불러오기
	
	
	if (main_img.empty()) {
		cerr << "Image load failed!" << endl; //이미지가 불러와지지 않을 경우
		return;
	}
	

	Mat new_img; //리사이즈를 위한 새로운 이미지 변수
	int IMG_SIZE = 1000; //이미지 사이즈 설정을 위한 변수

	int a = 10; //영역 잘라낼 때 x좌표
	int b = 10; //영역 잘라낼 때 y좌표
	int c = 50; //영역 잘라낼 때 가로 크기
	int d = 50; //영역 잘라낼 때 세로 크기

	resize(main_img, new_img, Size(IMG_SIZE, IMG_SIZE), INTER_LINEAR); //이미지 리사이즈
	
	Mat cut_img = new_img(Rect(a, b, c, d)); //영역 잘라내기  
	
	imshow("cut_img", cut_img); //잘라낸 이미지 보여주기

	waitKey();
	destroyAllWindows();
}
