# iota.c templates  

This repository contains two templates for developing iota.c out of the box.

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

For more details:  
[Bazel C++ Tutorial](https://docs.bazel.build/versions/master/tutorial/cpp.html)  
[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)  

# How to use

After clone this repository, copy and rename cmake_template or bazel_template to your project workspace.  

```shell
git clone https://github.com/oopsmonk/iota_c_templates.git

# cmake
cp -r iota_c_templates/cmake_template iota_cmake_app
cd iota_cmake_app
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$PWD .. && make -j8
# run the example 
./my_app

# bazel
cp -r iota_c_templates/bazel_template iota_bazel_app
cd iota_bazel_app
bazel run :my_app
```
