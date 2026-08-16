// Simulated firmware module: on-device credential storage
#include <iostream>

void storeCredentials(unsigned char* data, unsigned char* key) {
    AES128_encrypt(data, key);
}

void verifyStoredIntegrity(unsigned char* data) {
    SHA256(data);
}

void archiveOldRecords(unsigned char* record) {
    // Deprecated: only used when migrating very old device backups
    DES_encrypt(record);
}
