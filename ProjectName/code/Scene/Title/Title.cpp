module Scene.Title;

import <DxLib.h>;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Title::Title()
        : m_nextScene(SceneType::None)
    {
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Title::Initialize()
    {
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void Title::Update()
    {
        // スペースキーが押されたらプレイシーンへ
        if (CheckHitKey(KEY_INPUT_SPACE))
        {
            m_nextScene = SceneType::Play;
        }
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Title::Draw()
    {
        // タイトルテキストを描画
        DrawString(500, 300, "3D GAME SAMPLE", GetColor(255, 255, 255));
        DrawString(450, 350, "Press SPACE to Start", GetColor(255, 255, 255));
    }

    /// <summary>
    /// 終了処理
    /// </summary>
    void Title::Finalize()
    {
    }
}
