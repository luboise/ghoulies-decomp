from conan import ConanFile


class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        self.folders.generators = "conan"

    def requirements(self):
        # self.requires("fmt/11.0.2")
        self.requires("sdl/3.2.20")
        self.requires("glm/1.0.1")
        self.requires("libdeflate/1.23")

    def build_requirements(self):
        self.test_requires("catch2/3.7.1")
