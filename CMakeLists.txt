cmake_minimum_required(VERSION 3.20)
project(rohdeschwarz)


# windows __declspec work-around
if (WIN32 AND BUILD_SHARED_LIBS)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


# find boost components
find_package(Boost 1.83.0 REQUIRED COMPONENTS system)


# rohdeschwarz
add_library(
  rohdeschwarz
  src/busses/socket/address.cpp
  src/busses/socket/buffer.cpp
  src/busses/socket/socket.cpp
)
target_link_libraries(rohdeschwarz PUBLIC Boost::headers Boost::system)
target_include_directories(rohdeschwarz PUBLIC include)
install(TARGETS rohdeschwarz)
install(DIRECTORY include DESTINATION .)
