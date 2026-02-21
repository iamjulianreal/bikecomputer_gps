cmake_minimum_required(VERSION 3.16)
project(BikeComputer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Qml Quick Positioning)

add_executable(bikecomputer
  main.cpp
  GpsPositionSource.cpp
  GpxLogger.cpp
  app.qrc
  gpio_reader.h
  GpsPositionSource.h
  GpxLogger.h
  MapController.h
  MapController.cpp
)

# libgpiod
find_library(GPIOD_LIB gpiod REQUIRED)

# pigpiod client library (optional at build-time; source has fallback if header missing)
find_library(PIGPIOD_IF2_LIB pigpiod_if2)

# Optional: point this at your libosmscout checkout/build
set(OSMSCOUT_SOURCE_ROOT "" CACHE PATH "Path to libosmscout source root")
set(OSMSCOUT_BUILD_ROOT "" CACHE PATH "Path to libosmscout build root")

if(OSMSCOUT_SOURCE_ROOT)
  target_include_directories(bikecomputer PRIVATE
    "${OSMSCOUT_SOURCE_ROOT}/libosmscout-client-qt/include"
    "${OSMSCOUT_SOURCE_ROOT}/libosmscout/include"
  )
endif()

if(OSMSCOUT_BUILD_ROOT)
  target_link_directories(bikecomputer PRIVATE
    "${OSMSCOUT_BUILD_ROOT}/libosmscout-client-qt"
    "${OSMSCOUT_BUILD_ROOT}/libosmscout"
  )

  set_target_properties(bikecomputer PROPERTIES
    BUILD_RPATH "${OSMSCOUT_BUILD_ROOT}/libosmscout-client-qt;${OSMSCOUT_BUILD_ROOT}/libosmscout"
    INSTALL_RPATH "${OSMSCOUT_BUILD_ROOT}/libosmscout-client-qt;${OSMSCOUT_BUILD_ROOT}/libosmscout"
  )
endif()

target_link_libraries(bikecomputer PRIVATE
  Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::Positioning
  ${GPIOD_LIB}
  osmscout_client_qt
)

if(PIGPIOD_IF2_LIB)
  target_link_libraries(bikecomputer PRIVATE ${PIGPIOD_IF2_LIB})
endif()
