cmake_minimum_required(VERSION 3.14)
project(my_project)
set(CMAKE_CXX_STANDARD 20)

add_definitions(-DUNIT_TEST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

find_package(GTest REQUIRED)

set(SRC_FILES
    ../src/alarm_manager.cpp
    ../src/command_parser.cpp
    ../src/pump_state_machine.cpp
    ../src/volume_tracker.cpp
    ../src/uart_zephyr.cpp
    ../src/states/state_complete.cpp
    ../src/states/state_idle.cpp
    ../src/states/state_infusing.cpp
    ../src/states/state_occlusion_alarm.cpp
    ../src/states/state_paused.cpp
    ../src/states/state_priming.cpp
    stubs/stub_file.cpp
)

set(INCLUDE_DIRS
    ../include
    ../include/Hal
    mocks/
)

set(LINK_LIBS
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
)

foreach(TEST test_alarm test_command test_pump_state_machine test_states test_volume)
    add_executable(${TEST} ${SRC_FILES} ${TEST}.cpp)
    target_include_directories(${TEST} PRIVATE ${INCLUDE_DIRS})
    target_link_libraries(${TEST} PRIVATE ${LINK_LIBS})
endforeach()

# Coverage target
find_program(LCOV lcov)
find_program(GENHTML genhtml)

add_custom_target(coverage
    COMMAND lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch
    COMMAND lcov --remove coverage.info '/usr/*' '*/tests/stubs/*' --output-file coverage_filtered.info
    COMMAND genhtml coverage_filtered.info --output-directory coverage_html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)