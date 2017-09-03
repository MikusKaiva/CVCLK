#include <opencv2/opencv.hpp>
#include <string>

int FindImage(cv::Mat& imgToSearch, cv::Mat& imgLocation, int& x1, int& y1, int& x2, int& y2);
int FindImageInPartOfDesktop(const std::string imgFileName, int x1, int y1, int x2, int y2);