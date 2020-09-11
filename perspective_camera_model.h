#pragma once

#include "Eigen/Dense"
#include "sophus/se3.hpp"
#include "opencv2/core.hpp"

/// \brief Represents the Perspective Camera Model.
class PerspectiveCameraModel
{
public:
  using Matrix34d = Eigen::Matrix<double, 3, 4>;
  using Vector5d = Eigen::Matrix<double, 5, 1>;

  /// \brief Constructs the camera model.
  /// \param K The intrinsic calibration matrix.
  /// \param pose_world_camera The pose of the camera in the world coordinate system.
  /// \param distortion_coeffs Distortion coefficients on the form [k1, k2, p1, p2, k3].
  PerspectiveCameraModel(const Eigen::Matrix3d& K,
                         const Sophus::SE3d& pose_world_camera,
                         const Vector5d& distortion_coeffs);

  /// \return The pose of the camera in world coordinates.
  Sophus::SE3d getPose() const;

  /// \return The intrinsic calibration matrix.
  Eigen::Matrix3d getCalibrationMatrix() const;

  /// \return The camera projection matrix.
  Matrix34d getCameraProjectionMatrix() const;

  /// \brief Projects a world point into pixel coordinates.
  /// \param world_point A 3D point in world coordinates.
  Eigen::Vector2d projectWorldPoint(Eigen::Vector3d world_point) const;

  /// \brief Projects a set of world points into pixel coordinates.
  /// \param world_points A set of 3D points in world coordinates.
  Eigen::Matrix2Xd projectWorldPoints(Eigen::Matrix3Xd world_points) const;

  /// \brief Undistorts an image corresponding to the camera model.
  /// \param distorted_image The original, distorted image.
  /// \return The undistorted image.
  cv::Mat undistortImage(cv::Mat distorted_image) const;

private:
  Matrix34d computeCameraProjectionMatrix();

  Eigen::Matrix3d K_;
  Sophus::SE3d pose_world_camera_;
  Vector5d distortion_coeffs_;
  Matrix34d camera_projection_matrix_;
};
