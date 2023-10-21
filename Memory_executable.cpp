#include <iostream>
#include <fstream>
#include <vector>

// Function to encrypt the code with a key
void encryptCode(std::vector<char>& code, const std::string& key) {
    for (size_t i = 0; i < code.size(); ++i) {
        code[i] ^= key[i % key.size()];
    }
}

// Function to decrypt the code with the same key
void decryptCode(std::vector<char>& code, const std::string& key) {
    encryptCode(code, key); // XOR-based encryption is symmetric
}

int main() {
    // Load code from a file
    std::ifstream file("my_code.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open code file." << std::endl;
        return 1;
    }

    // Determine the size of the code
    file.seekg(0, std::ios::end);
    size_t codeSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate memory for the code
    std::vector<char> code(codeSize);
    file.read(code.data(), codeSize);

    // Encryption and decryption using a key
    const std::string encryptionKey = "7a1e0ac75d7e087366ce1d8628651ca0f8e82a0c0fdea5c6c9b6a61989b35d64";
    encryptCode(code, encryptionKey); // Encrypt the code

    // Execute the loaded and decrypted code
    int result = 0;
    __asm {
        call code.data()
        mov result, eax
    }

    // Decryption for cleanup
    decryptCode(code, encryptionKey);

    // Display the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}
