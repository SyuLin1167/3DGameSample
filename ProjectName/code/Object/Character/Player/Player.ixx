export module Object.Player;

import <string>;
export import Object.GameObject;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// プレイヤーオブジェクト
    /// </summary>
    export class Player final : public GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Player();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Player() override = default;

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

    private:
        /// <summary>
        /// 入力処理
        /// </summary>
        void HandleInput();

    private:
        static constexpr float MOVE_SPEED = 0.1f;  // 移動速度
        DxLib::VECTOR m_velocity;                         // 速度
    };
}
