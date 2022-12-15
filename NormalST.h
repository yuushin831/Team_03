#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#pragma once
class NormalST
{
public:
	//������
	void Initialize(Model* model);
	//�X�V
	void Update();
	//�\��
	void Draw(ViewProjection& viewProjection);
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	//uint32_t textureHandle_ = 0u;
	//�r���[�v���W�F�N�V����
	//ViewProjection viewProjection_;
};