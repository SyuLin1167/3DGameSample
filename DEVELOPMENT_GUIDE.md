# 3D Game Sample - 開発ガイド

## 概要
このドキュメントでは、3D Game Sampleを使用してゲームを開発する方法について説明します。

## アーキテクチャ

### シーンシステム
シーンはゲームの状態を管理する単位です。各シーンは以下のライフサイクルを持ちます：

1. **Initialize()** - シーン開始時に1回だけ呼ばれる
2. **Update()** - 毎フレーム呼ばれる（ゲームロジック）
3. **Draw()** - 毎フレーム呼ばれる（描画処理）
4. **Finalize()** - シーン終了時に1回だけ呼ばれる

#### 新しいシーンの追加方法

```cpp
// 1. SceneBase.ixxにシーンタイプを追加
export enum class SceneType
{
    None,
    Title,
    Play,
    Result,
    Stage2,  // ← 新しく追加
};

// 2. 新しいシーンクラスを作成
// code/Scene/Stage2/Stage2.ixx
export module Scene.Stage2;

import <string>;
export import Scene.SceneBase;

export namespace scene
{
    export class Stage2 final : public SceneBase
    {
    public:
        Stage2();
        ~Stage2() override = default;
        
        void Initialize() override;
        void Update() override;
        void Draw() override;
        void Finalize() override;
        
        SceneType GetNextScene() const override { return m_nextScene; }
        std::string GetSceneName() const override { return "Stage2"; }
        
    private:
        SceneType m_nextScene;
    };
}

// 3. SceneManager.cppのCreateScene()に追加
std::unique_ptr<SceneBase> SceneManager::CreateScene(SceneType type)
{
    switch (type)
    {
    case SceneType::Title:
        return std::make_unique<Title>();
    case SceneType::Play:
        return std::make_unique<Play>();
    case SceneType::Result:
        return std::make_unique<Result>();
    case SceneType::Stage2:  // ← 追加
        return std::make_unique<Stage2>();
    default:
        return nullptr;
    }
}
```

### オブジェクトシステム
GameObjectはゲーム内のすべてのエンティティの基底クラスです。

#### 新しいオブジェクトの作成方法

```cpp
// code/Object/Enemy/Enemy.ixx
export module Object.Enemy;

import <string>;
export import Object.GameObject;

export namespace object
{
    export class Enemy final : public GameObject
    {
    public:
        Enemy();
        ~Enemy() override = default;
        
        void Initialize() override;
        void Update() override;
        void Draw() override;
        
    private:
        VECTOR m_velocity;
        float m_speed;
    };
}

// ObjectManagerで使用
void ObjectManager::Initialize()
{
    // 敵を追加
    auto enemy = std::make_unique<Enemy>();
    enemy->SetPosition(VGet(10.0f, 0.0f, 0.0f));
    AddObject(std::move(enemy));
}
```

### カメラシステム
3Dカメラの位置と注視点を制御します。

```cpp
// カメラの位置を設定
m_camera->SetPosition(VGet(0.0f, 15.0f, -25.0f));

// プレイヤーを追従させる
VECTOR playerPos = player->GetPosition();
m_camera->SetTarget(playerPos);
m_camera->SetPosition(VAdd(playerPos, VGet(0.0f, 10.0f, -20.0f)));
```

## よくある開発タスク

### 1. プレイヤーの移動速度を変更する
`code/Object/Character/Player/Player.ixx`の`MOVE_SPEED`定数を変更します：

```cpp
private:
    static constexpr float MOVE_SPEED = 0.2f;  // 値を大きくすると速くなる
```

### 2. カメラの初期位置を変更する
`code/GameSystem/Camera/Camera.cpp`のコンストラクタを変更します：

```cpp
Camera::Camera()
    : m_position(VGet(0.0f, 20.0f, -30.0f))  // 位置を変更
    , m_target(VGet(0.0f, 0.0f, 0.0f))
    , m_up(VGet(0.0f, 1.0f, 0.0f))
{
}
```

### 3. ウィンドウサイズを変更する
`code/GameSystem/Library/Library.cpp`の`SetupWindow()`を変更します：

```cpp
void Library::SetupWindow()
{
    ChangeWindowMode(TRUE);
    SetGraphMode(1920, 1080, 32);  // サイズを変更
    SetMainWindowText("3D Game Sample");
    SetBackgroundColor(100, 149, 237);
}
```

### 4. フレームレートを変更する
`code/GameSystem/FrameRate/FrameRate.ixx`の`TARGET_FPS`を変更します：

```cpp
private:
    static constexpr int TARGET_FPS = 60;  // 30や120などに変更可能
```

### 5. 地面の色を変更する
`code/Object/Map/Map.cpp`の`Draw()`メソッドを変更します：

```cpp
DrawBox3D(
    VGet(-50.0f, -1.0f, -50.0f),
    VGet(50.0f, 0.0f, 50.0f),
    GetColor(200, 100, 100),  // 赤っぽい地面に変更
    GetColor(255, 255, 255),
    TRUE
);
```

## デバッグのヒント

### 1. デバッグ情報の表示
任意のシーンのDraw()メソッドで情報を表示できます：

```cpp
void Play::Draw()
{
    // オブジェクトの描画
    m_objectManager->Draw();
    
    // デバッグ情報
    VECTOR playerPos = /* プレイヤーの位置を取得 */;
    DrawFormatString(10, 10, GetColor(255, 255, 255), 
        "Player: (%.1f, %.1f, %.1f)", playerPos.x, playerPos.y, playerPos.z);
}
```

### 2. ワイヤーフレーム表示
物体をワイヤーフレームで描画してデバッグ：

```cpp
DrawSphere3D(m_position, 1.0f, 16, GetColor(255, 100, 100), 
             GetColor(255, 255, 255), FALSE);  // FALSE = ワイヤーフレーム
```

## パフォーマンスの最適化

### 1. 描画の最適化
- 画面外のオブジェクトは描画をスキップ
- 遠くのオブジェクトは簡易モデルで描画（LOD）
- オブジェクトをまとめて描画（バッチング）

### 2. 更新処理の最適化
- 非アクティブなオブジェクトは更新をスキップ
- 画面外のオブジェクトは簡易更新
- 重い処理は複数フレームに分散

## トラブルシューティング

### ビルドエラー
- DXライブラリが正しくインストールされているか確認
- プロジェクト設定でx64プラットフォームが選択されているか確認
- C++20が有効になっているか確認

### 実行時エラー
- DXライブラリのDLLがexeと同じディレクトリにあるか確認
- リソースファイルのパスが正しいか確認

### パフォーマンスの問題
- フレームレートをチェック（FrameRate::GetDeltaTime()）
- オブジェクト数を確認
- 描画負荷を確認（ポリゴン数、テクスチャサイズ）

## 次のステップ

このサンプルを基に、以下の機能を追加していくことをお勧めします：

1. **衝突判定システム** - 3D空間での当たり判定
2. **物理演算** - 重力、跳ね返りなど
3. **3Dモデルの読み込み** - .x, .mqo, .pmd などのフォーマット
4. **アニメーション** - キャラクターアニメーション
5. **パーティクル** - 爆発、煙などのエフェクト
6. **サウンド** - BGM、効果音
7. **UI** - HP表示、スコアなど
8. **セーブ/ロード** - ゲームデータの保存

詳細については、DXライブラリの公式ドキュメントを参照してください：
https://dxlib.xsrv.jp/
