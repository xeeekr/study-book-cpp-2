add_executable(ch4-2-2 ch4-2-2-random.cpp)

find_package(SDL REQUIRED COMPONENTS SDL)
add_executable(ch4-2-1 ch4-2-1-mandelbrot.cpp)
target_link_libraries(ch4-2-1 PRIVATE SDL::SDL)


