#include "stdafx.h"
#include "WickedSpaceFlight.h"

#include <string>
#include <sstream>
#include <fstream>
#include <thread>

void WickedSpaceFlight::Initialize()
{
    wi::renderer::SetShaderSourcePath(WickedEngine_SHADER_DIR);
    wi::Application::Initialize();

    infoDisplay.active = true;
    infoDisplay.watermark = true;
    infoDisplay.fpsinfo = true;
    infoDisplay.resolution = true;
    infoDisplay.heap_allocation_counter = true;


    renderer.init(canvas);
    renderer.Load();

    ActivatePath(&renderer);
}

void WickedSpaceFlightRenderer::Load()
{
    setSSREnabled(false);
    setReflectionsEnabled(true);
    setFXAAEnabled(false);

    label.Create("Label1");
    label.SetText("WickedSpaceFlight");
    label.font.params.h_align = wi::font::WIFALIGN_CENTER;
    label.SetSize(XMFLOAT2(240,20));
    GetGUI().AddWidget(&label);

    static wi::audio::Sound sound;
    static wi::audio::SoundInstance soundinstance;
}

void WickedSpaceFlightRenderer::Start()
{
    // Reset all state that tests might have modified:
    wi::eventhandler::SetVSync(true);
    wi::renderer::SetToDrawGridHelper(false);
    wi::renderer::SetTemporalAAEnabled(false);
    wi::scene::GetScene().weather = wi::scene::WeatherComponent();

    // Reset camera position:
    wi::scene::TransformComponent transform;
    transform.Translate(XMFLOAT3(0, 2.f, -4.5f));
    transform.UpdateTransform();
    wi::scene::GetCamera().TransformCamera(transform);

    float screenW = GetLogicalWidth();
    float screenH = GetLogicalHeight();

    wi::ecs::Entity asteroids = wi::scene::LoadModel("../Assets/AsteroidTestScene.wiscene");
    wi::ecs::Entity spaceship = wi::scene::LoadModel("../Assets/spaceship2.wiscene");
    //wi::scene::LoadModel("/usr/lib/WickedEngine/Content/models/teapot.wiscene");
    asteroid = wi::scene::GetScene().Entity_FindByName("Asteroid_no_3");
    player_spaceship = wi::scene::GetScene().Entity_FindByName("spaceship");

    RenderPath3D::Load();

//     wi::renderer::SetWireRender(true);
}

void WickedSpaceFlightRenderer::Update(float dt)
{
    wi::scene::TransformComponent *asteroid_transform = wi::scene::GetScene().transforms.GetComponent(asteroid);
    asteroid_transform->Rotate(XMVECTOR {dt * 5.0f, 0, 0});

    wi::scene::TransformComponent *player_transform = wi::scene::GetScene().transforms.GetComponent(player_spaceship);
    player_transform->Rotate(XMVectorSet(0,dt,0,1));

    RenderPath3D::Update(dt);
}
