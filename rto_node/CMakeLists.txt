cmake_minimum_required(VERSION 3.5)
project(rto_node)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

list(APPEND CMAKE_MODULE_PATH "/usr/local/robotino/api2/cmake" "/opt/robotino/cmake")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(RobotinoAPI2 REQUIRED)
find_package(rto_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


include_directories(
  include/rto_node
  /usr/local/robotino/api2
)

add_executable(
  rto_node
  src/rto_node.cpp
  src/AnalogInputArrayROS.cpp
  src/BumperROS.cpp
  src/CameraROS.cpp
  src/ComROS.cpp
  src/DigitalInputArrayROS.cpp
  src/DigitalOutputArrayROS.cpp
  src/DistanceSensorArrayROS.cpp
  src/EncoderInputROS.cpp
  src/LaserRangeFinderROS.cpp
  src/MotorArrayROS.cpp
  src/OdometryROS.cpp
  src/OmniDriveROS.cpp
  src/PowerManagementROS.cpp
  src/RTONode.cpp
)

target_link_libraries(
  rto_node
  ${REC_ROBOTINO_API2_LIBRARY}
)


ament_target_dependencies(rto_node rclcpp rto_msgs std_msgs geometry_msgs sensor_msgs tf2 tf2_ros nav_msgs builtin_interfaces) 

add_executable(
  rto_laserrangefinder_node
  src/rto_laserrangefinder_node.cpp
  src/ComROS.cpp
  src/LaserRangeFinderROS.cpp
  src/RTOLaserRangeFinderNode.cpp
)

ament_target_dependencies(rto_laserrangefinder_node rclcpp rto_msgs std_msgs geometry_msgs sensor_msgs tf2 tf2_ros builtin_interfaces) 


target_link_libraries(
  rto_laserrangefinder_node
  ${REC_ROBOTINO_API2_LIBRARY}
)

add_executable(
  rto_camera_node
  src/rto_camera_node.cpp
  src/ComROS.cpp
  src/CameraROS.cpp
  src/RTOCameraNode.cpp
)

ament_target_dependencies(rto_camera_node rclcpp rto_msgs std_msgs geometry_msgs sensor_msgs tf2 tf2_ros builtin_interfaces) 

target_link_libraries(
  rto_camera_node
  ${REC_ROBOTINO_API2_LIBRARY}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  rto_node
  rto_camera_node
  rto_laserrangefinder_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
