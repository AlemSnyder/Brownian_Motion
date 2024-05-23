#include <iostream>

#include "particles.hpp"

int main(int argc, char** arcv) {

    Particles particles(10.0, 4);

    particles.step();

    float temperature = particles.temperature();

    std::cout << "Temperature: " << temperature << "\n";
    
    std::cout << std::endl;

}