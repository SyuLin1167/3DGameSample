module GameSystem.Execution;

import <memory>;
import <DxLib.h>;

import GameSystem.Library;
import Scene.SceneManager;

namespace gameSystem
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Execution::Execution()
        : m_library(std::make_unique<Library>())
        , m_scene(std::make_unique<scene::SceneManager>())
    {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Execution::~Execution()
    {
    }

    /// <summary>
    /// ゲームを実行する
    /// </summary>
    /// <returns>-1:エラー|0:正常終了</returns>
    int Execution::Run()
    {
        // ライブラリの初期化に失敗したら終了
        if (m_library->Initialize() == -1)
        {
            return -1;
        }

        // ゲームループ
        m_scene->GameLoop();

        // DXライブラリの終了処理
        DxLib_End();

        return 0;
    }
}
