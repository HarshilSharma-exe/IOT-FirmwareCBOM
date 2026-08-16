#include "RiskAnalyzer.h"

RiskAnalyzer::RiskAnalyzer(const CryptoDatabase& db) : database(db) {}

std::string RiskAnalyzer::scoreToLevel(int score) {
    if (score <= 1) return "LOW";
    if (score <= 3) return "MEDIUM";
    if (score == 4) return "HIGH";
    return "CRITICAL"; // score >= 5
}

void RiskAnalyzer::analyze(std::vector<CryptoComponent>& components) const {
    for (auto& component : components) {
        int score = database.getRiskScore(component.getAlgorithm());
        component.setRisk(scoreToLevel(score));
    }
}

int RiskAnalyzer::calculateFCHI(const std::vector<CryptoComponent>& components) const {
    if (components.empty()) {
        return 100; // no crypto detected: nothing to be at risk (edge case, worth flagging in report)
    }

    double totalScore = 0.0;
    for (const auto& component : components) {
        totalScore += database.getRiskScore(component.getAlgorithm());
    }

    double averageScore = totalScore / static_cast<double>(components.size()); // 1 (best) - 5 (worst)
    double normalized = (averageScore - 1.0) / 4.0; // 0.0 (best) - 1.0 (worst)
    int fchi = static_cast<int>(100.0 - (normalized * 100.0));

    if (fchi < 0) fchi = 0;
    if (fchi > 100) fchi = 100;
    return fchi;
}
