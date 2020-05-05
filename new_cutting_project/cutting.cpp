#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	Mat img;
	Mat gray;
	Mat bi;
	Mat cut_img;
	Mat final_img;

	int zero_cnt = 0;
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	//�̹��� �Է�
	img = imread("sample_gang.jpg");

	// Grayscale
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//Binarization
	threshold(gray, bi, 180, 255, THRESH_BINARY);

	// ���� Y��
	for (int x = 0; x < bi.cols; x++)
	{
		for (int y = 0; y < bi.rows; y++)
		{
			if (bi.at<uchar>(y, x) == 255)
				zero_cnt++;
		}

		if (zero_cnt > 10) {
			x1 = x;
			zero_cnt = 0;
			break;
		}
		zero_cnt = 0;
	}

	//������ Y��
	for (int x = 0; x < bi.cols; x++) {
		for (int y = 0; y < bi.rows; y++) {
			if (bi.at<uchar>(y, (bi.cols - 1) - x) == 255)
				zero_cnt++;
		}

		if (zero_cnt > 0) {
			x2 = (bi.cols - 1) - x;
			zero_cnt = 0;
			break;
		}
		zero_cnt = 0;
	}

	// �� X��
	for (int y = 0; y < bi.rows; y++) {
		for (int x = 0; x < bi.cols; x++) {
			if (bi.at<uchar>(y, x) == 255)
				zero_cnt++;
		}

		if (zero_cnt > 0) {
			y1 = y;
			zero_cnt = 0;
			break;
		}
		zero_cnt = 0;
	}

	// �Ʒ� X��
	for (int y = 0; y < bi.rows; y++) {
		for (int x = 0; x < bi.cols; x++) {
			if (bi.at<uchar>((bi.rows - 1) - y, x) == 255)
				zero_cnt++;
		}
		if (zero_cnt > 0) {
			y2 = (bi.rows - 1) - y;
			zero_cnt = 0;
			break;
		}
		zero_cnt = 0;
	}

	cut_img = bi(Range(y1, y2), Range(x1, x2)); //resize�� ���� xy��ǥ

	resize(cut_img, cut_img, Size(200, 200), 0, 0, INTER_LINEAR);

	final_img = ~cut_img; // �۾��� ����������, ����� ������� ��ȯ

	imshow("Crop", final_img);

	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(95);
	imwrite("Cut_img.jpg", img, params);//jpg ���Ϸ� ����


	waitKey();
	destroyAllWindows();
}