#include <iostream>

extern "C" {
    int doble(int);
}

int main() {
    std::cout << "El doble de 2 es: " << doble(2) << std::endl;
}