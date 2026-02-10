#include <Novice.h>

const char kWindowTitle[] = "LC1D_24_ヒチワ_リク_タイトル";

// ===== イーズインアウト関数 =====
float EaseOutQuad(float t) {
    float result;

    if (t < 0.5f) {
        result = 2.0f * t * t; // 前半：加速
    }
    else {
        result = -1.0f + (4.0f - 2.0f * t) * t; // 後半：減速
    }

    return result;
}

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // アニメーション用変数
    float startX = 100.0f;
    float endX = 1100.0f;
    float elapsedTime = 0.0f;
    float duration = 2.0f;  // 秒
    float posY = 300.0f;
    float radius = 50.0f;
    int direction = 1; // 1:右へ, -1:左へ

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理
        ///

        // 時間を進める（1フレーム60FPS想定）
        elapsedTime += 1.0f / 60.0f * direction;

        // t を 0～1 に正規化
        float t = elapsedTime / duration;
        if (t > 1.0f)
        {
            t = 1.0f;
            direction = -1;  // 右から左へ
        }
        if (t < 0.0f) 
        {
            t = 0.0f;
            direction = 1;   // 左から右へ
        }

        // イーズインアウトで補間
        float factor = EaseOutQuad(t);

        // 移動座標
        float posX = startX + (endX - startX) * factor;

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理
        ///

        Novice::DrawEllipse((int)posX, (int)posY, (int)radius, (int)radius,0, WHITE, kFillModeSolid);

        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーで終了
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
