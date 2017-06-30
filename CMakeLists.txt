project(focus)
cmake_minimum_required(VERSION 2.8)
find_package(OpenCV REQUIRED)

include_directories(./include)
file(GLOB SRC src/*.h* src/*.c* include/*.h*)
add_executable(focus_exe ${SRC} ${include})
target_link_libraries(focus_exe ${OpenCV_LIBS})

