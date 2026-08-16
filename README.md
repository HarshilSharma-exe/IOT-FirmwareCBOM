# FirmwareCBOM

**An Object-Oriented Framework for Cryptographic Inventory and Risk Assessment of IoT Firmware**

FirmwareCBOM scans firmware source code, identifies the cryptographic algorithms it uses,
evaluates their security risk, and generates a **Cryptographic Bill of Materials (CBOM)** —
the cryptographic equivalent of a Software Bill of Materials (SBOM).

> A normal SBOM answers *"what software components are present?"*
> A CBOM answers *"what cryptographic components are present?"*
> **FirmwareCBOM** asks *"what cryptographic components are present in IoT firmware, and what is their security status?"*

## Problem

IoT devices often embed cryptographic primitives (AES, RSA, ECDSA, SHA-256, and — worryingly —
still MD5, SHA-1, or DES) without any clear, auditable inventory of what's actually in use, how
strong it is, or whether it's deprecated. FirmwareCBOM makes that inventory automatic.

## Features

- **Firmware scanning** — recursively scans firmware source files for cryptographic keywords
- **Cryptographic component detection** — builds a typed object model of every algorithm found
- **Risk assessment** — every component gets a LOW / MEDIUM / HIGH / CRITICAL rating
- **Firmware Cryptographic Health Index (FCHI)** — a single 0–100 score summarizing overall firmware crypto health
- **CBOM generation** — machine-readable JSON output plus a human-readable text report
- **Extensible database** — algorithm risk data is centralized, not hardcoded into scanning logic

## Architecture

```
firmware_samples/ (input)
        │
        ▼
 ┌───────────────┐
 │ CryptoScanner │  finds algorithm keywords in source files
 └───────┬───────┘
         │  vector<CryptoComponent>
         ▼
 ┌────────────────┐      ┌──────────────────┐
 │  RiskAnalyzer   │◄────►│  CryptoDatabase   │  known algorithms,
 └───────┬────────┘      │  (risk, deprecated)│  risk scores, recs
         │                └──────────────────┘
         ▼
 ┌─────────────────┐
 │  CBOMGenerator   │  → output/cbom.json
 └─────────────────┘  → output/report.txt
```

**Design separation:** the *scanner* answers "what did I find?"; the *database* answers
"what does it mean?"; the *analyzer* combines the two into a risk verdict. This keeps risk
data out of the scanning logic, so adding a new algorithm never requires touching the parser.

### Class overview

| Class | Responsibility |
|---|---|
| `CryptoComponent` | Represents one detected cryptographic algorithm instance (encapsulated data + `display()`) |
| `CryptoScanner` | Reads firmware source files and detects known crypto keywords |
| `CryptoDatabase` | Reference data: risk score, deprecation status, recommendation per algorithm |
| `RiskAnalyzer` | Assigns risk levels to components and computes the overall FCHI score |
| `CBOMGenerator` | Serializes results to `cbom.json` and a plain-text security report |

## Technologies

- C++17
- CMake (≥ 3.10)
- Standard Library only — no external dependencies

## How to build and run

```bash
git clone <your-repo-url>
cd FirmwareCBOM
mkdir build && cd build
cmake ..
make

# Run against the bundled sample firmware
./firmwarecbom firmware_samples IoT-Sensor-v1 output
```

This produces `output/cbom.json` and `output/report.txt`.

You can point it at any directory of source files:

```bash
./firmwarecbom /path/to/other/firmware MyFirmwareName output
```

### Running tests

```bash
cd build
ctest --output-on-failure
# or directly:
./tests/test_scanner
```

## Example output

Scanning the bundled `firmware_samples/` (four simulated firmware modules) produces:

```
Algorithm        Type            Risk        Source
--------------------------------------------------------------
AES-128          encryption      MEDIUM      firmware_samples/storage.cpp
SHA-256          hash            LOW         firmware_samples/storage.cpp
DES              encryption      CRITICAL    firmware_samples/storage.cpp
AES-256          encryption      LOW         firmware_samples/sensor.cpp
RSA-2048         public-key      MEDIUM      firmware_samples/sensor.cpp
SHA-256          hash            LOW         firmware_samples/sensor.cpp
RSA-2048         public-key      MEDIUM      firmware_samples/authentication.cpp
SHA-256          hash            LOW         firmware_samples/authentication.cpp
MD5              hash            CRITICAL    firmware_samples/authentication.cpp
AES-256          encryption      LOW         firmware_samples/communication.cpp
ECDSA            public-key      MEDIUM      firmware_samples/communication.cpp
SHA-1            hash            HIGH        firmware_samples/communication.cpp

Firmware Cryptographic Health Index (FCHI): 68/100
Overall Status: MODERATE RISK
```

## Scope and limitations (important)

This is a **source-level** cryptographic scanner: it analyzes firmware represented as source
code or simulated firmware, not compiled binaries (`.bin` / `.hex` / `.elf`). This is a
deliberate staged design choice, not an oversight — reverse-engineering compiled firmware
binaries is a substantially harder problem better tackled as a follow-on extension once the
core object model and pipeline are proven.

**Current version:** source-level / simulated firmware cryptographic analysis.
**Future work:** binary firmware analysis (ELF/`.bin` parsing, disassembly, symbol/string
extraction), post-quantum-readiness scoring, and pluggable risk strategies (see below).

## Roadmap / future work

- [ ] `CryptoAlgorithm` abstract base class with `AES`, `RSA`, `ECC`, `SHA` subclasses (polymorphism)
- [ ] `RiskStrategy` interface (Strategy pattern) with `BasicRiskStrategy`, `QuantumRiskStrategy`, `IoTRiskStrategy`
- [ ] Post-quantum readiness assessment and ML-KEM / ML-DSA migration recommendations
- [ ] `ELFScanner` / `BinaryScanner` for compiled firmware analysis
- [ ] Experimental evaluation across a corpus of 20–50 simulated firmware projects (detection accuracy, false positive/negative rate, FCHI validation)

## License

MIT — see [LICENSE](LICENSE).
