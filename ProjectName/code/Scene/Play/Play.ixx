export module Scene.Play;

import <string>;
import <memory>;
export import Scene.SceneBase;

// 前方宣言
export namespace object
{
    class ObjectManager;
}

export namespace gameSystem
{
    class Camera;
}

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    /// <summary>
    /// プレイシーン
    /// </summary>
    export class Play final : public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Play();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Play() override;

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Initialize() override;

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 終了処理
        /// </summary>
        void Finalize() override;

        /// <summary>
        /// 次のシーンを取得
        /// </summary>
        /// <returns>次のシーン</returns>
        SceneType GetNextScene() const override { return m_nextScene; }

        /// <summary>
        /// シーン名を取得
        /// </summary>
        /// <returns>シーン名</returns>
        std::string GetSceneName() const override { return "Play"; }

    private:
        SceneType m_nextScene;                              // 次のシーン
        std::unique_ptr<object::ObjectManager> m_objectManager;  // オブジェクト管理
        std::unique_ptr<gameSystem::Camera> m_camera;       // カメラ
    };
}
