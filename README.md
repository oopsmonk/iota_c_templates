# iota.c templates  

This repository contains two templates for developing IOTA client application out of the box.  
* Bazel template: building your application with [Bazel](https://bazel.build/).  
* CMake template: building your application with [CMake](https://cmake.org/).  

For more details:  
[Bazel C++ Tutorial](https://docs.bazel.build/versions/master/tutorial/cpp.html)  
[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)  

**Source layout:**  
```
.
├── bazel_template
│   ├── BUILD
│   ├── .clang-format
│   ├── config.h
│   ├── .gitignore
│   ├── my_app.c
│   └── WORKSPACE
├── cmake_template
│   ├── .clang-format
│   ├── CMakeLists.txt
│   ├── config.h
│   ├── .gitignore
│   └── my_app.c
├── LICENSE
└── README.md
```

## How to use templates  

After clone this repository, copy and rename a template to your project workspace.  

```shell
git clone https://github.com/oopsmonk/iota_c_templates.git

# cmake project
cp -r iota_c_templates/cmake_template iota_cmake_app

# bazel or bazelisk project
cp -r iota_c_templates/bazel_template iota_bazel_app
```


## How to compile application on Linux  

It is tested on Ubuntu but I believe it works on MacOS as well.  
For making sure your Bazel is up-to-date or you can use [bazelisk](https://github.com/bazelbuild/bazelisk)  

```shell
# cmake
cd iota_cmake_app
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$PWD .. && make -j8
# run the example 
./my_app

# bazel
cd iota_bazel_app
bazel run my_app

# bazelisk
cd iota_bazel_app
USE_BAZEL_VERSION=2.1.0 bazelisk run my_app
```

## How to compile application on Windows  

It is tested via Powershell on Windows 10.  
The iota.c library only support MinGW compiler on Windows, make sure you have installed it on your system.  
Due to the [CMake symlink issue](https://gitlab.kitware.com/cmake/cmake/issues/17739) we can use ninja generator instead of the default generator.  

**Requirements**  
* [Bazel](https://github.com/bazelbuild/bazel/releases) or [Bazelisk](https://github.com/bazelbuild/bazelisk/releases)  
* [MinGW](https://osdn.net/projects/mingw/releases/)  
* [Ninja](https://github.com/ninja-build/ninja/releases)  

```shell

# cmake
cp -r iota_c_templates/cmake_template iota_cmake_app
PS C:\Users\Sam\IOTA\> cd iota_cmake_app
PS C:\Users\Sam\IOTA\iota_cmake_app> mkdir app_build && cd app_build
PS C:\Users\Sam\IOTA\iota_cmake_app\app_build> cmake.exe -G Ninja -DCMAKE_INSTALL_PREFIX=$PWD .. 
PS C:\Users\Sam\IOTA\iota_cmake_app\app_build> ninja.exe
# run the example 
PS C:\Users\Sam\IOTA\iota_cmake_app\app_build> .\my_app.exe

# bazel
cp -r iota_c_templates/bazel_template iota_bazel_app
PS C:\Users\Sam\IOTA> cd iota_bazel_app
PS C:\Users\Sam\IOTA\iota_bazel_app> bazel.exe run --compiler=mingw-gcc my_app

# bazelisk
PS C:\Users\Sam\IOTA\iota_bazel_app> bazelisk.exe run --compiler=mingw-gcc my_app
```
