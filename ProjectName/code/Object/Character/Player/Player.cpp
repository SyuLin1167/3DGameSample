module;
#include <DxLib.h>

module Object.Player;

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

        // 矢印キーで移動
        if (CheckHitKey(KEY_INPUT_UP))
        {
            input.z += 1.0f;
        }
        if (CheckHitKey(KEY_INPUT_DOWN))
        {
            input.z -= 1.0f;
        }
        if (CheckHitKey(KEY_INPUT_LEFT))
        {
            input.x -= 1.0f;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT))
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
