#include "glits/glits.hpp"

bool glits::check_buffer(std::string ref, GLuint bufid, double max_mean, double max_dev) { return true; }

bool glits::check_texture(std::string ref, GLuint texid, double max_mean, double max_dev) {
#ifndef GLITS_GENERATE_DATA
  cv::Mat image;
  image = cv::imread(ref, 1);
  cv::Mat image2;
  image2 = cv::imread("../testdata/test2.png", 1);
  cv::Mat diff;
  cv::Scalar meanmat;
  cv::Scalar stddevmat;

  if (!image.data) {
    std::cout << "GLITS: couldn't load image from " << ref << std::endl;
    return false;
  }

  cv::absdiff(image, image2, diff);
  cv::meanStdDev(diff, meanmat, stddevmat);

  auto mean = meanmat.val[0];
  auto stddev = stddevmat.val[0];

  if (mean > max_mean || stddev > max_dev) {
    std::cout << "GLITS: " << ref << " mean: " << mean << " max mean: " << max_mean << " stddev: " << stddev << " max stddev: " << max_dev << std::endl;
    return false;
  }

#else
#endif

  return true;
}

bool glits::check_framebuffer(std::string ref, double max_mean, double max_dev) { return true; }
