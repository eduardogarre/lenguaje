#include <iostream>

extern "C" {
    int dobleTriple(int);
}

int main() {
    int númeroDoble = 20;
    std::cout << "El doble de " << númeroDoble << " es: " << dobleTriple(númeroDoble) << std::endl;
    int númeroTriple = 3;
    std::cout << "El triple de " << númeroTriple << " es: " << dobleTriple(númeroTriple) << std::endl;
}