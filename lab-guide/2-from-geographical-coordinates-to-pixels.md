# Step 2: From geographical coordinates to pixels
Now, lets compute the connection between geographical coordinates and image pixels using real data!

## The Sophus library
We will use [Sophus](https://github.com/strasdat/Sophus) to represent poses and orientations. 
It lets us perform operations on SO(3) and SE(3) matrix Lie groups with Eigen. 
Take a look at [so3.hpp](https://github.com/strasdat/Sophus/blob/master/sophus/so3.hpp) and [se3.hpp](https://github.com/strasdat/Sophus/blob/master/sophus/se3.hpp) for documentation. 
Ask the instructors when you have questions about Sophus!

## Coordinate systems
In [camera_pose_lab.cpp](../camera_pose_lab.cpp), we are given the geodetic position of a light pole:

![Map with position of light pole](img/light-pole-position.png)

We will create a local Cartesian NED coordinate system around this position using `LocalCoordinateSystem`. 
The helicopter (body) navigation data is given as a set of [geodetic positions](https://en.wikipedia.org/wiki/Geographic_coordinate_system) with the corresponding [NED attitude](https://en.wikipedia.org/wiki/Axes_conventions#Ground_reference_frames:_ENU_and_NED). 
The `LocalCoordinateSystem` class lets us convert navigation data to poses in the local coordinate system *F<sub>l</sub>*.

Take a look at the documentation in [local_coordinate_system.h](../local_coordinate_system.h).

![Illustration of the different coordinate systems](img/coordinate_systems.png)

With `LocalCoordinateSystem`, we are able to represent the poses of the helicopter *F<sub>b</sub>* in a common Cartesian coordinate system *F<sub>l</sub>*.

The camera  pose measurements in *F<sub>c</sub>* are represented as Cartesian positions with corresponding NED attitudes relative to the body frame *F<sub>b</sub>*.

For each image, we are given these data in `DataElement`. 
Take a look at `DataElement` in [dataset.h](../dataset.h).
Then, get an overview of the data structures in [attitude.h](../attitude.h), [geodetic_position.h](../geodetic_position.h) and [cartesian_position.h](../cartesian_position.h).

## 1. Convert geographical body position and attitude to local Cartesian pose
The first step is to convert the navigation data to the poses **T**<sub>*lb*</sub> (pose of *F<sub>b</sub>* relative to *F<sub>l</sub>*). 
To accomplish this, we need to convert the orientation from roll-pitch-yaw Euler angles (*&theta;<sub>1</sub>*, *&theta;<sub>2</sub>*, *&theta;<sub>3</sub>*) to a proper rotation matrix:

![From roll-pitch-yaw to a rotation matrix](img/math_euler.png)

You will need to finish the `Attitude::toQuaternion` member function in [attitude.cpp](../attitude.cpp), which is used by `Attitude::toSO3` to return a `Sophus::SO3d` orientation.
1. Convert attitude in Euler angles (roll-pitch-yaw) to a Quaternion. 
   Use `Eigen::AngleAxisd`, which lets us [create principal rotations, combine them and return quaternions](http://eigen.tuxfamily.org/dox/classEigen_1_1AngleAxis.html).
2. Add body axes to the 3D viewer in [camera_pose_lab.cpp](../camera_pose_lab.cpp) using [`Viewer3D::addBodyAxes`](../viewer_3d.h).
   Use the image number provided by the data element.
3. Compile and run. 
   You should see the body axes for each image.
   The forward axis (is that *x*, *y* or *z*?) should point approximately towards the next pose.
   Check also that the other directions (right and down) look reasonable

## 2. Compute the pose of the camera
The next step is to convert the camera pose measurements to poses **T**<sub>*lc*</sub> (pose of *F<sub>c</sub>* relative to *F<sub>l</sub>*).

You will need to finish `CartesianPosition::toVector` to return a translation vector between *F<sub>b</sub>* and *F<sub>c</sub>*. 
You can then use this translation and the corresponding SO(3) orientation from the camera's attitude to compute the SE(3) pose **T**<sub>*bc*</sub>. 
This will let you compute and visualize the pose **T**<sub>*lc*</sub>.

1. Convert the Cartesian position to a translation vector between *F<sub>b</sub>* and *F<sub>c</sub>* by finishing `CartesianPosition::toVector` in [cartesian_position.cpp](../cartesian_position.cpp).
2. Construct the pose **T**<sub>*bc*</sub> in the body coordinate system in [camera_pose_lab.cpp](../camera_pose_lab.cpp).
3. Compute the pose **T**<sub>*lc*</sub> in the local coordinate system in [camera_pose_lab.cpp](../camera_pose_lab.cpp).
4. Add the camera axes to the 3D viewer in [camera_pose_lab.cpp](../camera_pose_lab.cpp) using [`Viewer3D::addCameraAxes`](../viewer_3d.h).
5. Compile and run. 
   You should see the smaller camera axes together with the body axes for each image.
   The optical axis (is that *x*, *y* or *z*?) should point approximately towards the origin of the local coordinate system, shown by the big axes in the center of the grid plane.
   Does the result look reasonable?

## 3. Undistort the images
Before we can project world points into the images, we need to undistort them.
Why?

The calibration parameters have been read into `Intrinsics` objects. 
To use them, we need to finish `Intrinsics::toCalibrationMatrix` to return the camera calibration matrix **K** and `Intrinsics::toDistortionVector` to return an [OpenCV distortion coefficient vector](https://docs.opencv.org/4.9.0/d9/d0c/group__calib3d.html).
We can then undistort the image using `PerspectiveCameraModel`.
Take a look at the documentation in [perspective_camera_model.h](../perspective_camera_model.h).

1. Finish `Intrinsics::toCalibrationMatrix` in [intrinsics.cpp](../intrinsics.cpp).
2. Finish `Intrinsics::toDistortionVector` in [intrinsics.cpp](../intrinsics.cpp). 
   You should return a vector on the form [*k*<sub>1</sub>, *k*<sub>2</sub>, 0, 0, *k*<sub>3</sub>], where *k*<sub>*i*</sub> are the different radial distortion parameters.
3. Use the camera model to undistort the image in [camera_pose_lab.cpp](../camera_pose_lab.cpp).
4. Compile and run. 
   You will probably not notice any significant changes to the images, but if they still look reasonable, we are ready to continue!

## 4. Project a geographic world point into the images
We are now ready to project the position of the light pole into each image. 
Remember that the light pole is at the origin in the local coordinate system *F<sub>l</sub>*.

First, we need to compute the camera projection matrix

![Formula for the projection matrix P](img/math_proj-matrix.png)

in `PerspectiveCameraModel::computeCameraProjectionMatrix`. 

Make certain that you are using the correct pose when you extract **R** and **t**. 
You might be interested in the [`se3::matrix3x4`](https://github.com/strasdat/Sophus/blob/26c200265e2eb3d76e5ab00a99ada686d6a80d15/sophus/se3.hpp#L282) member function.

We can then use the camera projection matrix to implement the perspective camera projection function in `PerspectiveCameraModel::projectWorldPoint`. 
Remember to use the homogenous representations in Eigen.

1. Finish `PerspectiveCameraModel::computeCameraProjectionMatrix` in [perspective_camera_model.cpp](../perspective_camera_model.cpp).
2. Finish `PerspectiveCameraModel::projectWorldPoint` in [perspective_camera_model.cpp](../perspective_camera_model.cpp).
3. Add the camera frustum to the 3D viewer using [`Viewer3D::addCameraFrustum`](../viewer_3d.h) in [camera_pose_lab.cpp](../camera_pose_lab.cpp).
4. Compile and run. 
   Does the camera frustums look reasonable? 
   Is the light pole projected correctly into the images?
   
Congratulations! 
You have now established the connection between geographical coordinates and image pixels using the power of imaging geometry! 
Cool, right?

## Extra
- Finish [`PerspectiveCameraModel::projectWorldPoints`](https://github.com/tek5030/lab_05/blob/master/perspective_camera_model.cpp#L45) and project other geographical points into the images (see www.norgeskart.no).
- Create a virtual camera and project points into this camera.
