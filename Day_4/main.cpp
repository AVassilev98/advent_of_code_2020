#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

enum class HeightType { In, Cm, Invalid };

struct Passport {
    uint8_t codes;

    int byr;
    int iyr;
    int eyr;
    int hgt;
    HeightType hgt_type;
    std::string hcl;
    std::string ecl;
    std::string pid;

    Passport() : codes(0) {}
};

int q1(const std::vector<Passport> &passports);
int q2(const std::vector<Passport> &passports);

int main(int argc, char *argv[]) {

    auto start = std::chrono::steady_clock::now();

    std::ifstream input("input.txt");
    std::vector<Passport> passports(1);

    if (!input.is_open()) return 1;
    std::string line;
    while (std::getline(input, line)) {
        if (line.size() == 0) {
            passports.emplace_back();
        } else {
            int idx = -1;
            while ((idx = line.find(':', idx + 1)) != std::string::npos) {
                std::string code = line.substr(idx - 3, 3);
                int endIdx = line.find_first_of(" \t\n", idx + 1);
                std::string value = line.substr(idx + 1, endIdx - (idx + 1));
                if (code == "byr") passports.back().codes |= 1 << 0;
                else if (code == "iyr")
                    passports.back().codes |= 1 << 1;
                else if (code == "eyr")
                    passports.back().codes |= 1 << 2;
                else if (code == "hgt")
                    passports.back().codes |= 1 << 3;
                else if (code == "hcl")
                    passports.back().codes |= 1 << 4;
                else if (code == "ecl")
                    passports.back().codes |= 1 << 5;
                else if (code == "pid")
                    passports.back().codes |= 1 << 6;
                else if (code == "cid")
                    passports.back().codes |= 1 << 7;

                if (code == "byr") passports.back().byr = stoi(value);
                else if (code == "iyr")
                    passports.back().iyr = stoi(value);
                else if (code == "eyr")
                    passports.back().eyr = stoi(value);
                else if (code == "hgt") {
                    size_t idx;
                    passports.back().hgt = stoi(value, &idx);
                    std::string hgt_code = value.substr(idx, 2);
                    if (hgt_code == "in") passports.back().hgt_type = HeightType::In;
                    else if (hgt_code == "cm")
                        passports.back().hgt_type = HeightType::Cm;
                    else
                        passports.back().hgt_type = HeightType::Invalid;
                } else if (code == "hcl")
                    passports.back().hcl = value;
                else if (code == "ecl")
                    passports.back().ecl = value;
                else if (code == "pid")
                    passports.back().pid = value;
            }
        }
    }

    std::cout << q1(passports) << std::endl;
    std::cout << q2(passports) << std::endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}

int q1(const std::vector<Passport> &passports) {
    int validPassports = 0;
    for (const Passport &pp : passports) {
        if (pp.codes == 0xFF || pp.codes == 0x7F) validPassports++;
    }
    return validPassports;
}
int q2(const std::vector<Passport> &passports) {
    int oldValidPp = -1;
    int validPassports = 0;
    for (const Passport &pp : passports) {
        if (pp.codes != 0xFF && pp.codes != 0x7F) continue;
        oldValidPp = validPassports;
        if (pp.byr < 1920 || pp.byr > 2002) continue;
        if (pp.iyr < 2010 || pp.iyr > 2020) continue;
        if (pp.eyr < 2020 || pp.eyr > 2030) continue;
        if (pp.hgt_type == HeightType::Invalid) continue;
        if (pp.hgt_type == HeightType::In && (pp.hgt < 59 || pp.hgt > 76)) continue;
        if (pp.hgt_type == HeightType::Cm && (pp.hgt < 150 || pp.hgt > 193)) continue;
        if (pp.hcl[0] != '#' || pp.hcl.length() != 7) continue;
        for (int i = 1; i < pp.hcl.length(); i++) {
            unsigned char c = pp.hcl[i];
            if (c < 48 || (c > 57 && c < 97) || c > 102) continue;
        }
        const std::string &ecl = pp.ecl;
        if (ecl.length() != 3) continue;
        if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && ecl != "grn" &&
            ecl != "hzl" && ecl != "oth")
            continue;
        if (pp.pid.length() != 9) continue;
        for (char c : pp.pid) {
            if (c - '0' < 0 || c - '0' > 9) continue;
        }
        validPassports++;
    }
    return validPassports;
}
