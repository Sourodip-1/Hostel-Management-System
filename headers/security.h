#ifndef SECURITY_H
#define SECURITY_H

// Hashes a plain text password into a hex string.
// outputBuffer must be at least 65 characters long (64 hex + null terminator).
void hashPassword(const char *plain, char *outputBuffer);

#endif
