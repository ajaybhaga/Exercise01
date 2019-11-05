cmake_minimum_required(VERSION 3.15)
project(EANN_Simple)

set(CMAKE_CXX_STANDARD 14)

#SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

#add_executable(Test main.cpp)


#target_include_directories(cyclonelib PUBLIC cyclone)


#target_include_directories(calclib PUBLIC include)
#target_compile_features(cyclonelib PUBLIC cxx_std_11)

set(CMAKE_SOURCE_DIR /Users/badzindagi/dev/MayaBrain)

set(cyclonelib ${CMAKE_SOURCE_DIR}/cyclone/body.cpp ${CMAKE_SOURCE_DIR}/cyclone/collide_coarse.cpp ${CMAKE_SOURCE_DIR}/cyclone/collide_fine.cpp ${CMAKE_SOURCE_DIR}/cyclone/contacts.cpp ${CMAKE_SOURCE_DIR}/cyclone/core.cpp ${CMAKE_SOURCE_DIR}/cyclone/fgen.cpp ${CMAKE_SOURCE_DIR}/cyclone/joints.cpp ${CMAKE_SOURCE_DIR}/cyclone/particle.cpp ${CMAKE_SOURCE_DIR}/cyclone/pcontacts.cpp ${CMAKE_SOURCE_DIR}/cyclone/pfgen.cpp ${CMAKE_SOURCE_DIR}/cyclone/plinks.cpp ${CMAKE_SOURCE_DIR}/cyclone/pworld.cpp ${CMAKE_SOURCE_DIR}/cyclone/random.cpp ${CMAKE_SOURCE_DIR}/cyclone/world.cpp)
set(winlib ${CMAKE_SOURCE_DIR}/app.cpp ${CMAKE_SOURCE_DIR}/timing.cpp)
#set(cyclonelib ${CMAKE_SOURCE_DIR}/cyclone/core.cpp ${CMAKE_SOURCE_DIR}/cyclone/cyclone/core.h ./cyclone/random.cpp ./cyclone/random.h ./cyclone/cyclone.h)

#set(HEADER_FILES ${YOUR_DIRECTORY}/file1.h ${YOUR_DIRECTORY}/file2.h)

#add_compile_options("-framework GLUT -framework OpenGL -framework Cocoa")
#link_libraries("-framework GLUT -framework OpenGL -framework Cocoa")

include_directories("${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/cyclone"
        "${CMAKE_SOURCE_DIR}/glut")

add_executable(EANN_Simple main.cpp genotype.cpp genotype.h random_d.h genetic_algorithm.cpp genetic_algorithm.h evolution_manager.cpp evolution_manager.h agent.cpp agent.h listener.cpp listener.h neural_layer.cpp neural_layer.h neural_network.cpp neural_network.h math_helper.cpp math_helper.h event.cpp event.h agent_controller.cpp agent_controller.h shared_libs.h grid.cpp grid.h sensor.cpp sensor.h ${winlib} ${cyclonelib} gl/glut.h fracture.cpp)
#target_include_directories(EANN_Simple PRIVATE cyclone)
target_link_libraries(EANN_Simple ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})


#target_link_libraries(EANN_Simple PUBLIC cyclonelib)
#add_library(calclib STATIC src/calclib.cpp include/calc/lib.hpp)

#add_executable(calc apps/calc.cpp)
#target_link_libraries(calc PUBLIC calclib)