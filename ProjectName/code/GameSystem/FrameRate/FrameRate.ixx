export module GameSystem.FrameRate;

/// <summary>
/// システム関連
/// </summary>
export namespace gameSystem
{
    /// <summary>
    /// フレームレート管理
    /// </summary>
    export class FrameRate final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        FrameRate();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~FrameRate() = default;

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update();

        /// <summary>
        /// 待機処理
        /// </summary>
        void Wait();

        /// <summary>
        /// デルタタイムを取得
        /// </summary>
        /// <returns>デルタタイム(秒)</returns>
        float GetDeltaTime() const { return m_deltaTime; }

    private:
        static constexpr int TARGET_FPS = 60;           // 目標FPS
        static constexpr float FRAME_TIME = 1000.0f / TARGET_FPS;  // 1フレームの時間(ミリ秒)

        int m_startTime;        // フレーム開始時刻
        float m_deltaTime;      // デルタタイム(秒)
    };
}
