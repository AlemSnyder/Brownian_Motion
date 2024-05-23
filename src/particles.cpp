#include "particles.hpp"
#include <random>

Particles::Particles(float box_size, size_t num_particles)
    : box_size_(box_size), mass(num_particles, 1), radius(num_particles, 0.5){
    auto rand_engine = std::default_random_engine();

    auto uniform = std::uniform_real_distribution(-box_size, box_size);
    auto normal = std::normal_distribution(); // mean 0 std 1 I assume

    current_positions.reserve(num_particles);
    current_velocities.reserve(num_particles);
    next_positions.reserve(num_particles);
    next_velocities.reserve(num_particles);

    for (size_t i = 0; i < num_particles; i++){
        float x = uniform(rand_engine);
        float y = uniform(rand_engine);

        current_positions.push_back(vec2({x, y}));

        float xv = normal(rand_engine);
        float yv = normal(rand_engine);

        current_velocities.push_back(vec2({xv, yv}));
    }
}

void Particles::step(){
    size_t num_particles = current_positions.size();

    //#pragma parallel for
    for (size_t i = 0; i < num_particles; i++){
        next_positions[i] = current_positions[i] + current_velocities[i];
    }

    for (size_t i = 0; i < num_particles - 1; i++){
        for (size_t j = i+1; j < num_particles; j++){
            if (norm_squared( current_positions[i] - current_positions[j]) < radius[i] + radius[j]){

                // I read this on the internet somewhere
                next_velocities[i] = current_velocities[j];
                next_velocities[j] = current_velocities[i];
            }
        }
    }
}

float Particles::temperature() const {
    size_t num_particles = current_positions.size();

    float total_energy = 0;
    // the temperature is the average kinetic energy
    // E = 1/2 m v^2
    for (std::size_t i = 0; i < num_particles; i++){
        total_energy += current_velocities[i] * current_velocities[i];
    }

    return total_energy / num_particles;
}
