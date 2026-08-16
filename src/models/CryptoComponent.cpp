#include "CryptoComponent.h"
#include <iostream>

CryptoComponent::CryptoComponent(std::string algorithm,
                                  std::string type,
                                  std::string sourceFile)
    : algorithm(std::move(algorithm)),
      type(std::move(type)),
      sourceFile(std::move(sourceFile)),
      risk("UNKNOWN") {}

std::string CryptoComponent::getAlgorithm() const { return algorithm; }
std::string CryptoComponent::getType() const { return type; }
std::string CryptoComponent::getSourceFile() const { return sourceFile; }
std::string CryptoComponent::getRisk() const { return risk; }

void CryptoComponent::setRisk(const std::string& riskLevel) {
    risk = riskLevel;
}

void CryptoComponent::display() const {
    std::cout << "Algorithm: " << algorithm
              << " | Type: " << type
              << " | Source: " << sourceFile
              << " | Risk: " << risk << std::endl;
}
