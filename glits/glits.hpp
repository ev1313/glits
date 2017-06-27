#pragma once

#include "epoxy/gl.h"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>

namespace glits {

bool check_mat(cv::Mat img1, cv::Mat img2, double max_mean, double max_dev);
bool check_buffer(std::string ref, GLuint bufid, double max_mean, double max_dev, bool generate = false);
bool check_texture(std::string ref, GLuint texid, double max_mean, double max_dev, bool generate = false);
bool check_framebuffer(std::string ref, double max_mean, double max_dev, bool generate = false);
}
