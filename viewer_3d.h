#pragma once

#include "perspective_camera_model.h"
#include "sophus/se3.hpp"
#include "opencv2/viz.hpp"

class Viewer3D
{
public:
  Viewer3D();

  void addBodyAxes(Sophus::SE3d pose_local_body, int img_num);
  void addCameraAxes(Sophus::SE3d pose_local_camera, int img_num);
  void addCameraFrustum(const PerspectiveCameraModel& cameraModel, const cv::Mat& img, int img_num);

  void spinOnce();
  void spin();

private:
  cv::viz::Viz3d viz_win_;
};
