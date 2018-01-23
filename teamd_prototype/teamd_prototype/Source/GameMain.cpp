#include "GameMain.h"

#include "SceneManager.h"
#include "KeyInput.h"
#include "SoundManager.h"
#include "ImageMng.h"
#include "EffectManager.h"

GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}

int GameMain::Init() {
	SceneManager::GetInstance().Initialize();
	KeyInput::GetInstance().Initialize();
	SoundManager::GetInstance().Initialize(); //Ç±Ç±Ç‡ÅIÇ®Ç±ÇæÇÊÅIxD
	ImageMng::Create();
	EffectManager::Instance().Initialize();
	return 0;
}
int GameMain::Update() {
	KeyInput::GetInstance().Update();
	SceneManager::GetInstance().Update();

	return 0;
}
int GameMain::Draw() {
	SceneManager::GetInstance().Draw();

	return 0;
}
void GameMain::End() {
	SceneManager::GetInstance().Finalize();
	KeyInput::GetInstance().Finalize();
	EffectManager::Instance().Finalize();

}