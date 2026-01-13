module Scene.Result;

import <DxLib.h>;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Result::Result()
        : m_nextScene(SceneType::None)
    {
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Result::Initialize()
    {
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void Result::Update()
    {
        // スペースキーが押されたらタイトルシーンへ
        if (CheckHitKey(KEY_INPUT_SPACE))
        {
            m_nextScene = SceneType::Title;
        }
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Result::Draw()
    {
        // リザルトテキストを描画
        DrawString(500, 300, "RESULT", GetColor(255, 255, 255));
        DrawString(450, 350, "Press SPACE to Title", GetColor(255, 255, 255));
    }

    /// <summary>
    /// 終了処理
    /// </summary>
    void Result::Finalize()
    {
    }
}
