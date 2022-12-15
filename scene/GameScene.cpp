#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	delete spriteTitle_;
}

void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//タイトル２ｄ
	texturHandleTitle_ = TextureManager::Load("Title.png");
	spriteTitle_ = Sprite::Create(texturHandleTitle_, { 0,0 });
}

void GameScene::Update()
{
	//各シーンの更新処理を呼び出す
	switch (sceneMode_)
	{
	/*case 0:
		GaemPlayUpdate();
		break;*/
	case 1:
		TitleUpdate();
		break;
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>sishi
	//各シーンの更新処理を呼び出す
	switch (sceneMode_)
	{
	//case 0:
	//	GaemPlayDraw2DNear();
	//	break;
	case 1:
		TitleDraw2DNear();
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
//タイトル更新
void GameScene::TitleUpdate()
{
	//エンターキーを押した瞬間
	if (input_->TriggerKey(DIK_RETURN))
	{
		//ゲームプレイ移行
		sceneMode_ = 0;
	}
}
//タイトル表示
void GameScene::TitleDraw2DNear()
{
	spriteTitle_->Draw();
}
//ゲームプレイ更新
void GameScene::GaemPlayUpdate()
{

}