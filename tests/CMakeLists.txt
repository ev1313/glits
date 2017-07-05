find_package(X11 REQUIRED)

option(GENERATE_TESTS "generate the test data out of the actual state." OFF)

if(GENERATE_TESTS)
  add_definitions(-DGLITS_GENERATE_TESTS=true)
else(GENERATE_TESTS)
  add_definitions(-DGLITS_GENERATE_TESTS=false)
endif(GENERATE_TESTS)

set(TEST_SRC
  glits/x11window.cpp
  glits/testimage.cpp
  main.cpp
  )

add_executable(tests ${TEST_SRC})
setup_target(tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}\\bin)
file(COPY testdata DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Catch/include)
target_link_libraries(tests X11)
target_link_libraries(tests glits)
target_link_libraries(tests "atomic")
