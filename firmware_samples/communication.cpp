// Simulated firmware module: sensor-to-cloud communication
#include <iostream>

void sendTelemetry(unsigned char* data, unsigned char* key) {
    AES256_encrypt(data, key);
}

void establishSecureChannel(unsigned char* peerKey) {
    ECDSA_verify(peerKey);
}

void legacyChecksum(unsigned char* payload) {
    // Old integrity check, kept only for legacy firmware compatibility
    SHA1(payload);
}
