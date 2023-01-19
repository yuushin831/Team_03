#include "GameScene.h"
#include "TextureManager.h"
#include"SetMatrix.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelplayer_;
	delete modelgoal_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//プレイヤー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelplayer_ = Model::Create();
	worldTransformPlayer_.Initialize();

	worldTransformPlayer_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransformPlayer_.translation_ = { 0.0f,-19.5f,0.0f };
	worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
	worldTransformPlayer_.TransferMatrix();

	//ゴール
	textureHandleGoal_ = TextureManager::Load("enemy.png");
	modelgoal_ = Model::Create();
	worldTransformGoal_.Initialize();

	worldTransformGoal_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransformGoal_.translation_ = { 35.5f,-8.0f,0.0f };
	worldTransformGoal_.matWorld_= CreatematWorld(worldTransformGoal_);
	worldTransformGoal_.TransferMatrix();
	



	
}

void GameScene::Update() {
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

	if (input_->PushKey(DIK_SPACE) && JumpCount == 0)
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
		if (worldTransformPlayer_.translation_.y <= -19.5f) {//着地したら
			worldTransformPlayer_.translation_.y = -19.5f;//めり込みを防ぐ
			JumpCount = 0;
		}
	}

	Collision();

	worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
	worldTransformPlayer_.TransferMatrix();
	debugText_->SetPos(0, 0);
	debugText_->Printf("%f,%f,%f", worldTransformPlayer_.translation_.x, worldTransformPlayer_.translation_.y, worldTransformPlayer_.translation_.z);
	debugText_->SetPos(0, 15);
	debugText_->Printf("GoalFlag:%d", GoalFlag);

	

}

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
	modelplayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
	modelgoal_->Draw(worldTransformGoal_, viewProjection_, textureHandleGoal_);

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

void GameScene::Collision()
{
	CollisionPlayerGoal();
}

void GameScene::CollisionPlayerGoal()
{
	if (GoalFlag == 0)
	{
		float dx = (worldTransformPlayer_.translation_.x - worldTransformGoal_.translation_.x);
		float dy = (worldTransformPlayer_.translation_.y - worldTransformGoal_.translation_.y);
		float dz = (worldTransformPlayer_.translation_.z - worldTransformGoal_.translation_.z);
		float PlayerR = 0.5f;//プレイヤー半径
		float GoalR = 0.5f;//ゴール半径
		float radius = (PlayerR + GoalR) * (PlayerR + GoalR);
		// 二つの座標の距離
		float dist = dx * dx + dy * dy + dz * dz;

		if (dist <= radius)
		{
			GoalFlag = 1;
			
		}
		
	}
	
	
}

void GameScene::PlayerUpdate()
{
	
	//worldTransformPlayer_.UpdateMatrix();

	
	
	
}
