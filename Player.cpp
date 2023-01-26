#include "Player.h"
#include "SetMatrix.h"

Player::Player()
{
	textureHandle_ = TextureManager::Load("player.png");
	modelplayer_ = Model::Create();
	worldTransform_.Initialize();
}

void Player::Initialize()
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_.translation_ = { 0.0f,-19.5f,0.0f };
	worldTransform_.matWorld_ = CreatematWorld(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Update()
{
	//移動
	if (input_->PushKey(DIK_D))
	{
		worldTransform_.translation_.x += 0.5f;
	}
	if (input_->PushKey(DIK_A))
	{
		worldTransform_.translation_.x -= 0.5f;
	}

	if (worldTransform_.translation_.x >= 35.5f) {
		worldTransform_.translation_.x = 35.5f;
	}

	if (worldTransform_.translation_.x <= -35.5f) {
		worldTransform_.translation_.x = -35.5f;
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
		worldTransform_.translation_.y += JumpSpeed_;//Y座標にジャンプスピードを加える
		JumpSpeed_ -= 0.01f;//ジャンプスピードに重力を加える
		if (worldTransform_.translation_.y <= -19.5f) {//着地したら
			worldTransform_.translation_.y = -19.5f;//めり込みを防ぐ
			JumpCount = 0;
		}
	}
	//
	//Collision();

	worldTransform_.matWorld_ = CreatematWorld(worldTransform_);
	worldTransform_.TransferMatrix();
	debugText_->SetPos(0, 0);
	debugText_->Printf("%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	debugText_->SetPos(0, 15);
	
}

void Player::Draw(ViewProjection& viewProjection)
{
	modelplayer_->Draw(worldTransform_, viewProjection, textureHandle_);
}
