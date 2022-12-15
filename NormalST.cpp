#include "NormalST.h"
#include"Procession.h"
#include <cassert>
//初期化
void NormalST::Initialize(Model* model)
{
	//NULLポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 100,100,100 };
	worldTransform_.translation_ = { 0,0,0 };
}
//更新
void NormalST::Update()
{
	//回転
	//worldTransform_.rotation_ += {0, 0.001f, 0};
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}
//表示
void NormalST::Draw(ViewProjection& viewProjection_)
{
	//model_->Draw(worldTransform_, viewProjection_);
}
