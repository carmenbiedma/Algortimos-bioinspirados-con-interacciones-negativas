CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(trajectory)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
)
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
SET(SRC
  da.cpp)
 SET(CMAKE_TYPE_BUILD DEBUG)
add_executable(main main.cpp ${SRC})
target_link_libraries(main ${ARMADILLO_LIBRARIES})	
