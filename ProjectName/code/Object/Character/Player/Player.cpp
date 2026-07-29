module;
#include <DxLib.h>

module Object.Player;

import MyLib.KeyStatus;

using KeyHelper = ::input::KeyStatus;

namespace object
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player::Player()
        : m_velocity(VGet(0.0f, 0.0f, 0.0f))
    {
        m_tag = ObjectTag::Player;
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Player::Initialize()
    {
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void Player::Update()
    {
        HandleInput();

        // 速度を位置に加算
        m_position = VAdd(m_position, m_velocity);

        // 速度を減衰
        m_velocity = VScale(m_velocity, 0.9f);
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Player::Draw()
    {
        // プレイヤーを球体として描画
        DrawSphere3D(m_position, 1.0f, 16, GetColor(255, 100, 100), GetColor(255, 255, 255), TRUE);
    }

    /// <summary>
    /// 入力処理
    /// </summary>
    void Player::HandleInput()
    {
        VECTOR input = VGet(0.0f, 0.0f, 0.0f);

        constexpr int MOVE_KEY_STATE = ON_PRESS | PRESSING;

        // 矢印キーで移動
        if (KeyHelper::CheckKey(keyType.UP, MOVE_KEY_STATE))
        {
            input.z += 1.0f;
        }
        if (KeyHelper::CheckKey(keyType.DOWN, MOVE_KEY_STATE))
        {
            input.z -= 1.0f;
        }
        if (KeyHelper::CheckKey(keyType.LEFT, MOVE_KEY_STATE))
        {
            input.x -= 1.0f;
        }
        if (KeyHelper::CheckKey(keyType.RIGHT, MOVE_KEY_STATE))
        {
            input.x += 1.0f;
        }

        // 入力がある場合、正規化して速度に加算
        if (VSquareSize(input) > 0.0f)
        {
            input = VNorm(input);
            m_velocity = VAdd(m_velocity, VScale(input, MOVE_SPEED));
        }
    }
}
