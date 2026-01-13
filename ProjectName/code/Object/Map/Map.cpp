module Object.Map;

import <DxLib.h>;

namespace object
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Map::Map()
    {
        m_tag = ObjectTag::Stage;
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Map::Initialize()
    {
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void Map::Update()
    {
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Map::Draw()
    {
        // 地面を描画
        DrawBox3D(
            VGet(-50.0f, -1.0f, -50.0f),
            VGet(50.0f, 0.0f, 50.0f),
            GetColor(100, 200, 100),
            GetColor(255, 255, 255),
            TRUE
        );

        // グリッドを描画
        DrawGrid();
    }

    /// <summary>
    /// グリッドを描画
    /// </summary>
    void Map::DrawGrid()
    {
        const float GRID_SIZE = 5.0f;
        const int GRID_COUNT = 20;
        const unsigned int COLOR = GetColor(150, 150, 150);

        // X方向のライン
        for (int i = -GRID_COUNT; i <= GRID_COUNT; ++i)
        {
            float x = i * GRID_SIZE;
            DrawLine3D(
                VGet(x, 0.01f, -GRID_COUNT * GRID_SIZE),
                VGet(x, 0.01f, GRID_COUNT * GRID_SIZE),
                COLOR
            );
        }

        // Z方向のライン
        for (int i = -GRID_COUNT; i <= GRID_COUNT; ++i)
        {
            float z = i * GRID_SIZE;
            DrawLine3D(
                VGet(-GRID_COUNT * GRID_SIZE, 0.01f, z),
                VGet(GRID_COUNT * GRID_SIZE, 0.01f, z),
                COLOR
            );
        }
    }
}
