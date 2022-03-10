#include "local_coordinate_system.h"
#include "Eigen/Geometry"

LocalCoordinateSystem::LocalCoordinateSystem(const GeodeticPosition& origin)
    : local_{origin.latitude, origin.longitude, origin.altitude}
{}

Sophus::SE3d LocalCoordinateSystem::toLocalPose(const GeodeticPosition& position_geodetic_body,
                                                const Sophus::SO3d& orientation_ned_body) const
{
  // Use a std::vector as storage for a row-major Eigen::Matrix3d.
  std::vector<double> matrix_data(9);
  Eigen::Map<Eigen::Matrix<double, 3, 3, Eigen::RowMajor>> R_local_ned(matrix_data.data());
  Eigen::Vector3d position_enu_body;

  // Transform geodetic coordinates to local (ENU-based) cartesian coordinate system.
  local_.Forward(position_geodetic_body.latitude, position_geodetic_body.longitude, position_geodetic_body.altitude,
                 position_enu_body.x(), position_enu_body.y(), position_enu_body.z(),
                 matrix_data);

  // Compute attitude in local (NED-based) coordinate system.
  const Sophus::SO3d orientation_local_body{Sophus::SO3d{R_local_ned} * orientation_ned_body};

  // Compute position in local (NED-based) coordinate system.
  const Eigen::Vector3d position_local_body{position_enu_body.y(), position_enu_body.x(), -position_enu_body.z()};

  return {orientation_local_body, position_local_body};
}
