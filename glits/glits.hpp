#pragma once

#include "epoxy/gl.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

namespace glits {

bool check_buffer(std::string ref, GLuint bufid, double max_mean, double max_dev);
bool check_texture(std::string ref, GLuint texid, double max_mean, double max_dev);
bool check_framebuffer(std::string ref, double max_mean, double max_dev);

}
