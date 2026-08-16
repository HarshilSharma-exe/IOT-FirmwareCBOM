#ifndef CRYPTOCOMPONENT_H
#define CRYPTOCOMPONENT_H

#include <string>

// Represents a single cryptographic algorithm/component detected
// inside a piece of firmware (or firmware source code).
class CryptoComponent {
private:
    std::string algorithm;   // e.g. "AES-256", "MD5"
    std::string type;        // e.g. "encryption", "hash", "public-key"
    std::string sourceFile;  // where it was detected
    std::string risk;        // LOW / MEDIUM / HIGH / CRITICAL (set later by RiskAnalyzer)

public:
    CryptoComponent(std::string algorithm,
                     std::string type,
                     std::string sourceFile);

    // Getters
    std::string getAlgorithm() const;
    std::string getType() const;
    std::string getSourceFile() const;
    std::string getRisk() const;

    // Setter (RiskAnalyzer assigns this after the component is created)
    void setRisk(const std::string& riskLevel);

    void display() const;
};

#endif // CRYPTOCOMPONENT_H
