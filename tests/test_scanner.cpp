// Minimal self-contained test for CryptoScanner + RiskAnalyzer.
// No external test framework required: build fails (non-zero exit) on failure.

#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdio>

#include "../src/models/CryptoComponent.h"
#include "../src/database/CryptoDatabase.h"
#include "../src/scanner/CryptoScanner.h"
#include "../src/analyzer/RiskAnalyzer.h"

int main() {
    // Create a temporary firmware file with known crypto keywords.
    const std::string tmpFile = "test_sample.cpp";
    {
        std::ofstream out(tmpFile);
        out << "AES256_encrypt(data, key);\n";
        out << "SHA256(data);\n";
        out << "MD5(password);\n";
    }

    CryptoDatabase db;
    CryptoScanner scanner(db);
    RiskAnalyzer analyzer(db);

    std::vector<CryptoComponent> components = scanner.scanFile(tmpFile);
    assert(components.size() == 3 && "expected 3 crypto components to be detected");

    analyzer.analyze(components);

    bool foundCritical = false;
    for (const auto& c : components) {
        if (c.getAlgorithm() == "MD5") {
            assert(c.getRisk() == "CRITICAL" && "MD5 must be flagged CRITICAL");
            foundCritical = true;
        }
    }
    assert(foundCritical && "MD5 component was not found");

    int fchi = analyzer.calculateFCHI(components);
    assert(fchi >= 0 && fchi <= 100 && "FCHI must be within 0-100");

    std::remove(tmpFile.c_str());

    std::cout << "All tests passed." << std::endl;
    return 0;
}
