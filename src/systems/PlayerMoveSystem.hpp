#pragma once 

#include "ISystem.hpp"

class PlayerMoveSystem : public ISystem {
  public:   
    
    void awake() override;
    void start() override;
    void update(double dt) override;
    void fixed_update(double tmod) override;
    void render() override;
    void dispose() override;
};
