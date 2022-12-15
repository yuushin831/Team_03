#include "NormalST.h"
#include"Procession.h"
#include <cassert>
//������
void NormalST::Initialize(Model* model)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 100,100,100 };
	worldTransform_.translation_ = { 0,0,0 };
}
//�X�V
void NormalST::Update()
{
	//��]
	//worldTransform_.rotation_ += {0, 0.001f, 0};
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}
//�\��
void NormalST::Draw(ViewProjection& viewProjection_)
{
	//model_->Draw(worldTransform_, viewProjection_);
}
