#include <iostream>

int main() {
    std::cout << "\033[31m" << "This text is red." << "\033[0m" << std::endl;
    std::cout << "\033[32m" << "This text is green." << "\033[0m" << std::endl;
    std::cout << "\033[33m" << "This text is red." << "\033[0m" << std::endl;
    std::cout << "\033[34m" << "This text is red." << "\033[0m" << std::endl;
    std::cout << "\033[35m" << "This text is red." << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "This text is red." << std::endl;
    std::cout << "abcdefg";
    return 0;
}
