export module Scene.SceneBase;
export import <string>;
export import <memory>;
export import <functional>;
export import <variant>;
export import Object.ObjectManager;

/// <summary>
/// シーン関連
/// </summary>
export namespace scene
{
    export class SceneBase;   // 前方宣言
    export using SceneBuilder = std::function<std::shared_ptr<SceneBase>()>;    // シーン構築関数

    export struct CmdPush { SceneBuilder build; };      // シーンを積む
    export struct CmdReplace { SceneBuilder build; };   // シーンを置き換える
    export struct CmdPop {};                            // シーンを削除する
    export struct CmdQuit {};                           // 終了要求

    export using SceneCmd = std::variant<std::monostate, CmdPush, CmdReplace, CmdPop, CmdQuit>; // シーンコマンド

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
        virtual SceneCmd Update() = 0;

        /// <summary>
        /// 描画処理
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// 終了処理
        /// </summary>
        virtual void Finalize() = 0;

        /// <summary>
        /// シーン名を取得
        /// </summary>
        /// <returns>シーン名</returns>
        virtual std::string GetSceneName() const = 0;
    };
}
