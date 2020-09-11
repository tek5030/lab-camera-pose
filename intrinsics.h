#pragma once

#include "Eigen/Dense"
#include <iostream>

/// \brief Intrinsic camera calibration parameters.
struct Intrinsics
{
  double fu;  /// Focal length in the horizontal u-direction.
  double fv;  /// Focal length in the vertical v-direction.
  double s;   /// Skew.
  double cu;  /// Principal coordinate in the horizontal u-direction.
  double cv;  /// Principal coordinate in the vertical v-direction.

  double k1;  /// First radial distortion coefficient.
  double k2;  /// Second radial distortion coefficient.
  double k3;  /// Third radial distortion coefficient.

  /// Shorthand for 5x1 vector.
  using Vector5d = Eigen::Matrix<double, 5, 1>;

  /// \brief Extract calibration matrix.
  Eigen::Matrix3d toCalibrationMatrix();

  /// \brief Extract distortion coefficients on the form [k1, k2, 0, 0, k3].
  Vector5d toDistortionCoefficientVector();
};

/// \brief Operator for reading data from stream.
std::istream& operator>>(std::istream& is, Intrinsics& intrinsics);

/// \brief Operator for printing data to stream.
/// Meant for showing data, and is not compatible with the reader.
std::ostream& operator<<(std::ostream& os, const Intrinsics& intrinsics);
