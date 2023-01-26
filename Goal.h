#pragma once
#include <cstdint>
#include <Model.h>
class Goal
{
private:
	uint32_t textureHandle_ = 0;
	Model* modelgoal_;
	WorldTransform worldTransform_;
	int GoalFlag = 0;

public:
	Goal();
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
	void Draw(ViewProjection& viewProjection);

	Vector3 GetPosition()
	{
		return worldTransform_.translation_;
	}
};

