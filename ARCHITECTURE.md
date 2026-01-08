# 3D Game Sample - アーキテクチャ図

## システム全体構成

```
┌─────────────────────────────────────────────────────────────┐
│                         main.cpp                             │
│                    (エントリーポイント)                        │
└─────────────────────┬───────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────┐
│                   GameSystem::Execution                      │
│                   (ゲーム実行管理)                            │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ Library (DXLib初期化)                                  │  │
│  │  - ウィンドウ設定                                       │  │
│  │  - 3D設定 (Z-buffer, Lighting, BackCulling)           │  │
│  └───────────────────────────────────────────────────────┘  │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ SceneManager (シーン管理)                              │  │
│  │  - GameLoop                                            │  │
│  │  - Scene切り替え                                       │  │
│  │  - FrameRate制御                                       │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────┐
│                    Scene System                              │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐     │
│  │    Title     │  │     Play     │  │    Result    │     │
│  │   シーン      │  │   シーン      │  │   シーン      │     │
│  └──────────────┘  └──────────────┘  └──────────────┘     │
│         │                 │                  │              │
│         │                 ▼                  │              │
│         │       ┌──────────────────┐         │              │
│         │       │ ObjectManager    │         │              │
│         │       │  - Player         │         │              │
│         │       │  - Map/Stage     │         │              │
│         │       │  - Other Objects │         │              │
│         │       └──────────────────┘         │              │
│         │                 │                  │              │
│         │                 ▼                  │              │
│         │       ┌──────────────────┐         │              │
│         │       │    Camera        │         │              │
│         │       │  - 位置/注視点    │         │              │
│         │       └──────────────────┘         │              │
└─────────────────────────────────────────────────────────────┘
```

## シーンの流れ

```
┌──────────┐     Space Key     ┌──────────┐     R Key     ┌──────────┐
│  Title   │ ─────────────────▶│   Play   │ ─────────────▶│  Result  │
│  Scene   │                    │  Scene   │                │  Scene   │
└──────────┘                    └──────────┘                └──────────┘
     ▲                                                            │
     │                         Space Key                         │
     └──────────────────────────────────────────────────────────┘
```

## クラス階層

### Scene System
```
SceneBase (interface)
├── Title
├── Play
└── Result
```

### Object System
```
GameObject (base class)
├── Player
│   └── 入力処理、移動、描画
├── Map
│   └── 地面、グリッド描画
└── (拡張可能)
    ├── Enemy
    ├── Item
    └── Obstacle
```

### Game System
```
GameSystem
├── Execution
│   └── ゲーム実行の統括
├── Library
│   └── DXLib初期化
├── FrameRate
│   └── FPS制御、デルタタイム管理
└── Camera
    └── 3Dカメラ制御
```

## データフロー

### 初期化フロー
```
1. main()
   ↓
2. Execution::Run()
   ↓
3. Library::Initialize()
   - DXLib初期化
   - ウィンドウ設定
   - 3D設定
   ↓
4. SceneManager::GameLoop()
   ↓
5. Scene::Initialize()
   ↓
6. ObjectManager::Initialize()
   ↓
7. GameObject::Initialize()
```

### ゲームループ
```
while (ウィンドウが開いている)
{
    FrameRate::Update()           // フレーム開始時刻記録
    ↓
    入力チェック (ESCキー等)
    ↓
    Scene::Update()
        ├─ ObjectManager::Update()
        │   └─ GameObject::Update()
        │       └─ 入力処理、移動、衝突判定等
        │
        └─ Camera::Update()
            └─ カメラ設定
    ↓
    ClearDrawScreen()             // 画面クリア
    ↓
    Scene::Draw()
        └─ ObjectManager::Draw()
            └─ GameObject::Draw()
                └─ 3D描画 (Sphere, Box, Line等)
    ↓
    ScreenFlip()                  // 画面反映
    ↓
    FrameRate::Wait()             // FPS調整のため待機
    ↓
    シーン切り替えチェック
}
```

## モジュール依存関係

```
main.cpp
  │
  └──▶ GameSystem.Execution
         ├──▶ GameSystem.Library
         │      └──▶ DxLib.h
         │
         └──▶ Scene.SceneManager
                ├──▶ Scene.SceneBase
                ├──▶ Scene.Title
                ├──▶ Scene.Play
                │      ├──▶ Object.ObjectManager
                │      │      ├──▶ Object.GameObject
                │      │      ├──▶ Object.Player
                │      │      └──▶ Object.Map
                │      │
                │      └──▶ GameSystem.Camera
                │
                ├──▶ Scene.Result
                └──▶ GameSystem.FrameRate
```

## 拡張ポイント

### 1. 新しいシーンの追加
```
code/Scene/NewScene/
├── NewScene.ixx        // インターフェース定義
└── NewScene.cpp        // 実装
```

### 2. 新しいオブジェクトの追加
```
code/Object/NewObject/
├── NewObject.ixx       // GameObjectを継承
└── NewObject.cpp       // 実装
```

### 3. コンポーネントの追加
```
code/Component/NewComponent/
├── NewComponent.ixx    // ComponentBaseを継承
└── NewComponent.cpp    // 実装
```

### 4. 衝突判定の追加
```
code/Collision/
├── Collider/           // 基底クラス
├── BoxCollider/        // ボックス衝突判定
├── SphereCollider/     // 球体衝突判定
└── ColliderManager/    // 衝突管理
```

## メモリ管理

### スマートポインタの使用
```cpp
// std::unique_ptr で所有権を明確に
std::unique_ptr<GameObject> player = std::make_unique<Player>();

// std::move で所有権を移動
m_objects.push_back(std::move(player));

// スマートポインタは自動的にdeleteされる
```

### オブジェクトのライフサイクル
```
作成 → Initialize() → Update()×N → Draw()×N → Finalize() → 削除
```

## パフォーマンス考慮事項

1. **描画最適化**
   - 画面外オブジェクトのカリング
   - LOD (Level of Detail)
   - バッチング

2. **更新最適化**
   - 非アクティブオブジェクトのスキップ
   - 空間分割（Quadtree等）
   - マルチスレッド処理

3. **メモリ最適化**
   - オブジェクトプール
   - リソースの共有
   - 遅延読み込み

## 開発の進め方

1. **プロトタイプ作成**
   - 基本機能の実装
   - シンプルな3D表現

2. **機能追加**
   - シーンの追加
   - オブジェクトの追加
   - ゲームロジックの実装

3. **ブラッシュアップ**
   - 3Dモデルの導入
   - エフェクトの追加
   - サウンドの統合

4. **最適化**
   - パフォーマンス測定
   - ボトルネックの特定
   - 改善の実施
