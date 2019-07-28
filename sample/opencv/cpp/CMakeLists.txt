cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
project( DisplayImage )
#find_package( OpenCV REQUIRED )
#message( ${OpenCV_LIBS} )

find_package( GTK2 REQUIRED )
#message( ${GTK2_LIBRARIES} )

#message(${OpenCV_INCLUDE_DIRS})
#include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( /home/bai/3rdparty/opencv-4.1.1/build/lnx/include/opencv4 )

#add_subdirectory(cpp)

set(opencv_dir /home/bai/3rdparty/opencv-4.1.1/build/lnx/lib)
set(opencv_3rd_dir /home/bai/3rdparty/opencv-4.1.1/build/lnx/lib/opencv4/3rdparty)
link_directories( ${opencv_dir} ${opencv_3rd_dir} )

add_executable( DisplayImage DisplayImage.cpp )

# add_library(lib-png STATIC IMPORTED)
# set_target_properties(lib-png PROPERTIES IMPORTED_LOCATION
# ${opencv_3rd_dir}/liblibpng.a)

# add_library(lib-ippicv STATIC IMPORTED)
# set_target_properties(lib-ippicv PROPERTIES IMPORTED_LOCATION
# ${opencv_3rd_dir}/libippicv.a)

target_link_libraries( DisplayImage 
    libopencv_imgcodecs.a 
    libopencv_imgproc.a
    libopencv_highgui.a
    libopencv_core.a
    liblibpng.a 
    liblibjpeg-turbo.a
    liblibjasper.a
    libade.a
    libquirc.a
    libippiw.a
    libippicv.a
    libIlmImf.a
    libittnotify.a
    libzlib.a
    -ldl
    -lpthread
    ${GTK2_LIBRARIES}
    )
    
# target_link_libraries( DisplayImage dl)
