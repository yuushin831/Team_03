#pragma once
#include <cstdint>
#include <Model.h>
#include "Input.h"
#include "DebugText.h"

class Player
{
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	uint32_t textureHandle_ = 0;
	Model* modelplayer_;
	WorldTransform worldTransform_;
	int JumpCount = 0;
	int JumpMode = 0;
	float JumpSpeed_ = 0;

public://メンバ関数
	Player();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection &viewProjection);

	Vector3 GetPosition()
	{
		return worldTransform_.translation_;
	}
};

