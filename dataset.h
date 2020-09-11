#pragma once

#include "attitude.h"
#include "cartesian_position.h"
#include "geodetic_position.h"
#include "intrinsics.h"

#include "opencv2/core.hpp"

/// \brief A set of data for each image in the dataset.
struct DataElement
{
  int img_num;
  cv::Mat image;
  Intrinsics intrinsics;
  CartesianPosition camera_position_in_body;
  Attitude camera_attitude_in_body;
  GeodeticPosition body_position_in_geo;
  Attitude body_attitude_in_geo;
};

/// \brief Represents the dataset for Lab 5.
class Dataset
{
public:
  /// \brief Constructs a Lab 5 dataset.
  /// \param folder_name the folder where the dataset resides.
  explicit Dataset(const std::string& folder_name)
  : folder_name_(folder_name)
  , curr_file_num_{first_file_num}
  , get_succeeded_{true}
  {}

  /// \brief Reads the next data element.
  /// \param[out] element Data is read into this element.
  /// \return True if success.
  bool getNext(DataElement& element);

  /// \brief Checks if there is more data.
  /// \return True if more data.
  bool hasNext() const;

  /// \brief Checks if last get operation succeeded.
  /// \return True if success.
  explicit operator bool() const;

  static constexpr int first_file_num = 502;
  static constexpr int last_file_num = 611;

private:
  void readImage(DataElement& element) const;
  void readMetadata(DataElement& element) const;

  std::string folder_name_;
  int curr_file_num_;
  bool get_succeeded_;
};

/// \brief Stream operator for getting the next data element.
Dataset& operator>>(Dataset& dataset, DataElement& element);
