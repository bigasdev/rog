#pragma once 
#include "ISystem.hpp"

class SpriteSystem : public ISystem
{
  public:
    SpriteSystem() = default;
    ~SpriteSystem() = default;
    void awake() override;
    void start() override;
    void update(double dt) override;
    void fixed_update(double tmod) override;
    void render() override;
    void dispose() override;
};
