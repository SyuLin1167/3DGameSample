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
        /// コピー禁止令
        /// </summary>
        FrameRate(const FrameRate&) = delete;
        FrameRate(FrameRate&&) = delete;

        /// <summary>
        /// 代入禁止令
        /// </summary>
        FrameRate& operator=(const FrameRate&) = delete;
        FrameRate& operator=(FrameRate&&) = delete;

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~FrameRate() = default;

        /// <summary>
        /// 更新処理
        /// </summary>
        static void Update();

        /// <summary>
        /// 待機処理
        /// </summary>
        static void Wait();

        /// <summary>
        /// デルタタイムを取得
        /// </summary>
        /// <returns>デルタタイム(秒)</returns>
        static float GetDeltaTime() { return Instance().m_deltaTime; }

    private:
        /// <summary>
        /// 自身のインスタンスを返す
        /// </summary>
        /// <returns>自身のインスタンス</returns>
        static FrameRate& Instance()
        {
            static FrameRate instance;
            return instance;
        }

        /// <summary>
        /// コンストラクタ
        /// </summary>
        FrameRate();

        static constexpr int TARGET_FPS = 60;           // 目標FPS
        static constexpr float FRAME_TIME = 1000.0f / TARGET_FPS;  // 1フレームの時間(ミリ秒)

        int m_startTime;        // フレーム開始時刻
        float m_deltaTime;      // デルタタイム(秒)
    };
}
