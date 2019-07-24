cmake_minimum_required(VERSION 3.0)

project(flowerOfLife)

FIND_PACKAGE(OpenCV 4 REQUIRED)
message("OpenCV: ${OpenCV_INCLUDE_DIRS}")

find_package(ImageMagick COMPONENTS Magick++ 
                                     #MagickWand
                                     MagickCore
                                     #animate
                                     #compare
                                     #composite
                                     #conjure
                                     #convert
                                     #display
                                     #identify
                                     #import
                                     #mogrify
                                     #montage
                                     #stream
                                     )
message("imageMagicFound is ${ImageMagick_FOUND}")
message("ImageMagick include dirs: ${ImageMagick_INCLUDE_DIRS}")
message("ImageMagick libraries: ${ImageMagick_LIBRARIES}")

# Configure compiler options ...
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    message("-- configuring clang options")
    set(CMAKE_CXX_FLAGS "-arch x86_64 -std=c++11 -stdlib=libc++ -Wno-deprecated-declarations -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

    message("-- configuring gcc options")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

endif()


#project include dir
set(INCLUDE_DIR "./source/headers")
message(INCLUDE_DIR " ${INCLUDE_DIR}")
# #easylogging include dir
# set(EASYLOGGING_INCLUDE_DIR "external/easyloggingpp")
# #lohmann include dir
# set(NLOHMANN_INCLUDE_DIR "external/nlohmann")


#add project executables

add_executable(${PROJECT_NAME}  ./source/flowerOfLife.cpp
                                # ./external/easyloggingpp/easylogging++.cc
                               )

target_link_libraries(${PROJECT_NAME}
                         ${OpenCV_LIBS}
                         ${ImageMagick_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR} ${EASYLOGGING_INCLUDE_DIR} ${NLOHMANN_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS} ${ImageMagick_INCLUDE_DIRS})
