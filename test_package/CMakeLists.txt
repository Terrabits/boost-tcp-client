cmake_minimum_required(VERSION 3.20)
project(PackageTest CXX)


# find rohdeschwarz
find_package(rohdeschwarz REQUIRED)


# executable
add_executable(main src/main.cpp)
target_link_libraries(main rohdeschwarz::rohdeschwarz)
