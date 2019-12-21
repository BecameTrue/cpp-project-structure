# cpp-project-structure

Clone to build C++ project. Testing is available with [GoogleTest](https://github.com/google/googletest).

## Contents of directory

```
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build
├── include
│   └── main.hpp
├── src
│   └── main.cpp
└── test
    ├── CMakeLists.txt
    ├── googletest
    ├── include
    └── src
```

1. `build` : Directory for building project. Call `cmake .. && make` in this directory to build project. The executable file will be placed here and executable file for testing will be placed in the `test` folder, which will be generated after build is done.
2. `include` : Directory for header files.
3. `src` : Directory for cpp files.
4. `test` : Directory for testing.
   1. `test/include` : Directory for header files to run tests.
   2. `test/src` : Directory for cpp files to run tests.
   3. `test/googletest` : Submodule included by git

## CMakeLists.txt

### Root CMakeLists.txt

```cmake
# SET MINIMUM VERSION OF CMAKE REQUIRED
cmake_minimum_required(VERSION 3.10)

# SET PROJECT NAME
# THIS PROJECT USES LANGUAGE C++
project("PROJECT_NAME_HERE" LANGUAGES CXX)

# BEING PLACED SOMEWHERE IN THE PRIMARY MEMORY, 
# EXECUTES PROPERLY REGARDLESS OF ITS ABSOLUTE ADDRESS.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# IF THIS PROJECT SHOULD BE TESTED
option(SHOULD_TEST "Build the tests" ON)
if(SHOULD_TEST)
    enable_testing()
    # ADD SUBDIRECTORY IN ORDER TO USE TESTING FRAMEWORK
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
    # SET SRC_DIR AS ${CMAKE_CURRENT_SOURCE_DIR}/src
endif()

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# THIS PROJECT WILL MAKE EXECUTABLE FILE WITH NAME OF "EXECUTABLE_FILE_NAME_HERE"
set(EXE "EXECUTABLE_FILE_NAME_HERE")
add_executable(
    ${EXE}
    ${SRC_DIR}/main.cpp
    # LIST OTHER CPP FILES HERE
)

# EXECUTABLE FILE SHOULD BE COMPILED WITH HEARDER FILES IN /include
target_include_directories(
    ${EXE} # INCLUDE IN EXECUTABLE FILE
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

Define custom project name by changing **"PROJECT_NAME_HERE"**. If this project needs testing, just change the option.

`SHOULD_TEST "..." ON` => `SHOULD_TEST "..." OFF`

Also, define your own executable file name by changing **"EXECUTABLE_FILE_NAME_HERE"**.

_Notice that your executable file for testing will be generated in `build/test`._

### test/CMakeLists.txt

```cmake
# SET TEST_SRC_DIR AS ${CMAKE_CURRENT_SOURCE_DIR}/src
set(TEST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# THIS PROJECT WILL MAKE EXECUTABLE FILE WITH NAME OF "TEST_EXECUTABLE_FILE_NAME_HERE"
set(TEST_EXE "TEST_EXECUTABLE_FILE_NAME_HERE")
add_executable(
    ${TEST_EXE}
    ${TEST_SRC_DIR}/test.cpp
    # LIST OTHER CPP FILES HERE
    # ${PROJECT_SOURCE_DIR}/src/CAN_USE_FILES_OF_MAIN_SRC.cpp
)

# EXECUTABLE FILE SHOULD BE COMPILED WITH HEARDER FILES IN /include
target_include_directories(
    ${TEST_EXE} 
    # INCLUDE HEADER FILES IN EXECUTABLE FILE 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    # INCLUDE HEADER FILES OF MAIN INCLUDE FOLDER
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# USE GOOGLETEST AS TESTING FRAMEWORK
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

# LINK LIBRARIES
target_link_libraries(
    ${TEST_EXE}
    gtest_main
    gmock_main
)
```

To use codes in root directory on testing, append it like following code. 

```cmake
add_executable(
    ${TEST_EXE}
    ${TEST_SRC_DIR}/test.cpp
    # LIST OTHER CPP FILES HERE
    ${PROJECT_SOURCE_DIR}/src/FILE_NAME.cpp # <- LIKE THIS
)
```

---

## Try

After first downloading/cloning this project,

```bash
hello@world:~/.../cpp-project-structure$ cd build
hello@world:~/.../cpp-project-structure/build$ cmake .. && make
```

Results,

```bash
-- The CXX compiler identification is GNU 7.4.0
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- The C compiler identification is GNU 7.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Found PythonInterp: /usr/bin/python (found version "2.7.17") 
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - not found
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE  
-- Configuring done
-- Generating done
-- Build files have been written to: /.../cpp-project-structure/build
Scanning dependencies of target EXECUTABLE_FILE_NAME_HERE
[  8%] Building CXX object CMakeFiles/EXECUTABLE_FILE_NAME_HERE.dir/src/main.cpp.o
[ 16%] Linking CXX executable EXECUTABLE_FILE_NAME_HERE
[ 16%] Built target EXECUTABLE_FILE_NAME_HERE
Scanning dependencies of target gtest
[ 25%] Building CXX object test/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 33%] Linking CXX static library ../../../lib/libgtest.a
[ 33%] Built target gtest
Scanning dependencies of target gtest_main
[ 41%] Building CXX object test/googletest/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 50%] Linking CXX static library ../../../lib/libgtest_main.a
[ 50%] Built target gtest_main
Scanning dependencies of target gmock
[ 58%] Building CXX object test/googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 66%] Linking CXX static library ../../../lib/libgmock.a
[ 66%] Built target gmock
Scanning dependencies of target gmock_main
[ 75%] Building CXX object test/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[ 83%] Linking CXX static library ../../../lib/libgmock_main.a
[ 83%] Built target gmock_main
Scanning dependencies of target TEST_EXECUTABLE_FILE_NAME_HERE
[ 91%] Building CXX object test/CMakeFiles/TEST_EXECUTABLE_FILE_NAME_HERE.dir/src/test.cpp.o
[100%] Linking CXX executable TEST_EXECUTABLE_FILE_NAME_HERE
[100%] Built target TEST_EXECUTABLE_FILE_NAME_HERE
```