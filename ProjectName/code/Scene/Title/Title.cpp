module;
#include <DxLib.h>

module Scene.Title;
import MyLib.KeyStatus;
import Scene.Play;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Title::Title()
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
    SceneCmd Title::Update()
    {
        // スペースキーが押されたらプレイシーンへ
        if (input::KeyStatus::CheckKey(keyType.SPACE, ON_PRESS))
        {
            return CmdReplace{ [] { return std::make_shared<Play>(); } };
        }

        return std::monostate{};
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
