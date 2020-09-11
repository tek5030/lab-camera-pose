#include "viewer_3d.h"
#include "opencv2/core/eigen.hpp"

Viewer3D::Viewer3D()
  : viz_win_{"3D Visualization"}
{
  // Add world coordinate-axes.
  viz_win_.showWidget("World-axes", cv::viz::WCoordinateSystem(100.0));

  // Add world xy-grid
  viz_win_.showWidget("xy-grid", cv::viz::WGrid(
      { 0,0,0 }, { 0,0,1 }, { 0,1,0 },
      cv::Vec2i::all(50), cv::Vec2d::all(10.0),cv::viz::Color::gray()));
}

void Viewer3D::addBodyAxes(Sophus::SE3d pose_local_body, int img_num)
{
  // Convert from Eigen::Matrix to cv::Mat
  cv::Mat T_local_body_cv;
  cv::eigen2cv(pose_local_body.matrix(), T_local_body_cv);

  std::stringstream body_id;
  body_id << "Body_" << img_num;

  // Visualize body.
  viz_win_.showWidget(body_id.str(), cv::viz::WCoordinateSystem(25.0), cv::Affine3d{T_local_body_cv});
}

void Viewer3D::addCameraAxes(Sophus::SE3d pose_local_camera, int img_num)
{
  // Convert from Eigen::Matrix to cv::Mat
  cv::Mat T_local_camera_cv;
  cv::eigen2cv(pose_local_camera.matrix(), T_local_camera_cv);

  std::stringstream camera_axes_id;
  camera_axes_id << "Cam_axes_" << img_num;

  // Visualize body.
  viz_win_.showWidget(camera_axes_id.str(), cv::viz::WCoordinateSystem(10.0), cv::Affine3d{T_local_camera_cv});
}

void Viewer3D::addCameraFrustum(const PerspectiveCameraModel& cameraModel, const cv::Mat& img, int img_num)
{
  // Convert from Eigen::Matrix to cv::Mat
  cv::Mat T_local_body_cv;
  cv::eigen2cv(cameraModel.getPose().matrix(), T_local_body_cv);
  cv::Matx33d K_cv;
  cv::eigen2cv(cameraModel.getCalibrationMatrix(), K_cv);

  std::stringstream cam_id;
  cam_id << "Cam_" << img_num;

  // Add camera frustum.
  viz_win_.showWidget(cam_id.str(),
                      cv::viz::WCameraPosition(K_cv, img, 25.0, cv::viz::Color::white()),
                      cv::Affine3d{T_local_body_cv});
}

void Viewer3D::spinOnce()
{
  viz_win_.spinOnce();
}

void Viewer3D::spin()
{
  viz_win_.spin();
}
