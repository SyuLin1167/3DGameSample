export module Object.ObjectManager;

import <memory>;
import <vector>;

export import Object.GameObject;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// オブジェクトを管理する
    /// </summary>
    export class ObjectManager final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ObjectManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~ObjectManager() = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Initialize();

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update();

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw();

        /// <summary>
        /// オブジェクトを追加
        /// </summary>
        /// <param name="object">オブジェクト</param>
        void AddObject(std::unique_ptr<GameObject> object);

        /// <summary>
        /// オブジェクトをクリア
        /// </summary>
        void Clear();

    private:
        std::vector<std::unique_ptr<GameObject>> m_objects;  // オブジェクトリスト
    };
}
