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

	player_ = new Player();
	player_->Initialize();

	goal_ = new Goal();
	goal_->Initialize();
	

	
	



	
}

void GameScene::Update() {
	player_->Update();

	goal_->Update();
	
	CollisionPlayerGoal(player_->GetPosition(),goal_->GetPosition());
	/*debugText_->SetPos(0, 0);
	debugText_->Printf("%f,%f,%f", worldTransformPlayer_.translation_.x, worldTransformPlayer_.translation_.y, worldTransformPlayer_.translation_.z);
	debugText_->SetPos(0, 15);
	debugText_->Printf("GoalFlag:%d", GoalFlag);

	*/

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
	player_->Draw(viewProjection_);
	//modelplayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);

	goal_->Draw(viewProjection_);
	//modelgoal_->Draw(worldTransform, viewProjection_, textureHandleGoal_);

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
	//CollisionPlayerGoal();
}

void GameScene::CollisionPlayerGoal(Vector3 player,Vector3 goal)
{
	if (GoalFlag == 0)
	{
		float dx = (player.x - goal.x);
		float dy = (player.y - goal.y);
		float dz = (player.z - goal.z);
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
