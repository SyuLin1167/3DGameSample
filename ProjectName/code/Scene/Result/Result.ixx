export module Scene.Result;

import <string>;
export import Scene.SceneBase;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    /// <summary>
    /// リザルトシーン
    /// </summary>
    export class Result final : public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Result();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Result() override = default;

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
        std::string GetSceneName() const override { return "Result"; }
    };
}
