#ifndef CBOMGENERATOR_H
#define CBOMGENERATOR_H

#include <string>
#include <vector>
#include "../models/CryptoComponent.h"

// Produces the final Cryptographic Bill of Materials as JSON,
// plus a human-readable plain-text security report.
class CBOMGenerator {
public:
    void generateJSON(const std::string& firmwareName,
                       const std::vector<CryptoComponent>& components,
                       int fchi,
                       const std::string& outputPath) const;

    void generateTextReport(const std::string& firmwareName,
                             const std::vector<CryptoComponent>& components,
                             int fchi,
                             const std::string& outputPath) const;
};

#endif // CBOMGENERATOR_H
