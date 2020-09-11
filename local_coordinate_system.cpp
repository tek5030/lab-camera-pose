#include "local_coordinate_system.h"
#include "Eigen/Geometry"

LocalCoordinateSystem::LocalCoordinateSystem(const GeodeticPosition& origin)
    : local_{origin.latitude, origin.longitude, origin.altitude}
{}

Sophus::SE3d LocalCoordinateSystem::toLocalPose(const GeodeticPosition& geo_pos, const Sophus::SO3d& att_ned_body) const
{
  // Use a std::vector as storage for a row-major Eigen::Matrix3d.
  std::vector<double> matrix_data(9);
  Eigen::Map<Eigen::Matrix<double, 3, 3, Eigen::RowMajor>> R_local_ned(matrix_data.data());
  Eigen::Vector3d t_enu;

  // Transform geodetic coordinates to local (ENU-based) cartesian coordinate system.
  local_.Forward(geo_pos.latitude, geo_pos.longitude, geo_pos.altitude,
               t_enu.x(), t_enu.y(), t_enu.z(),
               matrix_data);

  // Compute attitude in local (NED-based) coordinate system.
  const Sophus::SO3d att_local_body{Sophus::SO3d{R_local_ned} * att_ned_body};

  // Compute position in local (NED-based) coordinate system.
  const Eigen::Vector3d t_ned{t_enu.y(), t_enu.x(), -t_enu.z()};

  return {att_local_body, t_ned};
}
