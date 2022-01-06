#include "stdafx.h"
#include "WickedSpaceFlight.h"

#include <string>
#include <sstream>
#include <fstream>
#include <thread>

using namespace wiECS;
using namespace wiScene;

void WickedSpaceFlight::Initialize()
{
    wiRenderer::SetShaderSourcePath(WickedEngine_SHADER_DIR);
    MainComponent::Initialize();

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

	static wiAudio::Sound sound;
	static wiAudio::SoundInstance soundinstance;

    // Reset all state that tests might have modified:
    wiEvent::SetVSync(true);
    wiRenderer::SetToDrawGridHelper(false);
    wiRenderer::SetTemporalAAEnabled(false);
    wiRenderer::ClearWorld(wiScene::GetScene());
    wiScene::GetScene().weather = WeatherComponent();
    this->ClearSprites();
    this->ClearFonts();
    if (wiLua::GetLuaState() != nullptr) {
        wiLua::KillProcesses();
    }
    // Reset camera position:
    TransformComponent transform;
    transform.Translate(XMFLOAT3(0, 2.f, -4.5f));
    transform.UpdateTransform();
    wiScene::GetCamera().TransformCamera(transform);

    float screenW = GetLogicalWidth();
    float screenH = GetLogicalHeight();

    // This will spawn a sprite with two textures. The first texture is a color texture and it will be animated.
    //	The second texture is a static image of "hello world" written on it
    //	Then add some animations to the sprite to get a nice wobbly and color changing effect.
    //	You can learn more in the Sprite test in RunSpriteTest() function
    static wiSprite sprite;
    sprite = wiSprite("images/movingtex.png", "images/HelloWorld.png");
    sprite.params.pos = XMFLOAT3(screenW / 2, screenH / 2, 0);
    sprite.params.siz = XMFLOAT2(200, 100);
    sprite.params.pivot = XMFLOAT2(0.5f, 0.5f);
    sprite.anim.rot = XM_PI / 4.0f;
    sprite.anim.wobbleAnim.amount = XMFLOAT2(0.16f, 0.16f);
    sprite.anim.movingTexAnim.speedX = 0;
    sprite.anim.movingTexAnim.speedY = 3;
    this->AddSprite(&sprite);

    RenderPath3D::Load();
}
void TestsRenderer::Update(float dt)
{
    RenderPath3D::Update(dt);
}
