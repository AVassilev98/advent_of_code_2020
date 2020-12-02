#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int q1(std::vector<int> &nums);
int q2(std::vector<int> &nums);

const unsigned currentYear = 2020;

int main(int argc, char *argv[]) {

    std::ifstream input("input.txt");

    if (!input.is_open()) return 1;

    std::vector<int> nums;
    std::string line;
    while (std::getline(input, line)) {
        nums.push_back(std::stoi(line));
    }
    std::sort(nums.begin(), nums.end());

    std::cout << q1(nums) << std::endl;
    std::cout << q2(nums) << std::endl;

    return 0;
}

int q2(std::vector<int> &nums) {

    for (int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        int target = currentYear - num;
        int frontIdx = i + 1;
        int backIdx = nums.size() - 1;

        while (frontIdx < backIdx) {
            if (nums[frontIdx] + nums[backIdx] == target)
                return nums[frontIdx] * nums[backIdx] * num;
            else if (nums[frontIdx] + nums[backIdx] < target)
                frontIdx++;
            else if (nums[frontIdx] + nums[backIdx] > target)
                backIdx--;
        }
    }
    return -1;
}

int q1(std::vector<int> &nums) {

    int frontIdx = 0;
    int backIdx = nums.size() - 1;

    while (frontIdx < backIdx) {
        if (nums[frontIdx] + nums[backIdx] == currentYear) return nums[frontIdx] * nums[backIdx];
        else if (nums[frontIdx] + nums[backIdx] < currentYear)
            frontIdx++;
        else if (nums[frontIdx] + nums[backIdx] > currentYear)
            backIdx--;
    }

    return -1;
}