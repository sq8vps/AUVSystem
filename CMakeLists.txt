project(AUVSystem)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include_directories(external .)

include_directories("/opt/ros/noetic/include")

set(NAME Commons)

set(SOURCES
    CommonEnums.cpp
    jsonCommonFunctions.cpp
    NodeBase.cpp
    ROSEnums.cpp
)

set(HEADERS
    CommonEnums.h
    jsonCommonFunctions.h
    NodeBase.h
    ROSEnums.h
)

set(CMAKE_PREFIX_PATH _PATH "/opt/ros/noetic;${CMAKE_MODULE_PATH}")

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs geometry_msgs rospy)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

#add_subdirectory(AdditionalCameraProcessor)
add_subdirectory(Debug)
add_subdirectory(EmergencyRestartProtocol)
add_subdirectory(HealthCheck)
add_subdirectory(MainLogic)
add_subdirectory(PositioningSLAM)
add_subdirectory(TCPNode)
add_subdirectory(TrajectoryPlanner)
add_subdirectory(ThrusterRegulator)
add_subdirectory(UDPNode)
add_subdirectory(external)

add_library(${NAME} ${SOURCES} ${HEADERS})
set_target_properties( ${NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${NAME}/" )

target_link_libraries(${NAME} Eigen3::Eigen )
