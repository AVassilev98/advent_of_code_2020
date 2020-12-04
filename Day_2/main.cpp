#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct passwordCode {
    int minOcc;
    int maxOcc;
    char c;
    std::string password;
    void init_code(const std::string &s) {

        int index = 0;
        std::string::size_type sz;
        minOcc = std::stoi(s, &sz);
        index = sz + 1;
        maxOcc = std::stoi(s.substr(index), &sz);
        index += sz + 1;
        c = s[index];
        password = s.substr(index + 3);
    }

    void dump() {
        std::cout << minOcc << "-" << maxOcc << " " << c << ": ";
        std::cout << password << std::endl;
    }
};

int q1(std::vector<passwordCode> &passwords);
int q2(std::vector<passwordCode> &passwords);

int main(int argc, char *argv[]) {

    std::ifstream input("input.txt");

    if (!input.is_open()) return 1;

    std::vector<passwordCode> passwords;
    std::string line;
    while (std::getline(input, line)) {
        passwords.emplace_back();
        passwords[passwords.size() - 1].init_code(line);
        // passwords[passwords.size() - 1].dump();
    }

    std::cout << q1(passwords) << std::endl;
    std::cout << q2(passwords) << std::endl;

    return 0;
}

int q2(std::vector<passwordCode> &passwords) {
    unsigned validPasswords = 0;
    for (passwordCode &pc : passwords) {
        validPasswords +=
            (pc.password[pc.minOcc - 1] == pc.c) ^ (pc.password[pc.maxOcc - 1] == pc.c);
    }
    return validPasswords;
}

int q1(std::vector<passwordCode> &passwords) {
    unsigned validPasswords = 0;
    for (passwordCode &pc : passwords) {
        unsigned charCount = 0;
        for (char c : pc.password) {
            charCount += c == pc.c;
        }
        if (pc.minOcc <= charCount && charCount <= pc.maxOcc) validPasswords++;
    }
    return validPasswords;
}