#include "GameScene.h"
#include "TextureManager.h"
#include"SetMatrix.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelplayer_;
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
	//worldTransformPlayer_.scale_ = { 0.5f,0.5f,0.5f };
	worldTransformPlayer_.Initialize();

	worldTransformPlayer_.scale_ = { 1.0f,1.0f,1.0f };

	//Matrix4 matScale = CreatematWorld(worldTransformPlayer_);
	worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
	worldTransformPlayer_.TransferMatrix();
	



	
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
		if (worldTransformPlayer_.translation_.y <= 0) {//着地したら
			worldTransformPlayer_.translation_.y = 0;//めり込みを防ぐ
			JumpCount = 0;
		}
	}

	worldTransformPlayer_.matWorld_ = CreatematWorld(worldTransformPlayer_);
	worldTransformPlayer_.TransferMatrix();
	debugText_->SetPos(0, 0);
	debugText_->Printf("%f,%f,%f", worldTransformPlayer_.translation_.x, worldTransformPlayer_.translation_.y, worldTransformPlayer_.translation_.z);
	/*Matrix4 matIdentity;
	matIdentity.m[0][0] = 1;
	matIdentity.m[1][1] = 1;
	matIdentity.m[2][2] = 1;
	matIdentity.m[3][3] = 1;

	Matrix4 matScale;

	matScale.m[0][0] = worldTransformPlayer_.scale_.x;
	matScale.m[1][1] = worldTransformPlayer_.scale_.y;
	matScale.m[2][2] = worldTransformPlayer_.scale_.z;
	matScale.m[3][3] = 1;*/

	/*worldTransformPlayer_.matWorld_ = matIdentity;
	worldTransformPlayer_.matWorld_ *= matScale;*/


	/*Matrix4 matTrans = MathUtility::Matrix4Identity();

	matTrans.m[3][0] = worldTransformPlayer_.translation_.x;
	matTrans.m[3][1] = worldTransformPlayer_.translation_.y;
	matTrans.m[3][2] = worldTransformPlayer_.translation_.z;
	matTrans.m[3][3] = 1;

	worldTransformPlayer_.matWorld_ = matIdentity;
	worldTransformPlayer_.matWorld_ *= matScale *= matTrans;


	worldTransformPlayer_.TransferMatrix();*/

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

void GameScene::PlayerUpdate()
{
	
	//worldTransformPlayer_.UpdateMatrix();

	
	
	
}
