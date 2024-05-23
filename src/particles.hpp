#pragma once

#include <vector>
#include "linalg.hpp"

class Particles
{
private:

    float box_size_;

    std::vector<vec2> current_positions;
    std::vector<vec2> next_positions;
    std::vector<vec2> current_velocities;
    std::vector<vec2> next_velocities;

    std::vector<float> mass;
    std::vector<float> radius;

public:
    Particles(float box_size, std::size_t num_particles);
    
    void step();
    float temperature() const;
};


