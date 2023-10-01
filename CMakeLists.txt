cmake_minimum_required(VERSION 3.20)
project(BoostTcpClient)


# TODO: set boost options?
# set(Boost_USE_MULTITHREADED  ON)
# set(Boost_USE_STATIC_LIBS    $<NOT:BUILD_SHARED_LIBS>)
# set(Boost_USE_STATIC_RUNTIME $<NOT:BUILD_SHARED_LIBS)


# find boost components
find_package(Boost REQUIRED COMPONENTS system)


# rohdeschwarz socket library
add_library(
  rohdeschwarz
  src/address.cpp
  src/buffer.cpp
  src/socket.cpp
)
target_link_libraries(rohdeschwarz PUBLIC Boost::headers Boost::system)
target_include_directories(rohdeschwarz PUBLIC include)
install(TARGETS rohdeschwarz)
install(DIRECTORY include DESTINATION .)


# main
add_executable(
  main
  src/main.cpp
)
target_link_libraries(main rohdeschwarz)
install(TARGETS main)
