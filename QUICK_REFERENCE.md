# 3D Game Sample - クイックリファレンス

## 📋 主要なクラスとメソッド

### GameSystem（ゲームシステム）

#### Execution - ゲーム実行管理
```cpp
int Run();  // ゲームを実行
```

#### Library - DXライブラリ初期化
```cpp
int Initialize();  // ライブラリの初期化
```

#### FrameRate - フレームレート管理
```cpp
void Update();              // フレーム開始時に呼ぶ
void Wait();                // フレーム終了時に呼ぶ
float GetDeltaTime() const; // デルタタイム（秒）を取得
```

#### Camera - 3Dカメラ
```cpp
void SetPosition(const VECTOR& pos);  // カメラ位置を設定
void SetTarget(const VECTOR& target); // 注視点を設定
VECTOR GetPosition() const;           // カメラ位置を取得
VECTOR GetTarget() const;             // 注視点を取得
void Update();                        // カメラを更新（毎フレーム呼ぶ）
```

### Scene（シーン）

#### SceneBase - シーン基底クラス
```cpp
virtual void Initialize() = 0;          // 初期化
virtual void Update() = 0;              // 更新
virtual void Draw() = 0;                // 描画
virtual void Finalize() = 0;            // 終了処理
virtual SceneType GetNextScene() const = 0;  // 次のシーン
virtual std::string GetSceneName() const = 0; // シーン名
```

#### SceneManager - シーン管理
```cpp
void GameLoop();  // ゲームループ（自動でUpdate/Draw/シーン切り替え）
```

### Object（オブジェクト）

#### GameObject - ゲームオブジェクト基底クラス
```cpp
// 位置・回転・スケール
void SetPosition(const VECTOR& pos);
void SetRotation(const VECTOR& rot);
void SetScale(const VECTOR& scale);
VECTOR GetPosition() const;
VECTOR GetRotation() const;
VECTOR GetScale() const;

// タグ
void SetTag(ObjectTag tag);
ObjectTag GetTag() const;

// アクティブ状態
void SetActive(bool active);
bool IsActive() const;

// 継承して実装するメソッド
virtual void Initialize() = 0;
virtual void Update() = 0;
virtual void Draw() = 0;
```

#### ObjectManager - オブジェクト管理
```cpp
void Initialize();  // オブジェクトの初期化
void Update();      // オブジェクトの更新
void Draw();        // オブジェクトの描画
void AddObject(std::unique_ptr<GameObject> object);  // オブジェクトを追加
void Clear();       // 全オブジェクトをクリア
```

## 🎨 DXライブラリの主要な3D描画関数

### 基本図形
```cpp
// 球体
DrawSphere3D(VECTOR pos, float r, int divNum, 
             unsigned int diffuseColor, unsigned int specularColor, 
             int fillFlag);

// 箱
DrawBox3D(VECTOR pos1, VECTOR pos2, 
          unsigned int diffuseColor, unsigned int specularColor, 
          int fillFlag);

// カプセル
DrawCapsule3D(VECTOR pos1, VECTOR pos2, float r, int divNum,
              unsigned int diffuseColor, unsigned int specularColor,
              int fillFlag);

// 線
DrawLine3D(VECTOR pos1, VECTOR pos2, unsigned int color);
```

### ベクトル操作
```cpp
VECTOR VGet(float x, float y, float z);           // ベクトル作成
VECTOR VAdd(VECTOR v1, VECTOR v2);                // 加算
VECTOR VSub(VECTOR v1, VECTOR v2);                // 減算
VECTOR VScale(VECTOR v, float scale);             // スケール
VECTOR VNorm(VECTOR v);                           // 正規化
float VSize(VECTOR v);                            // 長さ
float VSquareSize(VECTOR v);                      // 長さの二乗
float VDot(VECTOR v1, VECTOR v2);                 // 内積
VECTOR VCross(VECTOR v1, VECTOR v2);              // 外積
```

### カメラ制御
```cpp
// カメラ設定（位置、注視点、上方向）
SetCameraPositionAndTarget_UpVecY(VECTOR position, VECTOR target);

// カメラのクリップ距離
SetCameraNearFar(float nearZ, float farZ);

// 視野角設定
SetupCamera_Perspective(float fov);
```

