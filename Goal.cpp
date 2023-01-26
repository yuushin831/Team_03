#include "Goal.h"
#include "SetMatrix.h"

Goal::Goal()
{
	textureHandle_ = TextureManager::Load("enemy.png");
	modelgoal_ = Model::Create();
	worldTransform_.Initialize();
}

void Goal::Initialize()
{
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_.translation_ = { 35.5f,-8.0f,0.0f };
	worldTransform_.matWorld_ = CreatematWorld(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Goal::Update()
{
}

void Goal::Draw(ViewProjection& viewProjection)
{
	modelgoal_->Draw(worldTransform_, viewProjection, textureHandle_);

}


