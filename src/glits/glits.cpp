#include "glits/glits.hpp"

bool glits::check_mat(cv::Mat img1, cv::Mat img2, double max_mean, double max_dev) {
  cv::Mat diff;
  cv::Scalar meanmat;
  cv::Scalar stddevmat;

  if (!img1.data || !img2.data) {
    std::cout << "glits check mat: missing img data" << std::endl;
    return false;
  }

  cv::absdiff(img1, img2, diff);
  cv::meanStdDev(diff, meanmat, stddevmat);

  auto mean = meanmat.val[0];
  auto stddev = stddevmat.val[0];

  if (mean > max_mean || stddev > max_dev) {
    std::cout << "GLITS: "
              << " mean: " << mean << " max mean: " << max_mean << " stddev: " << stddev << " max stddev: " << max_dev << std::endl;
    return false;
  }
  return true;
}

bool glits::check_buffer(std::string ref, GLuint bufid, double max_mean, double max_dev, bool generate) { return true; }

bool glits::check_texture(std::string ref, GLuint texid, double max_mean, double max_dev, bool generate) {
  GLint w, h;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

  cv::Mat img(w, h, CV_8UC3);
  img.create(w, h, CV_8UC3);

  // use fast 4-byte alignment (default anyway) if possible
  GLint packalignment;
  glGetIntegerv(GL_PACK_ALIGNMENT, &packalignment);
  glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);

  // set length of one complete row in destination data (doesn't need to equal img.cols)
  GLint packrowlength;
  glGetIntegerv(GL_PACK_ROW_LENGTH, &packrowlength);
  glPixelStorei(GL_PACK_ROW_LENGTH, img.step / img.elemSize());

  glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

  // restore old settings
  glPixelStorei(GL_PACK_ALIGNMENT, packalignment);
  glPixelStorei(GL_PACK_ROW_LENGTH, packrowlength);

  if (!generate) {
    cv::Mat img2;
    img2 = cv::imread(ref, 1);

    return check_mat(img, img2, max_mean, max_dev);
  } else {
    cv::imwrite(ref, img);
  }
}

bool glits::check_framebuffer(std::string ref, double max_mean, double max_dev, bool generate) {
  // get framebuffer dimensions
  GLint dims[4] = {0, 0, 0, 0};
  glGetIntegerv(GL_VIEWPORT, dims);
  cv::Mat img(dims[3], dims[2], CV_8UC3);
  img.create(dims[3], dims[2], CV_8UC3);

  // use fast 4-byte alignment (default anyway) if possible
  GLint packalignment;
  glGetIntegerv(GL_PACK_ALIGNMENT, &packalignment);
  glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);

  // set length of one complete row in destination data (doesn't need to equal img.cols)
  GLint packrowlength;
  glGetIntegerv(GL_PACK_ROW_LENGTH, &packrowlength);
  glPixelStorei(GL_PACK_ROW_LENGTH, img.step / img.elemSize());

  glReadPixels(dims[0], dims[1], dims[2], dims[3], GL_BGR, GL_UNSIGNED_BYTE, img.data);

  // restore old settings
  glPixelStorei(GL_PACK_ALIGNMENT, packalignment);
  glPixelStorei(GL_PACK_ROW_LENGTH, packrowlength);

  // either save the framebuffer content to a file or read it from file
  if (!generate) {
    cv::Mat img2;
    img2 = cv::imread(ref, 1);
    return check_mat(img, img2, max_mean, max_dev);
  } else {
    cv::imwrite(ref, img);
  }

  return true;
}
