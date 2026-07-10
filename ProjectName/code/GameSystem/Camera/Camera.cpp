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
    /// 初期化処理
    /// </summary>
    void Camera::Initialize()
    {
        // カメラの描画範囲
        SetCameraNearFar(0.1f, 1000.0f);

        // 3D描画用のZバッファを有効化
        SetUseZBuffer3D(TRUE);
        SetWriteZBuffer3D(TRUE);

        Apply();
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void Camera::Update()
    {

    }

    /// <summary>
    /// カメラ設定をDxLibへ反映
    /// </summary>
    void Camera::Apply() const
    {
        SetCameraPositionAndTarget_UpVecY(
            m_position,
            m_target
        );
    }
}
