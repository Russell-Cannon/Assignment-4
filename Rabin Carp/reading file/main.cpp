#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("IX.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }

    file.close();

    std::cout << "File content:\n" << content;

    return 0;
}
