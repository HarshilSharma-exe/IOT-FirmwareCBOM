add_executable(test_scanner
    test_scanner.cpp
    ${CMAKE_SOURCE_DIR}/src/models/CryptoComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/scanner/CryptoScanner.cpp
    ${CMAKE_SOURCE_DIR}/src/database/CryptoDatabase.cpp
    ${CMAKE_SOURCE_DIR}/src/analyzer/RiskAnalyzer.cpp
)
target_include_directories(test_scanner PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_test(NAME ScannerTests COMMAND test_scanner)
