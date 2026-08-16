cmake_minimum_required(VERSION 3.10)
project(FirmwareCBOM CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(firmwarecbom
    src/main.cpp
    src/models/CryptoComponent.cpp
    src/scanner/CryptoScanner.cpp
    src/database/CryptoDatabase.cpp
    src/analyzer/RiskAnalyzer.cpp
    src/generator/CBOMGenerator.cpp
)

target_include_directories(firmwarecbom PRIVATE src)

# Copy sample firmware next to the built binary so `./firmwarecbom` works
# from the build directory out of the box.
add_custom_command(TARGET firmwarecbom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/firmware_samples
        $<TARGET_FILE_DIR:firmwarecbom>/firmware_samples
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:firmwarecbom>/output
)

enable_testing()
add_subdirectory(tests)
