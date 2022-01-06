#pragma once
#include "WickedEngine.h"


class TestsRenderer : public RenderPath3D
{
	wiECS::Entity ik_entity = wiECS::INVALID_ENTITY;
public:
	void Load() override;
	void Update(float dt) override;
};

class WickedSpaceFlight : public MainComponent
{
	TestsRenderer renderer;
public:
	void Initialize() override;
};

