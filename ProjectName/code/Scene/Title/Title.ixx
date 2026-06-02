export module Scene.Title;

import <string>;
import Scene.SceneBase;

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
        SceneCmd Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 終了処理
        /// </summary>
        void Finalize() override;

        /// <summary>
        /// シーン名を取得
        /// </summary>
        /// <returns>シーン名</returns>
        std::string GetSceneName() const override { return "Title"; }
    };
}
