#pragma once

#include "sophus/so3.hpp"
#include <iostream>

/// \brief Attitude represented as a raw set of Euler angles.
struct Attitude
{
  double x_rot;  /// Angle around x-axis in radians.
  double y_rot;  /// Angle around y-axis in radians.
  double z_rot;  /// Angle around z-axis in radians.

  /// \brief Convert to quaternion representation.
  Eigen::Quaterniond toQuaternion() const;

  /// \brief Convert to SO3 representation.
  Sophus::SO3d toSO3() const;
};

/// \brief Operator for reading data from stream.
std::istream& operator>>(std::istream& is, Attitude& att);

/// \brief Operator for printing data to stream.
/// Meant for showing data, and is not compatible with the reader.
std::ostream& operator<<(std::ostream& os, const Attitude& att);
