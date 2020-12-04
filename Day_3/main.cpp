#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

enum class Token { Tree, Flat };

using Hill = std::vector<std::vector<Token>>;

int q1(const Hill &H, int x_inc, int y_inc);
unsigned q2(const Hill &H);

int main(int argc, char *argv[]) {

    std::ifstream input("input.txt");

    if (!input.is_open()) return 1;

    Hill H;
    std::string line;
    while (std::getline(input, line)) {
        std::vector<Token> row;
        for (char c : line) {
            switch (c) {
            case '#':
                row.push_back(Token::Tree);
                break;
            case '.':
                row.push_back(Token::Flat);
                break;
            default:
                std::cout << "Unknown symbol" << std::endl;
            }
        }
        H.emplace_back(std::move(row));
    }

    std::cout << q1(H, 3, 1) << std::endl;
    std::cout << q2(H) << std::endl;

    return 0;
}

int q1(const Hill &H, int x_inc, int y_inc) {
    int treeCount = 0;
    int pos_X = 0;

    for (int pos_Y = 0; pos_Y < H.size(); pos_Y += y_inc) {
        if (H[pos_Y][pos_X] == Token::Tree) treeCount++;
        pos_X = (pos_X + x_inc) % H[pos_Y].size();
    }

    return treeCount;
}
unsigned q2(const Hill &H) {
    std::array<int, 5> x_incs = {1, 3, 5, 7, 1};
    std::array<int, 5> y_incs = {1, 1, 1, 1, 2};

    unsigned result = 1;
    for (int i = 0; i < x_incs.size(); i++) {
        result *= q1(H, x_incs[i], y_incs[i]);
    }

    return result;
}
