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

void TestsRenderer::Load()
{
    setSSREnabled(false);
    setReflectionsEnabled(true);
    setFXAAEnabled(false);

    static wi::audio::Sound sound;
    static wi::audio::SoundInstance soundinstance;

    // Reset all state that tests might have modified:
    wi::eventhandler::SetVSync(true);
    wi::renderer::SetToDrawGridHelper(false);
    wi::renderer::SetTemporalAAEnabled(false);
    wi::renderer::ClearWorld(wi::scene::GetScene());
    wi::scene::GetScene().weather = wi::scene::WeatherComponent();
    this->ClearSprites();
    this->ClearFonts();
    if (wi::lua::GetLuaState() != nullptr) {
        wi::lua::KillProcesses();
    }
    // Reset camera position:
    wi::scene::TransformComponent transform;
    transform.Translate(XMFLOAT3(0, 2.f, -4.5f));
    transform.UpdateTransform();
    wi::scene::GetCamera().TransformCamera(transform);

    float screenW = GetLogicalWidth();
    float screenH = GetLogicalHeight();

    // This will spawn a sprite with two textures. The first texture is a color texture and it will be animated.
    //	The second texture is a static image of "hello world" written on it
    //	Then add some animations to the sprite to get a nice wobbly and color changing effect.
    //	You can learn more in the Sprite test in RunSpriteTest() function

//     static wi::Sprite sprite;
//     sprite = wi::Sprite("images/movingtex.png", "images/HelloWorld.png");
//     sprite.params.pos = XMFLOAT3(screenW / 2, screenH / 2, 0);
//     sprite.params.siz = XMFLOAT2(200, 100);
//     sprite.params.pivot = XMFLOAT2(0.5f, 0.5f);
//     sprite.anim.rot = XM_PI / 4.0f;
//     sprite.anim.wobbleAnim.amount = XMFLOAT2(0.16f, 0.16f);
//     sprite.anim.movingTexAnim.speedX = 0;
//     sprite.anim.movingTexAnim.speedY = 3;
//     this->AddSprite(&sprite);

    asteroid = wi::ecs::CreateEntity();

    RenderPath3D::Load();
}
void TestsRenderer::Update(float dt)
{
    RenderPath3D::Update(dt);
}
