module;
#include <DxLib.h>

module Object.GameObject;

namespace object
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameObject::GameObject()
        : m_position(VGet(0.0f, 0.0f, 0.0f))
        , m_rotation(VGet(0.0f, 0.0f, 0.0f))
        , m_scale(VGet(1.0f, 1.0f, 1.0f))
        , m_tag(ObjectTag::None)
        , m_isActive(true)
    {
    }
}
