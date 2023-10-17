cmake_minimum_required(VERSION 3.20)
project(rohdeschwarz)


# windows __declspec work-around
if (WIN32 AND BUILD_SHARED_LIBS)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


# find boost components
find_package(Boost 1.83.0 REQUIRED COMPONENTS filesystem system)


# rohdeschwarz

add_library(
  rohdeschwarz
  src/busses/socket/address.cpp
  src/busses/socket/buffer.cpp
  src/busses/socket/socket.cpp
  src/busses/visa/cvisa.cpp
  src/busses/visa/visa.cpp
  src/busses/bus.cpp
  src/instruments/vna/channel.cpp
  src/instruments/vna/data_format.cpp
  src/instruments/vna/display.cpp
  src/instruments/vna/preserve_data_format.cpp
  src/instruments/vna/trace.cpp
  src/instruments/vna/vna.cpp
  src/instruments/instrument.cpp
  src/instruments/preserve_timeout.cpp
  src/scpi/block_data.cpp
  src/scpi/bool.cpp
  src/scpi/index_name.cpp
  src/helpers.cpp
)


target_link_libraries(
  rohdeschwarz
  PUBLIC
  Boost::headers
  Boost::filesystem
  Boost::system
)


target_include_directories(
  rohdeschwarz
  PUBLIC
  include
  include/rs-visa
)


install(TARGETS rohdeschwarz)
install(
  DIRECTORY   include
  DESTINATION .
)
