#pragma once
#include "WickedEngine.h"


class WickedSpaceFlightRenderer : public wi::RenderPath3D
{
    wi::ecs::Entity asteroid = wi::ecs::INVALID_ENTITY;
    wi::ecs::Entity player_spaceship = wi::ecs::INVALID_ENTITY;
	wi::gui::Label label;

public:
    void Load() override;
    void Start() override;
    void Update(float dt) override;
};

class WickedSpaceFlight : public wi::Application
{
    WickedSpaceFlightRenderer renderer;
public:
    void Initialize() override;
};

