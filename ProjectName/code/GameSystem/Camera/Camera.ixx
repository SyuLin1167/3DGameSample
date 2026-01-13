export module GameSystem.Camera;

import <DxLib.h>;

/// <summary>
/// システム関連
/// </summary>
export namespace gameSystem
{
    /// <summary>
    /// 3Dカメラ管理
    /// </summary>
    export class Camera final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Camera();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Camera() = default;

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update();

        /// <summary>
        /// カメラ位置を設定
        /// </summary>
        /// <param name="pos">カメラ位置</param>
        void SetPosition(const VECTOR& pos) { m_position = pos; }

        /// <summary>
        /// 注視点を設定
        /// </summary>
        /// <param name="target">注視点</param>
        void SetTarget(const VECTOR& target) { m_target = target; }

        /// <summary>
        /// カメラ位置を取得
        /// </summary>
        /// <returns>カメラ位置</returns>
        VECTOR GetPosition() const { return m_position; }

        /// <summary>
        /// 注視点を取得
        /// </summary>
        /// <returns>注視点</returns>
        VECTOR GetTarget() const { return m_target; }

    private:
        VECTOR m_position;      // カメラ位置
        VECTOR m_target;        // 注視点
        VECTOR m_up;            // カメラの上方向ベクトル
    };
}
