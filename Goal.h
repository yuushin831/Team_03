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
	/// ‰Šú‰»
	/// </summary>
	void Initialize();
	/// <summary>
	/// XV
	/// </summary>
	void Update();
	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	Vector3 GetPosition()
	{
		return worldTransform_.translation_;
	}
};

