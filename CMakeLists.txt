cmake_minimum_required(VERSION 3.10)
project(ATMSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/UI.cpp
    src/SystemInitializer.cpp
    src/ATM.cpp
    src/Bank.cpp
    src/Account.cpp
    src/Session.cpp
    src/Transaction.cpp
    src/SystemSnapshot.cpp
)

# Create executable
add_executable(atm_system ${SOURCES})