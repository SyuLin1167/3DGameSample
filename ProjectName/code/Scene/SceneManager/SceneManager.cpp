module;
#include <DxLib.h>

module Scene.SceneManager;
import <memory>;
import <variant>;
import MyLib.KeyStatus;
import Scene.Title;
import GameSystem.FrameRate;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneManager::SceneManager()
        : m_pendingCmd(std::monostate{})
    {
        //最初のシーンをタイトルに設定
        m_currentScene.emplace(std::make_shared<Title>());
    }

    /// <summary>
    /// ゲームループ
    /// </summary>
    void SceneManager::GameLoop()
    {
        while (ProcessMessage() == 0)
        {
            // ESCキーが押されたら終了
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                break;
            }

            gameSystem::FrameRate::Update();

            // 更新処理
            Update();

            // 描画処理
            Draw();

            // フレームレート制御
            gameSystem::FrameRate::Wait();

            // シーンの切り替え
            ChangeScene();
        }
    }

    /// <summary>
    /// シーンの更新を行う
    /// </summary>
    void SceneManager::Update()
    {
        input::KeyStatus::UpdateKeyState();
        m_pendingCmd = m_currentScene.top()->Update();
    }

    /// <summary>
    /// シーンの描画を行う
    /// </summary>
    void SceneManager::Draw()
    {
        ClearDrawScreen();
        m_currentScene.top()->Draw();
        ScreenFlip();
    }

    /// <summary>
    /// シーンの切り替えを行う
    /// </summary>
    void SceneManager::ChangeScene()
    {
        // フレーム終端でコマンド適用
        std::visit(
            [this](auto&& cmd)
            {
                using T = std::decay_t<decltype(cmd)>;
                if constexpr (std::is_same_v<T, std::monostate>)
                {
                    // 何もしない
                }
                else if constexpr (std::is_same_v<T, CmdPush>)
                {
                    // 新しいシーンを積む
                    auto next = cmd.build ? cmd.build() : nullptr;
                    if (next)
                    {
                        m_currentScene.push(next);
                        m_currentScene.top()->Initialize();
                    }
                }
                else if constexpr (std::is_same_v<T, CmdReplace>)
                {
                    // 現在のシーンを置き換える
                    auto next = cmd.build ? cmd.build() : nullptr;
                    if (next)
                    {
                        if (!m_currentScene.empty())
                        {
                            m_currentScene.pop();
                        }
                        m_currentScene.push(next);
                        m_currentScene.top()->Initialize();
                    }
                }
                else if constexpr (std::is_same_v<T, CmdPop>)
                {
                    // 現在のシーンを取り除く
                    if (!m_currentScene.empty())
                    {
                        m_currentScene.pop();
                    }
                }
                else if constexpr (std::is_same_v<T, CmdQuit>)
                {
                    // ゲーム終了
                    PostQuitMessage(0);
                }
            },
            m_pendingCmd);

        // コマンドをクリア
        m_pendingCmd = std::monostate{};
    }
}
