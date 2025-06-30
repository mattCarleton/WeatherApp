cmake_minimum_required(VERSION 3.16)

project(WeatherApp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Test)

# Main project
add_executable(WeatherApp
  main.cpp
)
target_link_libraries(WeatherApp Qt${QT_VERSION_MAJOR}::Core)

# Test executable
add_executable(all_tests
  tests/all_tests.cpp
  tests/test_test.h tests/test_test.cpp)
target_link_libraries(all_tests Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS WeatherApp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
