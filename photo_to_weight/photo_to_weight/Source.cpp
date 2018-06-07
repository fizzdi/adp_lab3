#define _CRT_SECURE_NO_WARNINGS
#include<opencv2\opencv.hpp>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace cv;
using namespace std;
typedef vector<vector<double>> Matrix;
Matrix dig[10][5];
Matrix av_count[10], weight[10];
int main() {
	
	for (int d = 0; d < 10; d++) {
		string path = to_string(d) + ".txt";
		freopen(path.c_str(), "w", stdout);
		av_count[d].resize(4, vector<double>(3, 0));
		weight[d].resize(4, vector<double>(3, 0));
		for (int ind = 0; ind < 5; ind++) {
			string name = "digit\\" + to_string(d) + "_" + to_string(ind) + ".jpg";
			Mat img = imread(name);
			int lr = img.rows / 4;
			int lc = img.cols;
			dig[d][ind].resize(4, vector<double>(3, 0));
			for (int i = 0; i < img.rows; i++) {
				for (int j = 0; j < 3*img.cols; j++) {
					int tmp = img.at<uchar>(i, j);
					if (tmp < 50) tmp = 1;
					else tmp = 0;
					dig[d][ind][i / lr][j / lc] += tmp;
				}
			}
		}			
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				double tmp = 0;
				for (int ind = 0; ind < 5; ind++) {
					tmp += dig[d][ind][i][j];
				}
				av_count[d][i][j] = tmp / 5.0;
			}
		}
		double sum = 0; 
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				sum += av_count[d][i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				weight[d][i][j] = av_count[d][i][j] / sum;
				printf("%.3f ", weight[d][i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}