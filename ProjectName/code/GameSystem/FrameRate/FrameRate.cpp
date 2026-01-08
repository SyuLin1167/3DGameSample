module GameSystem.FrameRate;

import <DxLib.h>;

namespace gameSystem
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FrameRate::FrameRate()
        : m_startTime(0)
        , m_deltaTime(0.0f)
    {
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void FrameRate::Update()
    {
        m_startTime = GetNowCount();
    }

    /// <summary>
    /// 待機処理
    /// </summary>
    void FrameRate::Wait()
    {
        int elapsedTime = GetNowCount() - m_startTime;
        int waitTime = static_cast<int>(FRAME_TIME) - elapsedTime;

        if (waitTime > 0)
        {
            WaitTimer(waitTime);
        }

        // デルタタイムを計算(秒単位)
        int totalTime = GetNowCount() - m_startTime;
        m_deltaTime = totalTime / 1000.0f;
    }
}
