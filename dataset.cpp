#include "dataset.h"
#include "opencv2/imgcodecs.hpp"
#include <fstream>

bool Dataset::getNext(DataElement& element)
{
  get_succeeded_ = false;

  if (hasNext())
  {
    element.img_num = curr_file_num_;
    readImage(element);
    readMetadata(element);

    ++curr_file_num_;
    get_succeeded_ = true;
  }

  return get_succeeded_;
}

bool Dataset::hasNext() const
{
  return curr_file_num_ <= last_file_num;
}

Dataset::operator bool() const
{
  return get_succeeded_;
}

void Dataset::readImage(DataElement& element) const
{
  std::stringstream filepath;
  filepath << folder_name_ << "110608_Oslo_0" << curr_file_num_ << ".jpg";

  element.image = cv::imread(filepath.str(), cv::IMREAD_UNCHANGED);

  if (element.image.empty())
  {
    throw std::runtime_error("Could not open image file: " + filepath.str());
  }
}

void Dataset::readMetadata(DataElement& element) const
{
  std::stringstream filepath;
  filepath << folder_name_ << "110608_Oslo_0" << curr_file_num_ << ".txt";
  std::ifstream input_file{filepath.str()};

  if (!input_file)
  {
    throw std::runtime_error("Could not open file");
  }

  input_file >> element.intrinsics
             >> element.camera_position_in_body
             >> element.camera_attitude_in_body
             >> element.body_position_in_geo
             >> element.body_attitude_in_geo;
}

Dataset& operator>>(Dataset& dataset, DataElement& element)
{
  dataset.getNext(element);

  return dataset;
}
