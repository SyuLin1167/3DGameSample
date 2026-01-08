export module Scene.SceneBase;

import <string>;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    /// <summary>
    /// シーンの種類
    /// </summary>
    export enum class SceneType
    {
        None,       // なし
        Title,      // タイトル
        Play,       // プレイ
        Result,     // リザルト
    };

    /// <summary>
    /// シーンの基底クラス
    /// </summary>
    export class SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SceneBase() = default;

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~SceneBase() = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        virtual void Initialize() = 0;

        /// <summary>
        /// 更新処理
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// 描画処理
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// 終了処理
        /// </summary>
        virtual void Finalize() = 0;

        /// <summary>
        /// 次のシーンを取得
        /// </summary>
        /// <returns>次のシーン</returns>
        virtual SceneType GetNextScene() const = 0;

        /// <summary>
        /// シーン名を取得
        /// </summary>
        /// <returns>シーン名</returns>
        virtual std::string GetSceneName() const = 0;
    };
}
