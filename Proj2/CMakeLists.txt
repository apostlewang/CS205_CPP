CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)
project(cnn)

set(CMAKE_CXX_STANDARD 11)

IF(APPLE)
    set(OPENMP_LIBRARIES "/usr/local/Cellar/libomp/10.0.1/lib")
    set(OPENMP_INCLUDES "/usr/local/Cellar/libomp/10.0.1/include")

    link_directories("${OPENMP_LIBRARIES}")

    set(CMAKE_CXX_FLAGS "-Xpreprocessor -fopenmp -lomp -Wno-unused-command-line-argument -O3")
    set(CMAKE_C_FLAGS "-Xpreprocessor -fopenmp -lomp -Wno-unused-command-line-argument -O3")
ELSEIF(LINUX)
    set(CMAKE_CXX_FLAGS "-O3 ${OpenMP_CXX_FLAGS}")
ENDIF()

set(LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS} ${LOCAL_INCLUDE_DIR} ${OPENMP_INCLUDES})

#FIND_PACKAGE(OpenMP REQUIRED) 
FIND_PACKAGE(OpenCV REQUIRED) 

add_executable(cnn cnn.cpp main.cpp)

TARGET_LINK_LIBRARIES(cnn ${OpenCV_LIBS})