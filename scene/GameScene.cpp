#include "GameScene.h"
#include "TextureManager.h"
#include"SetMatrix.h"
//#include "WorldTransform.h"
#include <cassert>
//コンストラクタ
GameScene::GameScene() {}
//デストラクタ
GameScene::~GameScene()
{
	//チュートリアルステージ解放
	delete modelTutorialdome_;
	//ノーマルステージ解放
	delete modelNormaldome_;
	//ハードステージ解放
	delete modelHarddome_;

	delete title_;
	delete GameScene_;
	delete GamePlay_;
	delete GameCrear_;
	delete GameOver_;
	delete modelplayer_;
}
//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//チュートリアルステージ3Dモデルの生成
	modelTutorialdome_ = Model::CreateFromOBJ("tutorialdome", true);
	//ノーマルステージ3Dモデルの生成
	modelNormaldome_ = Model::CreateFromOBJ("normaldome", true);
	//ハードステージ3Dモデルの生成
	modelHarddome_ = Model::CreateFromOBJ("harddome", true);
	//チュートリアルステージ生成
	tutorialST_ = new TutorialST();
	//チュートリアルステージ初期化
	tutorialST_->Initialize(modelTutorialdome_);
	//ノーマルステージ生成
	normalST_ = new NormalST();
	//ノーマルステージ初期化
	normalST_->Initialize(modelNormaldome_);
	//ハードステージ生成
	hardST_ = new HardST();
	//ハードステージ初期化
	hardST_->Initialize(modelHarddome_);
	//ビュープロジェクション
	viewProjection_.Initialize();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//テクスチャを入れ込む
	textureHandle_[0] = TextureManager::Load("Title.png");
	textureHandle_[1] = TextureManager::Load("GameScene.png");
	textureHandle_[2] = TextureManager::Load("GamePlay.png");
	textureHandle_[3] = TextureManager::Load("GameCrear.png");
	textureHandle_[4] = TextureManager::Load("GameOver.png");
	//プレイヤー
	textureHandlePlayer_ = TextureManager::Load("player.png");

	//スプライトを生成
	title_ = Sprite::Create(textureHandle_[0], { 0,0 });
	GameScene_ = Sprite::Create(textureHandle_[1], { 0,0 });
	GamePlay_ = Sprite::Create(textureHandle_[2], { 0,0 });
	GameCrear_ = Sprite::Create(textureHandle_[3], { 0,0 });
	GameOver_ = Sprite::Create(textureHandle_[4], { 0,0 });

	modelplayer_ = Model::Create();
	//worldTransformPlayer_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransformPlayer_.Initialize();

	worldTransformPlayer_.scale_ = { 1.0f,1.0f,1.0f };

	//Matrix4 matScale = CreatematWorld(worldTransformPlayer_);
	worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
	worldTransformPlayer_.TransferMatrix();
}
//更新
void GameScene::Update()
{
	//チュートリアルステージ更新
	//tutorialST_->Update();
	//ノーマルステージ更新
	//normalST_->Update();
	//ハードステージ更新
	//hardST_->Update();
	switch (scene_)
	{

		//タイトル
	case 0:
#pragma region TITLE
		//初期化
		Timer = 250;
		if (input_->TriggerKey(DIK_RIGHT))
		{
			scene_ = 1;
		}
		break;

		//ゲーム説明
	case 1:
#pragma region GAMESCENE
		if (input_->TriggerKey(DIK_1))
		{
			scene_ = 2;
		}
		if (input_->TriggerKey(DIK_2))
		{
			scene_ = 3;
		}
		if (input_->TriggerKey(DIK_3))
		{
			scene_ = 4;
		}

		break;
		//ゲームプレイ(チュートリアルステージ)
	case 2:
#pragma region GAMEPLAY
		//チュートリアルステージ更新
		tutorialST_->Update();
		//移動
		if (input_->PushKey(DIK_D))
		{
			worldTransformPlayer_.translation_.x += 0.5f;
		}
		if (input_->PushKey(DIK_A))
		{
			worldTransformPlayer_.translation_.x -= 0.5f;
		}

		if (worldTransformPlayer_.translation_.x >= 35.5f) {
			worldTransformPlayer_.translation_.x = 35.5f;
		}

		if (worldTransformPlayer_.translation_.x <= -35.5f) {
			worldTransformPlayer_.translation_.x = -35.5f;
		}

		if (input_->PushKey(DIK_W) && JumpCount == 0)
		{
			JumpMode = 1;
			JumpCount = 1;
			JumpSpeed_ = 0.5f;//ジャンプの初速

		}
		//ジャンプ実施
		if (JumpCount == 1)
		{
			worldTransformPlayer_.translation_.y += JumpSpeed_;//Y座標にジャンプスピードを加える
			JumpSpeed_ -= 0.01f;//ジャンプスピードに重力を加える
			if (worldTransformPlayer_.translation_.y <= 0) {//着地したら
				worldTransformPlayer_.translation_.y = 0;//めり込みを防ぐ
				JumpCount = 0;
			}
		}

		worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
		worldTransformPlayer_.TransferMatrix();
		/*if (scene_ == 2)
		{
			Timer--;
		}
		if (Timer < 0)
		{
			scene_ = 6;
		}*/

		break;
		//ゲームプレイ(ノーマルステージ)
	case 3:
#pragma region GAMEPLAY
		//ノーマルステージ更新
		normalST_->Update();
		//移動
		if (input_->PushKey(DIK_D))
		{
			worldTransformPlayer_.translation_.x += 0.5f;
		}
		if (input_->PushKey(DIK_A))
		{
			worldTransformPlayer_.translation_.x -= 0.5f;
		}

		if (worldTransformPlayer_.translation_.x >= 35.5f) {
			worldTransformPlayer_.translation_.x = 35.5f;
		}

		if (worldTransformPlayer_.translation_.x <= -35.5f) {
			worldTransformPlayer_.translation_.x = -35.5f;
		}

		if (input_->PushKey(DIK_W) && JumpCount == 0)
		{
			JumpMode = 1;
			JumpCount = 1;
			JumpSpeed_ = 0.5f;//ジャンプの初速

		}
		//ジャンプ実施
		if (JumpCount == 1)
		{
			worldTransformPlayer_.translation_.y += JumpSpeed_;//Y座標にジャンプスピードを加える
			JumpSpeed_ -= 0.01f;//ジャンプスピードに重力を加える
			if (worldTransformPlayer_.translation_.y <= 0) {//着地したら
				worldTransformPlayer_.translation_.y = 0;//めり込みを防ぐ
				JumpCount = 0;
			}
		}

		worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
		worldTransformPlayer_.TransferMatrix();
		/*if (scene_ == 2)
		{
			Timer--;
		}
		if (Timer < 0)
		{
			scene_ = 7;
		}*/

		break;
		//ゲームプレイ(ハードステージ)
	case 4:
#pragma region GAMEPLAY
		//ハードステージ更新
		hardST_->Update();
		//移動
		if (input_->PushKey(DIK_D))
		{
			worldTransformPlayer_.translation_.x += 0.5f;
		}
		if (input_->PushKey(DIK_A))
		{
			worldTransformPlayer_.translation_.x -= 0.5f;
		}

		if (worldTransformPlayer_.translation_.x >= 35.5f) {
			worldTransformPlayer_.translation_.x = 35.5f;
		}

		if (worldTransformPlayer_.translation_.x <= -35.5f) {
			worldTransformPlayer_.translation_.x = -35.5f;
		}

		if (input_->PushKey(DIK_W) && JumpCount == 0)
		{
			JumpMode = 1;
			JumpCount = 1;
			JumpSpeed_ = 0.5f;//ジャンプの初速

		}
		//ジャンプ実施
		if (JumpCount == 1)
		{
			worldTransformPlayer_.translation_.y += JumpSpeed_;//Y座標にジャンプスピードを加える
			JumpSpeed_ -= 0.01f;//ジャンプスピードに重力を加える
			if (worldTransformPlayer_.translation_.y <= 0) {//着地したら
				worldTransformPlayer_.translation_.y = 0;//めり込みを防ぐ
				JumpCount = 0;
			}
		}

		worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
		worldTransformPlayer_.TransferMatrix();
		/*if (scene_ == 2)
		{
			Timer--;
		}
		if (Timer < 0)
		{
			scene_ = 8;
		}*/

		break;
		//ゲームクリア
	case 5:
#pragma region GAMECREAR
		if (input_->TriggerKey(DIK_RIGHT))
		{
			scene_ = 0;
		}

		break;
		//ゲームオーバー(チュートリアルステージ)
	case 6:
#pragma region GAMEOVER
		if (input_->TriggerKey(DIK_RIGHT))
		{
			scene_ = 2;
		}

		break;
		//ゲームオーバー(ノーマルステージ)
	case 7:
#pragma region GAMEOVER
		if (input_->TriggerKey(DIK_RIGHT))
		{
			scene_ = 3;
		}

		break;
		//ゲームオーバー(ハードステージ)
	case 8:
#pragma region GAMEOVER
		if (input_->TriggerKey(DIK_RIGHT))
		{
			scene_ = 4;
		}

		break;
	}

	//テキストの表示
	DebugText::GetInstance()->SetPos(1000, 0);
	DebugText::GetInstance()->Printf("scene_:%d", scene_);
	DebugText::GetInstance()->SetPos(1000, 30);
	DebugText::GetInstance()->Printf("Timer:%d", Timer);
}
//表示
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
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

	//////////シーン分け待ちここから//////////
	//modelplayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);



	//////////シーン分け待ちここまで//////////
	switch (scene_)
	{
	case 2:
		modelplayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
		//チュートリアルステージ描画
		tutorialST_->Draw(viewProjection_);
		break;
	case 3:
		modelplayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
		//ノーマルステージ描画 
		normalST_->Draw(viewProjection_);
		break;
	case 4:
		modelplayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
		//ハードステージ描画
		hardST_->Draw(viewProjection_);
		break;
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
		//表示
	switch (scene_)
	{
	case 0:
		title_->Draw();
		break;
	case 1:
		GameScene_->Draw();
		break;
	case 2:
		//GamePlay_->Draw();
		debugText_->DrawAll(commandList);
		break;
	case 3:
		//GamePlay_->Draw();
		debugText_->DrawAll(commandList);
		break;
	case 4:
		//GamePlay_->Draw();
		debugText_->DrawAll(commandList);
		break;
	case 5:
		GameCrear_->Draw();
		break;
	case 6:
		GameOver_->Draw();
		break;
	case 7:
		GameOver_->Draw();
		break;
	case 8:
		GameOver_->Draw();
		break;
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
