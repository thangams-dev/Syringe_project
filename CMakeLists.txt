cmake_minimum_required(VERSION 3.20)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(syringe_pump)
target_sources(app PRIVATE main.cpp)