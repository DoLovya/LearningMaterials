from conan import ConanFile
from conan.tools.files import copy
import os

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("zlib/1.2.11")

    def configure(self):
        self.options['zlib'].shared = True

    def generate(self):
        for dep in self.dependencies.values():
            print('dep.cpp_info.bindirs[0] -> ' + dep.cpp_info.bindirs[0])
            copy(self, "*.dll", dep.cpp_info.bindirs[0], self.build_folder + "/Release")

    def package(self):
        print('------------ package ----------------------')
        copy(self, "*.lib", self.build_folder, str.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.dll", self.build_folder, str.join(self.package_folder, "bin"), keep_path=False)