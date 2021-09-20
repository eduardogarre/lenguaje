#include <iostream>

extern "C" {
    int inicia();
    
    void escribe(int numero)
    {
        std::cout << numero << std::endl;
    }
}

int main() {
    return inicia();
}