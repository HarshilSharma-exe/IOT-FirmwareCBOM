// FirmwareCBOM
// An Object-Oriented Framework for Cryptographic Inventory and
// Risk Assessment of IoT Firmware (source-level MVP)
//
// Pipeline:
//   Firmware directory -> CryptoScanner -> CryptoComponent objects
//                       -> RiskAnalyzer (uses CryptoDatabase)
//                       -> CBOMGenerator -> cbom.json + report.txt

#include <iostream>
#include <string>
#include <vector>

#include "models/CryptoComponent.h"
#include "database/CryptoDatabase.h"
#include "scanner/CryptoScanner.h"
#include "analyzer/RiskAnalyzer.h"
#include "generator/CBOMGenerator.h"

int main(int argc, char* argv[]) {
    std::string firmwareDir = "firmware_samples";
    std::string firmwareName = "SampleFirmware_v1";
    std::string outputDir = "output";

    if (argc > 1) firmwareDir = argv[1];
    if (argc > 2) firmwareName = argv[2];
    if (argc > 3) outputDir = argv[3];

    std::cout << "FirmwareCBOM: scanning \"" << firmwareDir << "\"...\n" << std::endl;

    CryptoDatabase database;
    CryptoScanner scanner(database);
    RiskAnalyzer analyzer(database);
    CBOMGenerator generator;

    std::vector<CryptoComponent> components = scanner.scanDirectory(firmwareDir);

    if (components.empty()) {
        std::cout << "No cryptographic components were detected in \""
                  << firmwareDir << "\"." << std::endl;
        return 0;
    }

    analyzer.analyze(components);

    std::cout << "Detected " << components.size() << " cryptographic component(s):\n";
    for (const auto& c : components) {
        c.display();
    }

    int fchi = analyzer.calculateFCHI(components);
    std::cout << "\nFirmware Cryptographic Health Index (FCHI): " << fchi << "/100" << std::endl;

    generator.generateJSON(firmwareName, components, fchi, outputDir + "/cbom.json");
    generator.generateTextReport(firmwareName, components, fchi, outputDir + "/report.txt");

    return 0;
}
