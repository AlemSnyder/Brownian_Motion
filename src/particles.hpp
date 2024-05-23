#pragma once

#include <vector>
#include <utility>
#include "linalg.hpp"

using linalg::vec2;

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

    std::pair<vec2, vec2> collision(std::size_t i, std::size_t j) const;
};


