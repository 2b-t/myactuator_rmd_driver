cmake_minimum_required(VERSION 3.20)
project(myactuator_rmd)

option(PYTHON_BINDINGS "Building Python bindings" OFF)
option(BUILD_TESTING "Build unit and integration tests" OFF)
option(SETUP_TEST_IFNAME "Set-up the test VCAN interface automatically" OFF)

if(NOT UNIX)
  message(FATAL_ERROR "Currently this driver only supports Linux!")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(ament_cmake)
if(ament_cmake_FOUND)
  message(STATUS "Ament CMake detected.")
else()
  message(WARNING "Ament CMake not found!")
endif()
include(ConfigExtras.cmake)

include_directories(
  include/
)

add_library(myactuator_rmd SHARED
  src/can/node.cpp
  src/can/utilities.cpp
  src/protocol/requests.cpp
  src/protocol/responses.cpp
  src/driver.cpp
)
set(MYACTUATOR_RMD_LIBRARIES "")
target_link_libraries(myactuator_rmd ${MYACTUATOR_RMD_LIBRARIES})
install(TARGETS
  myactuator_rmd
  DESTINATION lib/${PROJECT_NAME}
)

if(PYTHON_BINDINGS)
  pybind11_add_module(pymyactuator_rmd bindings/myactuator_rmd.cpp)
  target_link_libraries(pymyactuator_rmd PRIVATE myactuator_rmd)
  set_target_properties(pymyactuator_rmd PROPERTIES OUTPUT_NAME myactuator_rmd)
  
  install(TARGETS
    pymyactuator_rmd
    DESTINATION lib/${PROJECT_NAME}
  )
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  enable_testing()

  find_package(Boost 1.40.0 REQUIRED COMPONENTS program_options)
  add_executable(can_node
    test/can_node.cpp
  )
  target_link_libraries(can_node ${Boost_PROGRAM_OPTIONS_LIBRARY} myactuator_rmd)

  find_package(GTest REQUIRED)
  set(MYACTUATOR_RMD_TEST_LIBRARIES ${MYACTUATOR_RMD_LIBRARIES} myactuator_rmd GTest::gmock GTest::gtest pthread)
  add_executable(run_tests
    test/can/utilities_test.cpp
    test/protocol/requests_test.cpp
    test/protocol/responses_test.cpp
    test/mock/actuator_adaptor.cpp
    test/mock/actuator_mock.cpp
    test/mock/driver_actuator_test.cpp
    test/driver_test.cpp
    test/run_tests.cpp
  )
  target_compile_definitions(run_tests PUBLIC NDEBUG)
  gtest_discover_tests(run_tests
    TEST_SUFFIX .noArgs
    TEST_LIST noArgsTests
  )
  set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
  target_link_libraries(run_tests ${MYACTUATOR_RMD_TEST_LIBRARIES})
  if (SETUP_TEST_IFNAME)
    set(VCAN_IFNAME "vcan_test")
    configure_file("CTestCustom.cmake.in" ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
  endif()
endif()

if(ament_cmake_FOUND)
  ament_package(CONFIG_EXTRAS ConfigExtras.cmake)
endif()
