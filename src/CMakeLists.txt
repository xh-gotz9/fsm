set(PATH_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${PATH_ROOT})

aux_source_directory(./demo MAIN_SRC)
add_executable(fsm-demo ${MAIN_SRC})
target_link_libraries(fsm-demo gtest gtest_main)
