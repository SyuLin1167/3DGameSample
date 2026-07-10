module;
#include <DxLib.h>

module Scene.Play;
import <memory>;
import Scene.Result;
import Object.ObjectManager;
import GameSystem.Camera;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Play::Play()
        : m_objectManager(std::make_unique<object::ObjectManager>())
        , m_camera(std::make_unique<gameSystem::Camera>())
    {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Play::~Play()
    {
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Play::Initialize()
    {
        // カメラの初期化
        m_camera->Initialize();

        // オブジェクトの初期化
        m_objectManager->Initialize();
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    SceneCmd Play::Update()
    {
        // Rキーが押されたらリザルトシーンへ
        if (CheckHitKey(KEY_INPUT_R))
        {
            return CmdReplace{ [] { return std::make_shared<Result>(); } };
        }

        // オブジェクトの更新
        m_objectManager->Update();

        // カメラの更新
        m_camera->Update();

        return std::monostate{};
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Play::Draw()
    {
        // カメラ反映
        m_camera->Apply();

        // オブジェクトの描画
        m_objectManager->Draw();

        // UI描画
        DrawString(10, 10, "Play Scene", GetColor(255, 255, 255));
        DrawString(10, 30, "Arrow Keys: Move", GetColor(255, 255, 255));
        DrawString(10, 50, "R: Result", GetColor(255, 255, 255));
    }

    /// <summary>
    /// 終了処理
    /// </summary>
    void Play::Finalize()
    {
    }
}
