#include "particles.hpp"
#include <random>
#include <iostream>

using linalg::vec2;

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

    #pragma omp parallel
    for (size_t i = 0; i < num_particles; i++){
        next_positions[i] = current_positions[i] + current_velocities[i];
        next_velocities[i] = current_velocities[i];
    }

    for (size_t i = 0; i < num_particles - 1; i++){
        for (size_t j = i+1; j < num_particles; j++){
            if (norm_squared( current_positions[i] - current_positions[j]) < radius[i] + radius[j]){

                std::cout << "Collision\n";


                auto [v1f, v2f] = collision(i, j);
                next_velocities[i] = v1f;
                next_velocities[j] = v2f;
            }
        }
    }

    for (size_t i = 0; i < num_particles; i++){
        current_velocities[i] = next_velocities[i];

        if (next_positions[i][0] < -box_size_){
            auto v = current_velocities[i];
            current_velocities[i] = vec2({std::abs(v[0]), v[1]});
        } else if (next_positions[i][0] > box_size_){
            auto v = current_velocities[i];
            current_velocities[i] = vec2({-std::abs(v[0]), v[1]});
        }

        if (next_positions[i][1] < -box_size_){
            auto v = current_velocities[i];
            current_velocities[i] = vec2({v[0], std::abs(v[1])});
        } else if (next_positions[i][1] > box_size_){
            auto v = current_velocities[i];
            current_velocities[i] = vec2({v[0], -std::abs(v[1])});
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

std::pair<vec2, vec2> Particles::collision(std::size_t i, std::size_t j) const {
    vec2 v1 = current_velocities[i];
    vec2 v2 = current_velocities[j];
    float m1 = mass[i];
    float m2 = mass[j];

    vec2 dp = linalg::normalize(current_positions[i] - current_positions[j]);
    vec2 dpp = linalg::perpendicular(dp);

    auto [v1s1, v1s2] = linalg::decomp(v1, dp, dpp);
    auto [v2s1, v2s2] = linalg::decomp(v2, dp, dpp);

    float mass_ratio1 = (m1 - m2) / (m1 + m2);
    float mass_ratio2 = (2 * m1) / (m1 + m2);
    float mass_ratio3 = (2 * m2) / (m1 + m2);


    vec2 v1f = v1s2 + v1s1 * mass_ratio1 + v2s1 * mass_ratio3;
    vec2 v2f = v2s2 + v1s1 * mass_ratio2 - v2s1 * mass_ratio1;

    return {v1f, v2f};
}
