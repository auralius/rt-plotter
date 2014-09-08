project(rt-plotter)

add_executable(rt-plotter main.cpp shm-access.cpp rt-plotter.cpp)

install(TARGETS rt-plotter RUNTIME DESTINATION bin)

target_link_libraries(rt-plotter fltk config mgl-wnd mgl pthread)

set (CMAKE_CXX_FLAGS -fpermissive )