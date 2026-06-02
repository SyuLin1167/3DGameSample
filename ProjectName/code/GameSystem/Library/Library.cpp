module;
#include <DxLib.h>

module GameSystem.Library;

namespace gameSystem
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Library::Library()
    {
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <returns>-1:エラー|0:正常終了</returns>
    int Library::Initialize()
    {
        // ウィンドウの設定
        SetupWindow();

        // 3D関連の設定
        Setup3D();

        // DXライブラリの初期化
        if (DxLib_Init() == -1)
        {
            return -1;
        }

        // 描画先を裏画面にする
        SetDrawScreen(DX_SCREEN_BACK);

        return 0;
    }

    /// <summary>
    /// ウィンドウの設定を行う
    /// </summary>
    void Library::SetupWindow()
    {
        // ウィンドウモードで起動
        ChangeWindowMode(TRUE);

        // ウィンドウサイズの設定
        SetGraphMode(1280, 720, 32);

        // ウィンドウタイトルの設定
        SetMainWindowText("3D Game Sample");

        // ウィンドウの背景色を設定
        SetBackgroundColor(100, 149, 237);  // コーンフラワーブルー
    }

    /// <summary>
    /// 3D関連の設定を行う
    /// </summary>
    void Library::Setup3D()
    {
        // Zバッファを有効にする
        SetUseZBuffer3D(TRUE);

        // Zバッファへの書き込みを有効にする
        SetWriteZBuffer3D(TRUE);

        // バックカリングを有効にする
        SetUseBackCulling(TRUE);

        // ライティングを有効にする
        SetUseLighting(TRUE);

        // デフォルトライトの設定
        ChangeLightTypeDir(VGet(0.3f, -0.7f, 0.8f));

        // カメラのクリップ距離を設定
        SetCameraNearFar(1.0f, 1000.0f);
    }
}
