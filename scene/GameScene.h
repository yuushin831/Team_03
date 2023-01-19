#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定
	/// </summary>
	void Collision();// 衝突判定
	void CollisionPlayerGoal();// 衝突判定(プレイヤーとゴール)

	

	

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//プレイヤー
	uint32_t textureHandlePlayer_ = 0;
	Model* modelplayer_;
	WorldTransform worldTransformPlayer_;
	int JumpCount = 0;
	int JumpMode = 0;
	float JumpSpeed_ = 0;

	//ゴール
	uint32_t textureHandleGoal_ = 0;
	Model* modelgoal_;
	WorldTransform worldTransformGoal_;
	int GoalFlag = 0;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	void PlayerUpdate();
};
