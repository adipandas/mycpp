# How to build and use this code.

1. You will have to build [this folder](../simple1_lib) first. Follow the instructions there.

2. Follow the below instructions to build the code in this folder:

    Update the path of the library as per your folder structure in [CMakeLists.txt](CMakeLists.txt). Default is set to ``target_link_libraries(simple1_lib_useage ~/git_clones/my_cpp/simple1_lib/build/libSimple.so)``.

    ```
    mkdir build
    cd build
    cmake ..
    make
    ./simple1_lib_useage
    ```
