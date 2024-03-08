# Pose and camera geometry

Welcome to this lab in the computer vision course [TEK5030] at the University of Oslo.

In this lab we will experiment with poses in different coordinate frames together with the perspective camera model, using real data taken from a helicopter flying around Holmenkollen.

![Holmenkollen in 3D with camera trajectory](lab-guide/img/holmenkollen-3d.png)

Then, open the lab project in CLion using the cmake-file in the base directory:
`lab-camera-pose/CMakeLists.txt`.
If you are uncertain about how this is done, please take a look at [the intro lab].

The lab is carried out by following these steps:

1. [Get an overview](lab-guide/1-get-an-overview.md)
2. [From geographical coordinates to pixels](lab-guide/2-from-geographical-coordinates-to-pixels.md)

You will find our proposed solution at https://github.com/tek5030/solution-camera-pose.
Please try to solve the lab with help from others instead of just jumping straight to the solution ;)

Start the lab by going to the [first step](lab-guide/1-get-an-overview.md).

## Prerequisites
- OpenCV must be installed on your system. If you are on a lab computer, you are all set.

  If you are on Ubuntu, but not on a lab computer, the following should be sufficient _for this lab_.

   ```bash
   sudo apt update
   sudo apt install libopencv-dev libopencv-viz-dev
   ```

- We refer to [setup_scripts](https://github.com/tek5030/setup_scripts) and [the intro lab] as a general getting started-guide for the C++ labs on Ubuntu 22.04.

---

[TEK5030]: https://www.uio.no/studier/emner/matnat/its/TEK5030/
[conan]: https://tek5030.github.io/tutorial/conan.html
[the intro lab]: https://github.com/tek5030/lab-intro/blob/master/cpp/lab-guide/1-open-project-in-clion.md
