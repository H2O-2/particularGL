#pragma once

#include "particle.hpp"
#include "../geometries/sphere.hpp"
#include "../geometries/square.hpp"
#include "../geometries/triangle.hpp"

class Emitter {
public:
    typedef std::vector<std::unique_ptr<Particle>> Particles;

    // Shape of particle emitter
    enum class EmitterType {
        POINT,
        BOX,
        SPHERE,
    };

    enum class EmitterDirection {
        UNIFORM, // random direction, this is the default setting
        DIRECTIONAL, // a certain direction, defaults to the direction of y axis
    };

    enum class ParticleType {
        // GLOW_SPHERE
        SPHERE,
        SQUARE,
        // TEXTURE
        TRIANGLE,
    };

    enum class ParticleBlend {
        NORMAL,
        ADD,
        SCREEN,
        LIGHTEN
    };

    Emitter(ParticleType particleType = ParticleType::SPHERE, uint32_t particlesPerSec = 100);
    ~Emitter();

    uint32_t getParticlesPerSec();
    void setParticlesPerSec(uint32_t particlesPerSec);
    ParticleBlend getBlendType();
    void setBlendType(ParticleBlend blendType);
    void setType(EmitterType emitterType);
    void setEmitDirection(EmitterDirection direction);
    void setDirectionSpread(float directionSpread);
    glm::vec3 getPosn();
    void setPosn(glm::vec3 posn);
    glm::vec3 getRotation();
    void setRotation(glm::vec3 rotation);
    glm::vec3 getSize();
    void setSize(glm::vec3 size);
    void setInitialVelocity(float initVelocity);
    void setInitialVelocityRandomness(float initVelocityRandom);
    void setLifeRandomness(int lifeRandom);
    void setSizeRandomness(int sizeRandom);
    void setRotationRandomness(int rotationRandom);
    void setOpacityRandomness(int opacityRandom);

    glm::vec3* getOffsets();
    glm::mat4* getModelMatrices();
    int getIndexNum();
    uint32_t getVAO();
    void draw();
private:
    Particles particles; // All particles generated by this emitter

    uint32_t particlesPerSec; // Number of particles generated per second

    /***** DEBUG *****/
    std::vector<glm::vec3> offsets;
    /***** DEBUG *****/

    ParticleType particleType; // Shape of particles
    ParticleBlend blendType; // Type of blend applied to particles
    EmitterType emitterType; // Emitter type
    std::unique_ptr<Geometry> curGeomtry; // Current geometry shape of the particles

    EmitterDirection direction; // Emitter direction
    float directionSpread; // Spread of the particle beam in percentage(%), this is disabled for uniform emitter direction

    glm::vec3 position; // Position of emitter
    glm::vec3 rotation; // Rotation of emitter
    glm::vec3 size; // Size of emitter, this is disabled for point emitters

    float initVelocity; // Initial velocity of particles
    float initVelocityRandom; // Randomness of velocity in percentage(%), 0% means no change of velocity to all particles and 100% means a possible range of [0, 2*v0] of velocity where v0 is the velocity specified

    int lifeRandom; // Randomness of particle life span in percentage(%), 0% means the particles genearted at the same time will all die at once and 100% means a possible range of [0.9*l0, 1.1*l0] where l0 is the life span specified
    int sizeRandom; // Randomness of particle size in percentage(%), 100% means a possible range of [0.2*s0, 5*s0] where s0 is the specified size
    int rotationRandom; // Rotates the particle around a random axis, randomness in percentage(%) where 0% means 0 deg rotation for all particles and 100% means rotation in the range of [0, 360] deg
    int opacityRandom; // Randomness of particle opacity in percentage(%), 100% means a possible range of [0, p0] where p0 is the specified opacity
    // float randomRotationSpeed; // Rotates the particle around a random axis, randomness in percentage(%) where a 0% means no randomness in rotation speed and 100% means
    /** TODO: size over life **/
    /** TODO: color over life and random color **/

    /** TODO: Pre Run **/
};
