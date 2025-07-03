cmake_minimum_required(VERSION 3.16)

project(WeatherApp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Network Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network Test)

# Main project
add_executable(WeatherApp
  main.cpp
  weather_manager.h weather_manager.cpp
)
target_link_libraries(WeatherApp
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
)

# Test executable
add_executable(all_tests
  tests/all_tests.cpp
  tests/test_weather_manager.h tests/test_weather_manager.cpp
  weather_manager.cpp)
target_link_libraries(all_tests
  Qt${QT_VERSION_MAJOR}::Test
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS WeatherApp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
