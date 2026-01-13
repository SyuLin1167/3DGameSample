export module Component.ComponentBase;

/// <summary>
/// コンポーネント関連
/// </summary>
export namespace component
{
    // 前方宣言
    namespace object
    {
        class GameObject;
    }

    /// <summary>
    /// コンポーネントの基底クラス
    /// </summary>
    export class ComponentBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        ComponentBase() : m_isActive(true) {}

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~ComponentBase() = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        virtual void Initialize() = 0;

        /// <summary>
        /// 更新処理
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// アクティブかどうかを取得
        /// </summary>
        /// <returns>アクティブならtrue</returns>
        bool IsActive() const { return m_isActive; }

        /// <summary>
        /// アクティブ状態を設定
        /// </summary>
        /// <param name="active">アクティブ状態</param>
        void SetActive(bool active) { m_isActive = active; }

    protected:
        bool m_isActive;  // アクティブかどうか
    };
}
