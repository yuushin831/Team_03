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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	int  sceneMode_ = 1;
	void TitleUpdate();
	void TitleDraw2DNear();
	//タイトル（スプライト）
	uint32_t texturHandleTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;

	void GaemPlayUpdate(); //ゲームプレイ更新
	void GaemPlayDraw3D(); //ゲームプレイ３D更新
	void GaemPlayDraw2DBack(); //ゲームプレイ背景２D表示
	void GaemPlayDraw2DNear();//ゲームプレイ近影２D表示
};
