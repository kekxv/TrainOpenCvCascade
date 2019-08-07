#CMakeLists.txt
#
#:Author: k
#:Email: k@hlst
#:Date: 2019-08-05 21:38
#
cmake_minimum_required(VERSION 3.1.2 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})

if (APPLE)
    link_directories(. /usr/local/lib/)
endif ()

add_executable(resizeImg
        resizeImg.cpp
        )
TARGET_LINK_LIBRARIES(resizeImg dl ${OpenCV_LIBS})

add_executable(testCascade
        testCascade.cpp
        )
TARGET_LINK_LIBRARIES(testCascade dl ${OpenCV_LIBS})
