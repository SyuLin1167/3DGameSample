module;
#include <DxLib.h>

module Scene.Play;
import <memory>;
import Object.ObjectManager;
import GameSystem.Camera;

namespace scene
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Play::Play()
        : m_nextScene(SceneType::None)
        , m_objectManager(std::make_unique<object::ObjectManager>())
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
        // オブジェクトの初期化
        m_objectManager->Initialize();
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void Play::Update()
    {
        // Rキーが押されたらリザルトシーンへ
        if (CheckHitKey(KEY_INPUT_R))
        {
            m_nextScene = SceneType::Result;
        }

        // オブジェクトの更新
        m_objectManager->Update();

        // カメラの更新
        m_camera->Update();
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Play::Draw()
    {
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
