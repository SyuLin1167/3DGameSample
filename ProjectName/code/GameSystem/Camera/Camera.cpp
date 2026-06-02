module;
#include <DxLib.h>

module GameSystem.Camera;

namespace gameSystem
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Camera::Camera()
        : m_position(VGet(0.0f, 10.0f, -20.0f))
        , m_target(VGet(0.0f, 0.0f, 0.0f))
        , m_up(VGet(0.0f, 1.0f, 0.0f))
    {
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void Camera::Update()
    {
        // カメラの設定
        SetCameraPositionAndTarget_UpVecY(m_position, m_target);
    }
}
