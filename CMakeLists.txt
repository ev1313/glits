project(glits)
cmake_minimum_required(VERSION 3.0)

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

find_package(epoxy REQUIRED)
find_package(OpenCV REQUIRED)

function(setup_target NAME)
  set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 14)
  set_property(TARGET ${NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
  target_compile_options(${NAME} PRIVATE -Wall -Wextra)
  target_compile_options(${NAME} PRIVATE $<$<CONFIG:DEBUG>:-ggdb -O2>)
  target_compile_options(${NAME} PRIVATE $<$<CONFIG:RELEASE>:-O3 -NDEBUG>)
endfunction(setup_target)

set(GLITS_SRC
  src/glits/glits.cpp
  )

set(GLITS_INC
  glits/glits.hpp
	)

add_library(${PROJECT_NAME} STATIC ${GLITS_INC} ${GLITS_SRC})
setup_target(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${EPOXY_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} "atomic")

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

add_subdirectory(tests)
