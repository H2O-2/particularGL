#pragma once

#include "../particle/particle.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <memory>

class Emitter {
public:
    Emitter();
    ~Emitter();
private:
    enum class EmitterType {
        POINT,
        BOX,
        SPHERE,
    };
    enum class EmitterDirection {
        UNIFORM, // random direction, this is the default setting
        DIRECTIONAL, // a certain direction, defaults to the direction of y axis
    };

    std::vector<std::unique_ptr<Particle>> particles; // All particles generated by this emitter

    unsigned int particlesPerSec; // Number of particles generated per second

    EmitterType type; // Emitter type

    EmitterDirection direction; // Emitter direction
    float directionSpread; // Spread of the particle beam in percentage(%), this is disabled for uniform emitter direction

    glm::vec3 position; // Position of emitter
    glm::vec3 rotation; // Rotation of emitter
    glm::vec3 size; // Size of emitter, this is disabled for point emitters

    float velocity; // Initial velocity of particles
    float velocityRandom; // Randomness of velocity in percentage(%), 0% means no change of velocity to all particles and 100% means a possible range of [0, 2*v0] of velocity where v0 is the velocity specified

    /** TODO?: Pre Run **/
};