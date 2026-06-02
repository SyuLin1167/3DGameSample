module;
#include <DxLib.h>

module GameSystem.FrameRate;

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
        Instance().m_startTime = GetNowCount();
    }

    /// <summary>
    /// 待機処理
    /// </summary>
    void FrameRate::Wait()
    {
        int elapsedTime = GetNowCount() - Instance().m_startTime;
        int waitTime = static_cast<int>(FRAME_TIME) - elapsedTime;

        if (waitTime > 0)
        {
            WaitTimer(waitTime);
        }

        // デルタタイムを計算(秒単位)
        int totalTime = GetNowCount() - Instance().m_startTime;
        Instance().m_deltaTime = totalTime / 1000.0f;
    }
}
