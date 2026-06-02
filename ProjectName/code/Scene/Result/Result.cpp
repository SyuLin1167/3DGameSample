module;
#include <DxLib.h>

module Scene.Result;
import Scene.Title;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Result::Result()
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
    SceneCmd Result::Update()
    {
        // スペースキーが押されたらタイトルシーンへ
        if (CheckHitKey(KEY_INPUT_SPACE))
        {
            return CmdReplace{ [] { return std::make_shared<Title>(); } };
        }

        return std::monostate{};
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
