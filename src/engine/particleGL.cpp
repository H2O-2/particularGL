#include "particleGL.hpp"

ParticleGL::ParticleGL(unsigned int windowWidth, unsigned int windowHeight, float framerate, glm::vec3 bgColor) {
    // Initialize OpenGL context
    secondPerFrame = framerate / 60.0f;
    renderer = make_unique<Renderer>(windowWidth, windowHeight, secondPerFrame, bgColor);
    this->window = renderer->initWindow();

    // Add first emitter
    addEmitter();

    // Initialize timer
    renderer->initTimer();
}

ParticleGL::~ParticleGL() {
    renderer->clean();
}

void ParticleGL::addEmitter() {
    emitters.emplace_back(make_unique<Emitter>(secondPerFrame));

    int curEmitterIndex = emitters.size() - 1;
    // Buffer instanced array
    renderer->bufferParticles(emitters[curEmitterIndex]->getVAO(), emitters[curEmitterIndex]->getOffsets());
    // Update render data
    renderData[emitters[curEmitterIndex]->getVAO()] = emitters[curEmitterIndex]->getIndexNum();
}

void ParticleGL::render() {
    // Process events
    EventManager::pollEvent(window);

    // Render
    renderer->renderEngine(renderData, [&](const float& interpolation) {
        for (int i = 0; i < emitters.size(); ++i) {
            // Update emitter & particle data
            emitters[i]->update(interpolation);
        }
    });
}

bool ParticleGL::shouldEnd() {
    return EventManager::shouldQuit;
}
