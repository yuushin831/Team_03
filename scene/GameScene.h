﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "PrimitiveDrawer.h"
#include "TutorialST.h"
#include "NormalST.h"
#include "HardST.h"
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
	ViewProjection viewProjection_;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;


	//チュートリアルステージ
	Model* modelTutorialdome_ = nullptr;
	TutorialST* tutorialST_ = nullptr;
	//ノーマルステージ
	Model* modelNormaldome_ = nullptr;
	NormalST* normalST_ = nullptr;
	//ハードステージ
	Model* modelHarddome_ = nullptr;
	HardST* hardST_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
