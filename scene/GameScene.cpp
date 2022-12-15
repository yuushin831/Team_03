#include "GameScene.h"
#include "TextureManager.h"
//#include "WorldTransform.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene()
{
	//チュートリアルステージ解放
	delete modelTutorialdome_;
	//ノーマルステージ解放
	delete modelNormaldome_;
	//ハードステージ解放
	delete modelHarddome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//チュートリアルステージ3Dモデルの生成
	modelTutorialdome_ = Model::CreateFromOBJ("tutorialdome", true);
	//ノーマルステージ3Dモデルの生成
	modelNormaldome_ = Model::CreateFromOBJ("normaldome", true);
	//ハードステージ3Dモデルの生成
	modelHarddome_ = Model::CreateFromOBJ("harddome", true);
	//チュートリアルステージ生成
	tutorialST_ = new TutorialST();
	//チュートリアルステージ初期化
	tutorialST_->Initialize(modelTutorialdome_);
	//ノーマルステージ生成
	normalST_ = new NormalST();
	//ノーマルステージ初期化
	normalST_->Initialize(modelNormaldome_);
	//ハードステージ生成
	hardST_ = new HardST();
	//ハードステージ初期化
	hardST_->Initialize(modelHarddome_);
	//ビュープロジェクション
	viewProjection_.Initialize();
}

void GameScene::Update()
{
	//チュートリアルステージ更新
	tutorialST_->Update();
	//ノーマルステージ更新
	normalST_->Update();
	//ハードステージ更新
	hardST_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//チュートリアルステージ描画
	tutorialST_->Draw(viewProjection_);
	//ノーマルステージ描画 
	normalST_->Draw(viewProjection_);
	//ハードステージ描画
	hardST_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
