from conans import ConanFile, CMake

class LabMosaic(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "eigen/3.4.0", "geographiclib/1.52", "opencv/4.5.5", "sophus/22.10"
    generators = "cmake_find_package", "virtualrunenv"
    default_options = {
        "opencv:dnn": False,
        "opencv:nonfree": True,
        "opencv:with_ffmpeg": False
    }

    def configure(self):
        if self.settings.os == "Linux":
            self.options["opencv"].with_v4l = True