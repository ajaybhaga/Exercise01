cmake_minimum_required(VERSION 3.15)
project(EANN_Simple)

set(CMAKE_CXX_STANDARD 14)

add_executable(EANN_Simple main.cpp genotype.cpp genotype.h random_d.h genetic_algorithm.cpp genetic_algorithm.h evolution_manager.cpp evolution_manager.h agent.cpp agent.h listener.cpp listener.h neural_layer.cpp neural_layer.h neural_network.cpp neural_network.h math_helper.cpp math_helper.h event.cpp event.h agent_controller.cpp agent_controller.h shared_libs.h)