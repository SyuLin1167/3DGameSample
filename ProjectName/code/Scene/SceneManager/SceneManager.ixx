export module Scene.SceneManager;

import <memory>;
import <unordered_map>;

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

        /// <summary>
        /// シーンを作成する
        /// </summary>
        /// <param name="type">シーンの種類</param>
        /// <returns>作成したシーン</returns>
        std::unique_ptr<SceneBase> CreateScene(SceneType type);

    private:
        std::unique_ptr<SceneBase> m_currentScene;  // 現在のシーン
        SceneType m_nextSceneType;                  // 次のシーンの種類
    };
}
