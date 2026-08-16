#ifndef CRYPTODATABASE_H
#define CRYPTODATABASE_H

#include <string>
#include <unordered_map>

// Holds reference information about known cryptographic algorithms:
// their type, risk score, deprecation status and recommendation.
// The Scanner answers "what did I find?"; the Database answers "what does it mean?"
class CryptoDatabase {
private:
    struct AlgorithmInfo {
        std::string type;
        int riskScore;        // 1 (safest) - 5 (critical)
        bool deprecated;
        std::string recommendation;
    };

    std::unordered_map<std::string, AlgorithmInfo> database;

    void seedDatabase();

public:
    CryptoDatabase();

    bool isKnown(const std::string& algorithm) const;
    std::string getType(const std::string& algorithm) const;
    int getRiskScore(const std::string& algorithm) const;
    bool isDeprecated(const std::string& algorithm) const;
    std::string getRecommendation(const std::string& algorithm) const;
};

#endif // CRYPTODATABASE_H
