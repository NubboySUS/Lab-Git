#include <iostream>
#include <fstream>
#include <sstream>

// removed debug mode

// TESTING
bool CheckValidInput() {
    if (std::cin.fail()) {
        std::cout << "Incorrect Input\n";
        return false;
    }
    return true;
}
bool CheckIfParamsAreValid(int a, int b, unsigned int h, unsigned int n) {
    if (h <= 0) {
        std::cout << "Step (h) is too small\n";
        return false;
    }
    if (a > b) {
        std::cout << "Start (a) is greater than End (b)\n";
        return false;
    }
    return true;
}

float Calculate(float x, unsigned int n) {
    float y = 0.0f;
    // SUM
    if (x <= 0.0f)
        for (unsigned int i = 2; i <= n - 1; i++)
            y += x / i;
    // PRODUCT OF SUMS
    else {
        y = 1.0f;
        for (unsigned int i = 0; i <= n - 1; i++) {
            float sum = 0.0f;
            for (unsigned int j = 0; j <= i; j++)
                sum += static_cast<float>(i) / (j + x);
            y *= sum;
        }
    }
    return y;
}

int main() {
    // GATHER INPUT
    std::cout << "Enter Start (a), End (b), Step (h), n: ";
    int a, b;
    unsigned int h, n;
    std::cin >> a >> b >> h >> n;
    if (!CheckValidInput() || !CheckIfParamsAreValid(a, b, h, n))
        return 0;
    // moved file saving to the start
    std::string filename;
    std::cout << "Enter filename (e.g., results.txt): ";
    std::cin >> filename;
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Error: Could not open the file for writing.\n";
        return 0;
    }
    outFile << "\n---------------------------------------------\n";
    outFile << " h  |         x          |         y\n";
    outFile << "---------------------------------------------\n";
    // MAIN LOOP
    for (float x = static_cast<float>(a); x <= b; x += h)
        outFile << " " << (h < 10 ? "0" : "") << h << " |         " << (x < 0 ? "-" : " ") << (std::abs(x) < 10 ? "0" : "") << std::abs(x) << "        |      " << Calculate(x, n) << "\n";
    outFile << "--------------------------------------------\n";
    // SAVE TO FILE
    outFile.close();
    std::cout << "Results successfully saved to " << filename << "\n";
    return 0;
}