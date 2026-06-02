export module Scene.SceneManager;

import <memory>;
import <unordered_map>;
import <stack>;

export import Scene.SceneBase;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    /// <summary>
    /// シーンを管理する
    /// </summary>
    export class SceneManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SceneManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~SceneManager() = default;

        /// <summary>
        /// ゲームループ
        /// </summary>
        void GameLoop();

    private:
        /// <summary>
        /// シーンの更新を行う
        /// </summary>
        void Update();

        /// <summary>
        /// シーンの描画を行う
        /// </summary>
        void Draw();

        /// <summary>
        /// シーンの切り替えを行う
        /// </summary>
        void ChangeScene();

    private:
        std::stack<std::shared_ptr<SceneBase>> m_currentScene;  // 現在のシーン
        SceneCmd m_pendingCmd;                      //次フレームに適用するコマンド
    };
}
