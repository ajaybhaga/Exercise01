cmake_minimum_required(VERSION 3.15)
project(MunvoAgentSim)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SOURCE_DIR /Users/badzindagi/dev/MunvoAgentSim)

#SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

#LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/lib )

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

IF(APPLE)
    #SET(GUI_TYPE MACOSX_BUNDLE)
    INCLUDE_DIRECTORIES ( /Developer/Headers/FlatCarbon )
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    MARK_AS_ADVANCED (CARBON_LIBRARY
            QUICKTIME_LIBRARY
            APP_SERVICES_LIBRARY)
    SET(EXTRA_LIBS ${CARBON_LIBRARY} ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})
ENDIF (APPLE)

set (CMAKE_DEBUG_POSTFIX "_d")

#if(WIN32)
 #   set(COMMON_LIBS optimized glfw3 debug glfw3_d ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${COCOA_LIBRARY})
#elseif (UNIX)
#    find_package(PkgConfig REQUIRED)
#    pkg_check_modules(GLFW REQUIRED glfw3)
#    set(COMMON_LIBS glfw3 dl ${COCOA_LIBRARY})
#endif()

set(COMMON_LIBS ${COMMON_LIBS} ${EXTRA_LIBS})

set(RUN_DIR ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_C_COMPILER "/usr/local/Cellar/llvm/9.0.0/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/9.0.0/bin/clang++")
set(OPENMP_LIBRARIES "/usr/local/Cellar/llvm/9.0.0/lib")
set(OPENMP_INCLUDES "/usr/local/Cellar/llvm/9.0.0/include")


set(cyclonelib ${CMAKE_SOURCE_DIR}/cyclone/body.cpp ${CMAKE_SOURCE_DIR}/cyclone/collide_coarse.cpp ${CMAKE_SOURCE_DIR}/cyclone/collide_fine.cpp ${CMAKE_SOURCE_DIR}/cyclone/contacts.cpp ${CMAKE_SOURCE_DIR}/cyclone/core.cpp ${CMAKE_SOURCE_DIR}/cyclone/fgen.cpp ${CMAKE_SOURCE_DIR}/cyclone/joints.cpp ${CMAKE_SOURCE_DIR}/cyclone/particle.cpp ${CMAKE_SOURCE_DIR}/cyclone/pcontacts.cpp ${CMAKE_SOURCE_DIR}/cyclone/pfgen.cpp ${CMAKE_SOURCE_DIR}/cyclone/plinks.cpp ${CMAKE_SOURCE_DIR}/cyclone/pworld.cpp ${CMAKE_SOURCE_DIR}/cyclone/random.cpp ${CMAKE_SOURCE_DIR}/cyclone/world.cpp)
set(winlib ${CMAKE_SOURCE_DIR}/app.cpp ${CMAKE_SOURCE_DIR}/cyclone/timing.cpp)

include_directories("${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/cyclone"
        "${CMAKE_SOURCE_DIR}/glut")

add_executable(MunvoAgentSim main.cpp ai/genotype.cpp ai/genotype.h util/random_d.h ai/genetic_algorithm.cpp ai/genetic_algorithm.h ai/evolution_manager.cpp ai/evolution_manager.h ai/agent.cpp ai/agent.h util/listener.cpp util/listener.h ai/neural_layer.cpp ai/neural_layer.h ai/neural_network.cpp ai/neural_network.h util/math_helper.cpp util/math_helper.h util/event.cpp util/event.h ai/agent_controller.cpp ai/agent_controller.h shared_libs.h util/grid.cpp util/grid.h ai/sensor.cpp ai/sensor.h ${winlib} ${cyclonelib} gl/glut.h environment.cpp environment.h ai/agent_movement.cpp ai/agent_movement.h block.h ai/fsm_event_data.cpp ai/fsm_event_data.h ai/fsm.cpp ai/fsm.h util/semaphore.h ai/agent_fsm.cpp ai/agent_fsm.h)
target_link_libraries(MunvoAgentSim ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
#target_compile_options(MunvoAgentSim PUBLIC -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk)


#add_executable(MunvoAgentSim WIN32 src/${EXAMPLE}/${EXAMPLE}.cpp)
#set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
#target_link_libraries(MunvoAgentSim ${COMMON_LIBS})
#target_link_libraries(MunvoAgentSim "-lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework CoreFoundation")

