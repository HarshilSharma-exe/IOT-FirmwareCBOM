#include "CBOMGenerator.h"
#include <fstream>
#include <iostream>

namespace {
    std::string riskStatus(int fchi) {
        if (fchi >= 80) return "LOW RISK";
        if (fchi >= 60) return "MODERATE RISK";
        if (fchi >= 40) return "HIGH RISK";
        return "CRITICAL RISK";
    }
}

void CBOMGenerator::generateJSON(const std::string& firmwareName,
                                  const std::vector<CryptoComponent>& components,
                                  int fchi,
                                  const std::string& outputPath) const {
    std::ofstream out(outputPath);
    if (!out.is_open()) {
        std::cerr << "Error: could not write to " << outputPath << std::endl;
        return;
    }

    out << "{\n";
    out << "  \"firmware\": \"" << firmwareName << "\",\n";
    out << "  \"fchi\": " << fchi << ",\n";
    out << "  \"status\": \"" << riskStatus(fchi) << "\",\n";
    out << "  \"cryptography\": [\n";

    for (size_t i = 0; i < components.size(); ++i) {
        const auto& c = components[i];
        out << "    {\n";
        out << "      \"algorithm\": \"" << c.getAlgorithm() << "\",\n";
        out << "      \"type\": \"" << c.getType() << "\",\n";
        out << "      \"source\": \"" << c.getSourceFile() << "\",\n";
        out << "      \"risk\": \"" << c.getRisk() << "\"\n";
        out << "    }" << (i + 1 < components.size() ? "," : "") << "\n";
    }

    out << "  ]\n";
    out << "}\n";
    out.close();

    std::cout << "CBOM written to " << outputPath << std::endl;
}

void CBOMGenerator::generateTextReport(const std::string& firmwareName,
                                        const std::vector<CryptoComponent>& components,
                                        int fchi,
                                        const std::string& outputPath) const {
    std::ofstream out(outputPath);
    if (!out.is_open()) {
        std::cerr << "Error: could not write to " << outputPath << std::endl;
        return;
    }

    out << "FirmwareCBOM Security Report\n";
    out << "============================\n";
    out << "Firmware: " << firmwareName << "\n";
    out << "Crypto components detected: " << components.size() << "\n\n";

    out << "Algorithm        Type            Risk        Source\n";
    out << "--------------------------------------------------------------\n";
    for (const auto& c : components) {
        out << c.getAlgorithm();
        for (size_t i = c.getAlgorithm().size(); i < 17; ++i) out << ' ';
        out << c.getType();
        for (size_t i = c.getType().size(); i < 16; ++i) out << ' ';
        out << c.getRisk();
        for (size_t i = c.getRisk().size(); i < 12; ++i) out << ' ';
        out << c.getSourceFile() << "\n";
    }

    out << "\nFirmware Cryptographic Health Index (FCHI): " << fchi << "/100\n";
    out << "Overall Status: " << riskStatus(fchi) << "\n";
    out.close();

    std::cout << "Report written to " << outputPath << std::endl;
}
