#include <iostream>

extern "C" {
    int dobleTriple(int);
}

int main() {
    int número = 20;
    std::cout << "El doble o triple de " << número << " es: " << dobleTriple(número) << std::endl;
}