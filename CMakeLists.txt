cmake_minimum_required( VERSION 3.5.1 )

project(lab_camera_pose)

# Compiler flags
if (MSVC)
  set(compiler_options /W4)
  add_definitions(/D_USE_MATH_DEFINES)
else ()
  set(compiler_options -Wall -Wextra -Wpedantic)
endif (MSVC)
  
# Find libraries
find_package(OpenCV 4 REQUIRED)
find_package(Sophus REQUIRED)
find_package(GeographicLib REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  attitude.h
  attitude.cpp
  cartesian_position.h
  cartesian_position.cpp
  dataset.h
  dataset.cpp
  geodetic_position.h
  geodetic_position.cpp
  intrinsics.h
  intrinsics.cpp
  camera_pose_lab.h
  camera_pose_lab.cpp
  local_coordinate_system.h
  local_coordinate_system.cpp
  perspective_camera_model.h
  perspective_camera_model.cpp
  viewer_3d.h
  viewer_3d.cpp
  )

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBS}
  ${GeographicLib_LIBRARIES}
  Sophus::Sophus
  )

target_compile_options(${PROJECT_NAME} PRIVATE ${compiler_options})
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD_REQUIRED ON
  CXX_STANDARD 14
  )
