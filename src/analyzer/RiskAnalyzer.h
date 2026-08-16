#ifndef RISKANALYZER_H
#define RISKANALYZER_H

#include <vector>
#include "../models/CryptoComponent.h"
#include "../database/CryptoDatabase.h"

// Converts a numeric risk score (from the CryptoDatabase) for each
// CryptoComponent into a human-readable risk level, and computes an
// overall Firmware Cryptographic Health Index (FCHI) for a firmware.
class RiskAnalyzer {
private:
    const CryptoDatabase& database;

    static std::string scoreToLevel(int score);

public:
    explicit RiskAnalyzer(const CryptoDatabase& db);

    // Assigns a risk level (LOW/MEDIUM/HIGH/CRITICAL) to every component, in place.
    void analyze(std::vector<CryptoComponent>& components) const;

    // Firmware Cryptographic Health Index: 0 (worst) - 100 (best).
    // Simple first version: 100 minus the average risk score scaled to 0-100.
    int calculateFCHI(const std::vector<CryptoComponent>& components) const;
};

#endif // RISKANALYZER_H
