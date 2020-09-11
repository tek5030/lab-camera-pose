# Step 1: Get an overview
We will as usual start by presenting an overview of the method and the contents of this project.

## Holmenkollen dataset
In the [`data` directory](https://github.com/tek5030/lab_05/tree/master/data), we are given a dataset of 110 images taken from a camera held by hand inside a helicopter.

For each image, we also have the following data:
- The intrinsic camera calibration.
- Navigation data: The pose of the helicopter (body) in geographical coordinates.
- Camera pose measurements: The pose of the camera relative to the helicopter.

We have also provided a data reader that we will use.

## Lab overview
Our job today is to represent and visualize these camera poses in a common coordinate system. 
We will then project the geographical coordinate of a light pole into the images, so that we can find its pixel position in each image.

The main steps in today's lab are:
- Represent the geographical body poses in a common local Cartesian coordinate system.
- Compute the corresponding camera poses in the same coordinate system.
- Undistort the images using the supplied calibration parameters.
- Project a geographic world point into the images, using the perspective camera model.

## Introduction to the project source files
We have chosen to distribute the code on the following files:

- *main.cpp*
  
  Starts lab 5, catches any exceptions and prints their error message on the console.
  
- *lab_5.h, lab_5.cpp*
  
  Runs the lab 5 loop.
  You will implement much of this loop.
  
- *attitude.h, attitude.cpp*
  
  Represents an attitude (orientation) as a set of x-y-z Euler angles (roll, pitch, yaw). 
  You will be responsible for converting Euler angles to a rotation matrix, represented as a unit quaternion.
  
- *cartesian_position.h, cartesian_position.cpp*
  
  Represents a position in Cartesian space in meters. 
  You will be responsible for converting this position to an `Eigen::Vector3d` translation vector.
  
- *dataset.h, dataset.cpp*
  
  Reads data as a stream of `DataElement`s.

- *geodetic_position.h, geodetic_position.cpp*
  
  Represents a position in [geodetic coordinates](https://en.wikipedia.org/wiki/Geographic_coordinate_system) (latitude, longitude and altitude).

- *intrinsics.h, intrinsics.cpp*
  
  Represents the intrinsic calibration parameters for a camera. 
  You will be responsible for converting these to the camera calibration matrix **K** and an [OpenCV distortion coefficient vector](https://docs.opencv.org/4.0.1/d9/d0c/group__calib3d.html).

- *local_coordinate_system.h, local_coordinate_system.cpp*
  
  Uses the library [GeographicLib](https://geographiclib.sourceforge.io/) to represent geographical coordinates in a local Cartesian coordinate system.

- *perspective_camera_model.h, perspective_camera_model.cpp*
  
  Represents a perspective camera. 
  You will be responsible for implementing functionality for projecting 3D points into pixels.

- *viewer_3d.h, viewer_3d.cpp*
  
  Uses the OpenCV module [viz3d](https://docs.opencv.org/4.0.1/d1/d19/group__viz.html) to visualize results in 3D.

Please continue to the [next step](2-from-geographical-coordinates-to-pixels.md) to get started!

