#pragma once

#include "Eigen/Dense"
#include <iostream>

/// \brief Position in cartesian space as raw x, y, z values in meters.
struct CartesianPosition
{
  double x;  /// Position along x-axis in meters.
  double y;  /// Position along y-axis in meters.
  double z;  /// Position along z-axis in meters.

  /// \brief Convert to vector representation.
  Eigen::Vector3d toVector();
};

/// \brief Operator for reading data from stream.
std::istream& operator>>(std::istream& is, CartesianPosition& pos);

/// \brief Operator for printing data to stream.
/// Meant for showing data, and is not compatible with the reader.
std::ostream& operator<<(std::ostream& os, const CartesianPosition& pos);