### ライト
```cpp
// 方向性ライト
ChangeLightTypeDir(VECTOR direction);

// ライトの有効/無効
SetUseLighting(int flag);

// 環境光
SetGlobalAmbientLight(COLOR_F color);
```

### 3D設定
```cpp
// Zバッファ
SetUseZBuffer3D(int flag);
SetWriteZBuffer3D(int flag);

// バックカリング
SetUseBackCulling(int flag);

// フォグ（霧）
SetFogEnable(int flag);
SetFogColor(int r, int g, int b);
SetFogStartEnd(float start, float end);
```

## ⌨️ 入力関数

### キーボード
```cpp
int CheckHitKey(int keyCode);  // キーが押されているか（1フレーム中）

// キーコード例
KEY_INPUT_UP        // ↑
KEY_INPUT_DOWN      // ↓
KEY_INPUT_LEFT      // ←
KEY_INPUT_RIGHT     // →
KEY_INPUT_SPACE     // スペース
KEY_INPUT_RETURN    // Enter
KEY_INPUT_ESCAPE    // ESC
KEY_INPUT_W         // W
KEY_INPUT_A         // A
KEY_INPUT_S         // S
KEY_INPUT_D         // D
```

### マウス
```cpp
int GetMousePoint(int *x, int *y);              // マウス座標取得
int GetMouseInput();                             // マウスボタン状態
int GetMouseWheelRotVol(int CounterReset);      // ホイール回転量
```

## 🎮 よく使うコードスニペット

### プレイヤーの移動（WASD）
```cpp
VECTOR input = VGet(0.0f, 0.0f, 0.0f);
if (CheckHitKey(KEY_INPUT_W)) input.z += 1.0f;
if (CheckHitKey(KEY_INPUT_S)) input.z -= 1.0f;
if (CheckHitKey(KEY_INPUT_A)) input.x -= 1.0f;
if (CheckHitKey(KEY_INPUT_D)) input.x += 1.0f;

if (VSquareSize(input) > 0.0f)
{
    input = VNorm(input);
    m_velocity = VAdd(m_velocity, VScale(input, MOVE_SPEED));
}
m_position = VAdd(m_position, m_velocity);
```

### カメラをプレイヤーに追従
```cpp
// プレイヤーの後ろからの視点
VECTOR cameraOffset = VGet(0.0f, 5.0f, -10.0f);
VECTOR cameraPos = VAdd(playerPos, cameraOffset);
m_camera->SetPosition(cameraPos);
m_camera->SetTarget(playerPos);
```

### オブジェクト間の距離チェック
```cpp
VECTOR diff = VSub(obj1->GetPosition(), obj2->GetPosition());
float distance = VSize(diff);
if (distance < 2.0f)
{
    // 衝突処理
}
```

### 回転アニメーション
```cpp
// Update()内で
m_rotation.y += 0.02f;  // Y軸周りに回転
if (m_rotation.y > DX_PI_F * 2.0f)
{
    m_rotation.y -= DX_PI_F * 2.0f;
}
```

### デバッグ情報表示
```cpp
DrawFormatString(10, 10, GetColor(255, 255, 255), 
                "FPS: %.1f", 1.0f / deltaTime);
DrawFormatString(10, 30, GetColor(255, 255, 255),
                "Pos: (%.1f, %.1f, %.1f)", pos.x, pos.y, pos.z);
```

## 🔢 定数

### 数学定数
```cpp
DX_PI_F      // π (float)
DX_PI        // π (double)
DX_TWO_PI_F  // 2π (float)
```

### 色
```cpp
GetColor(255, 255, 255)  // 白
GetColor(0, 0, 0)        // 黒
GetColor(255, 0, 0)      // 赤
GetColor(0, 255, 0)      // 緑
GetColor(0, 0, 255)      // 青
```

### 画面制御
```cpp
DX_SCREEN_BACK   // 裏画面
DX_SCREEN_FRONT  // 表画面
```

## 📚 参考リンク

- [DXライブラリ公式サイト](https://dxlib.xsrv.jp/)
- [DXライブラリ リファレンス](https://dxlib.xsrv.jp/dxfunc.html)
- [3D機能リファレンス](https://dxlib.xsrv.jp/function/dxfunc_3d.html)
