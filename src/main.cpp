#include <iostream>

#include "particles.hpp"

int main(int argc, char** arcv) {

    Particles particles(10.0, 4);

    float temperature = particles.temperature();
    std::cout << "Temperature: " << temperature << "\n";

    for (std::size_t n = 0; n < 2000; n++){

        particles.step();
        float temperature = particles.temperature();
        //std::cout << "Temperature: " << temperature << "\n";
    }
    
    std::cout << std::endl;

}