cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(syringe_pump)

target_include_directories(app PRIVATE 
        include 
        include/Hal)

target_sources(app PRIVATE
    src/main.cpp
    src/pump_state_machine.cpp
    src/command_parser.cpp
    src/alarm_manager.cpp
    src/volume_tracker.cpp
    src/hal/gpio_zephyr.cpp           
    src/hal/stepper_driver_zephyr.cpp 
    src/hal/uart_zephyr.cpp           
    src/states/state_idle.cpp
    src/states/state_priming.cpp
    src/states/state_infusing.cpp
    src/states/state_paused.cpp
    src/states/state_occlusion_alarm.cpp
    src/states/state_complete.cpp
)