cmake_minimum_required(VERSION 3.15)
project(EANN_Simple)

set(CMAKE_CXX_STANDARD 14)

#SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(CMAKE_SOURCE_DIR /Users/badzindagi/dev/MayaBrain)

set(cyclonelib ${CMAKE_SOURCE_DIR}/cyclone/body.cpp ${CMAKE_SOURCE_DIR}/cyclone/collide_coarse.cpp ${CMAKE_SOURCE_DIR}/cyclone/collide_fine.cpp ${CMAKE_SOURCE_DIR}/cyclone/contacts.cpp ${CMAKE_SOURCE_DIR}/cyclone/core.cpp ${CMAKE_SOURCE_DIR}/cyclone/fgen.cpp ${CMAKE_SOURCE_DIR}/cyclone/joints.cpp ${CMAKE_SOURCE_DIR}/cyclone/particle.cpp ${CMAKE_SOURCE_DIR}/cyclone/pcontacts.cpp ${CMAKE_SOURCE_DIR}/cyclone/pfgen.cpp ${CMAKE_SOURCE_DIR}/cyclone/plinks.cpp ${CMAKE_SOURCE_DIR}/cyclone/pworld.cpp ${CMAKE_SOURCE_DIR}/cyclone/random.cpp ${CMAKE_SOURCE_DIR}/cyclone/world.cpp)
set(winlib ${CMAKE_SOURCE_DIR}/app.cpp ${CMAKE_SOURCE_DIR}/timing.cpp)

include_directories("${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/cyclone"
        "${CMAKE_SOURCE_DIR}/glut")

add_executable(EANN_Simple main.cpp genotype.cpp genotype.h random_d.h genetic_algorithm.cpp genetic_algorithm.h evolution_manager.cpp evolution_manager.h agent.cpp agent.h listener.cpp listener.h neural_layer.cpp neural_layer.h neural_network.cpp neural_network.h math_helper.cpp math_helper.h event.cpp event.h agent_controller.cpp agent_controller.h shared_libs.h grid.cpp grid.h sensor.cpp sensor.h ${winlib} ${cyclonelib} gl/glut.h environment.cpp environment.h agent_movement.cpp agent_movement.h block.h fsm_event_data.cpp fsm_event_data.h fsm.cpp fsm.h semaphore.h)
target_link_libraries(EANN_Simple ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_compile_options(EANN_Simple PUBLIC -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk)
