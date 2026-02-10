#include <Windows.h>
#include"kamataEngine.h"
#include"GameScene.h"


using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//エンジン初期化
	KamataEngine::Initialize(L"LC1D_24_ヒチワ_リク_AL2");
	//Die
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	GameScene* gameScene = new GameScene();

	gameScene->Initialize();


	//メインループ
	while (true) {
		//エンジンの更新
		if (KamataEngine::Update())
		{
			break;
		}

		gameScene->Update();
		//描画開始
		dxCommon->PreDraw();

		gameScene->Draw();

		// 描画終了
		dxCommon->PostDraw();


	}

	delete gameScene;
	gameScene = nullptr;
	//エンジンの終了処理
	KamataEngine::Finalize();
	return 0;
}
