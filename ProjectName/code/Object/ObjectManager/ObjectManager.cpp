module Object.ObjectManager;

import <memory>;
#include "algorithm";

import Object.Player;
import Object.Map;

namespace object
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ObjectManager::ObjectManager()
    {
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void ObjectManager::Initialize()
    {
        // プレイヤーを追加
        auto player = std::make_unique<Player>();
        player->SetPosition(VGet(0.0f, 0.0f, 0.0f));
        AddObject(std::move(player));

        // ステージを追加
        auto stage = std::make_unique<Map>();
        AddObject(std::move(stage));

        // 全オブジェクトの初期化
        for (auto& obj : m_objects)
        {
            obj->Initialize();
        }
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void ObjectManager::Update()
    {
        // アクティブなオブジェクトのみ更新
        for (auto& obj : m_objects)
        {
            if (obj->IsActive())
            {
                obj->Update();
            }
        }

        // 非アクティブなオブジェクトを削除
        m_objects.erase(
            std::remove_if(m_objects.begin(), m_objects.end(),
                [](const std::unique_ptr<GameObject>& obj) { return !obj->IsActive(); }),
            m_objects.end()
        );
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void ObjectManager::Draw()
    {
        // アクティブなオブジェクトのみ描画
        for (auto& obj : m_objects)
        {
            if (obj->IsActive())
            {
                obj->Draw();
            }
        }
    }

    /// <summary>
    /// オブジェクトを追加
    /// </summary>
    /// <param name="object">オブジェクト</param>
    void ObjectManager::AddObject(std::unique_ptr<GameObject> object)
    {
        m_objects.push_back(std::move(object));
    }

    /// <summary>
    /// オブジェクトをクリア
    /// </summary>
    void ObjectManager::Clear()
    {
        m_objects.clear();
    }
}
