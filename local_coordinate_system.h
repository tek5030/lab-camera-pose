#pragma once

#include "GeographicLib/LocalCartesian.hpp"
#include "sophus/se3.hpp"
#include "geodetic_position.h"
#include "attitude.h"

/// \brief Computes and represents a local cartesian coordinate system.
class LocalCoordinateSystem
{
public:
  /// \brief Constructs a local NED coordinate system at the specified origin.
  /// \param origin Origin for coordinate system.
  explicit LocalCoordinateSystem(const GeodeticPosition& origin);

  /// \brief Transforms geodetic position and attitude to pose in local coordinate system.
  /// \param geo_pos Geodetic position
  /// \param att_ned_body Attitude
  Sophus::SE3d toLocalPose(const GeodeticPosition& geo_pos, const Sophus::SO3d& att_ned_body) const;

private:
  GeographicLib::LocalCartesian local_;
};
