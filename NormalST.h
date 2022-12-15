#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#pragma once
class NormalST
{
public:
	//初期化
	void Initialize(Model* model);
	//更新
	void Update();
	//表示
	void Draw(ViewProjection& viewProjection);
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	//uint32_t textureHandle_ = 0u;
	//ビュープロジェクション
	//ViewProjection viewProjection_;
};