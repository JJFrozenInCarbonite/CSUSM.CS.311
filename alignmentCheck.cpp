#include <iostream>

int main() {
    std::cout << "Alignment of int: " << __alignof__(int) << std::endl;
    std::cout << "Alignment of double: " << __alignof__(double) << std::endl;
    std::cout << "Alignment of pointer: " << __alignof__(void*) << std::endl;
    return 0;
}