export module Scene.Title;

import <string>;
export import Scene.SceneBase;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    /// <summary>
    /// タイトルシーン
    /// </summary>
    export class Title final : public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Title();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Title() override = default;

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
        std::string GetSceneName() const override { return "Title"; }

    private:
        SceneType m_nextScene;  // 次のシーン
    };
}
