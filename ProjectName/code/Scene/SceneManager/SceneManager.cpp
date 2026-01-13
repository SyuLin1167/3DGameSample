module Scene.SceneManager;

import <memory>;
import <DxLib.h>;

import Scene.Title;
import Scene.Play;
import Scene.Result;
import GameSystem.FrameRate;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneManager::SceneManager()
        : m_currentScene(nullptr)
        , m_nextSceneType(SceneType::Title)
    {
        // 最初のシーンを作成
        ChangeScene();
    }

    /// <summary>
    /// ゲームループ
    /// </summary>
    void SceneManager::GameLoop()
    {
        gameSystem::FrameRate frameRate;

        while (ProcessMessage() == 0)
        {
            frameRate.Update();

            // ESCキーが押されたら終了
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                break;
            }

            // 更新処理
            Update();

            // 画面クリア
            ClearDrawScreen();

            // 描画処理
            Draw();

            // 画面反映
            ScreenFlip();

            // フレームレート制御
            frameRate.Wait();
        }
    }

    /// <summary>
    /// シーンの更新を行う
    /// </summary>
    void SceneManager::Update()
    {
        if (m_currentScene)
        {
            m_currentScene->Update();

            // 次のシーンがあれば切り替える
            SceneType nextType = m_currentScene->GetNextScene();
            if (nextType != SceneType::None)
            {
                m_nextSceneType = nextType;
                ChangeScene();
            }
        }
    }

    /// <summary>
    /// シーンの描画を行う
    /// </summary>
    void SceneManager::Draw()
    {
        if (m_currentScene)
        {
            m_currentScene->Draw();
        }
    }

    /// <summary>
    /// シーンの切り替えを行う
    /// </summary>
    void SceneManager::ChangeScene()
    {
        // 現在のシーンの終了処理
        if (m_currentScene)
        {
            m_currentScene->Finalize();
        }

        // 次のシーンを作成
        m_currentScene = CreateScene(m_nextSceneType);

        // 新しいシーンの初期化
        if (m_currentScene)
        {
            m_currentScene->Initialize();
        }

        // 次のシーンタイプをリセット
        m_nextSceneType = SceneType::None;
    }

    /// <summary>
    /// シーンを作成する
    /// </summary>
    /// <param name="type">シーンの種類</param>
    /// <returns>作成したシーン</returns>
    std::unique_ptr<SceneBase> SceneManager::CreateScene(SceneType type)
    {
        switch (type)
        {
        case SceneType::Title:
            return std::make_unique<Title>();
        case SceneType::Play:
            return std::make_unique<Play>();
        case SceneType::Result:
            return std::make_unique<Result>();
        default:
            return nullptr;
        }
    }
}
