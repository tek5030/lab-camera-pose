#include "lab_5.h"

#include "dataset.h"
#include "local_coordinate_system.h"
#include "viewer_3d.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

Lab5::Lab5(const std::string& data_path)
  : data_path_{data_path}
  , window_name_{"World point in camera"}
{}

void Lab5::run()
{
  // Set up dataset.
  Dataset dataset{data_path_};

  // Define local coordinate system based on the position of a light pole.
  const GeodeticPosition light_pole_position{59.963516, 10.667307, 321.0};
  const LocalCoordinateSystem local_system(light_pole_position);

  // Construct viewers.
  cv::namedWindow(window_name_);
  Viewer3D viewer;

  // Process each image in the dataset.
  for (DataElement element{}; dataset >> element;)
  {
    // Todo 1: Convert geographical position and attitude to local Cartesian pose.
    // Todo 1.1: Finish Attitude::toQuaternion().
    // Compute the pose of the body in the local coordinate system.
    const Sophus::SE3d pose_local_body = local_system.toLocalPose(element.body_position_in_geo,
                                                                  element.body_attitude_in_geo.toSO3());

    // Todo 1.2: Add body coordinate axes to 3d viewer.
    // Add body coordinate axes to the 3D viewer.


    // Todo 2: Compute the pose of the camera
    // Todo 2.1: Finish CartesianPosition::toVector(),
    // Todo 2.2: Construct pose_body_camera correctly using element.
    // Compute the pose of the camera relative to the body.
    const Sophus::SE3d pose_body_camera{};

    // Todo 2.3: Construct pose_local_camera correctly using the poses above.
    // Compute the pose of the camera relative to the local coordinate system.
    const Sophus::SE3d pose_local_camera{};

    // Todo 2.4: Add camera coordinate axes to 3d viewer.
    // Add camera coordinate axes to the 3D viewer.

    // Todo 3: Undistort the images.
    // Todo 3.1: Finish Intrinsics::toCalibrationMatrix().
    // Todo 3.2: Finish Intrinsics::toDistortionVector().
    // Construct a camera model based on the intrinsic calibration and camera pose.
    const PerspectiveCameraModel camera_model{element.intrinsics.toCalibrationMatrix(),
                                             pose_local_camera,
                                             element.intrinsics.toDistortionCoefficientVector()};

    // Todo 3.3: Undistort image using the camera model. Why should we undistort the image?
    // Undistort the original image, instead of using it directly.
    cv::Mat undistorted_img = element.image;

    // Todo 4: Project a geographic world point into the images
    // Todo 4.1: Finish PerspectiveCameraModel::computeCameraProjectionMatrix().
    // Todo 4.2: Finish PerspectiveCameraModel::projectWorldPoint().
    // Project world point (the origin) into the image.
    const Eigen::Vector2d pix_pos = camera_model.projectWorldPoint(Eigen::Vector3d::Zero());

    // Draw a marker in the image at the projected position.
    const Eigen::Vector2i pix_pos_int = (pix_pos.array().round()).cast<int>();
    cv::drawMarker(undistorted_img, {pix_pos_int.x(), pix_pos_int.y()}, {0.,0.,255.}, cv::MARKER_CROSS, 40, 3);

    // Todo 4.3: Add the camera frustum to the 3D viewer.
    // Add the camera frustum with the image to the 3D viewer.

    // Show the image.
    cv::imshow(window_name_, undistorted_img);

    // Update the windows.
    viewer.spinOnce();
    cv::waitKey(100);
  }

  // Remove image viewer.
  cv::destroyWindow(window_name_);

  // Run 3D viewer until stopped.
  viewer.spin();
}
