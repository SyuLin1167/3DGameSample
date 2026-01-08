# リソースディレクトリ

このディレクトリには、ゲームで使用するリソースファイルを配置します。

## ディレクトリ構造

```
resources/
├── model/      # 3Dモデルファイル (.x, .mqo, .pmd など)
├── texture/    # テクスチャ画像 (.png, .jpg, .bmp など)
├── sound/      # サウンドファイル (.wav, .mp3, .ogg など)
└── data/       # その他のデータファイル (.json, .csv など)
```

## 使用方法

### 3Dモデル
```cpp
// モデルの読み込み
int modelHandle = MV1LoadModel("resources/model/character.x");

// モデルの描画
MV1DrawModel(modelHandle);

// モデルの削除
MV1DeleteModel(modelHandle);
```

### テクスチャ
```cpp
// テクスチャの読み込み
int textureHandle = LoadGraph("resources/texture/player.png");

// テクスチャの描画
DrawGraph(0, 0, textureHandle, TRUE);

// テクスチャの削除
DeleteGraph(textureHandle);
```

### サウンド
```cpp
// サウンドの読み込み
int soundHandle = LoadSoundMem("resources/sound/bgm.mp3");

// サウンドの再生
PlaySoundMem(soundHandle, DX_PLAYTYPE_LOOP);

// サウンドの停止
StopSoundMem(soundHandle);

// サウンドの削除
DeleteSoundMem(soundHandle);
```

### データファイル（JSON）
```cpp
// JSONファイルを読み込む場合は、nlohmann/jsonなどのライブラリを使用
#include <nlohmann/json.hpp>
#include <fstream>

std::ifstream file("resources/data/config.json");
nlohmann::json jsonData;
file >> jsonData;
```

## リソース作成のヒント

### 3Dモデル
- **推奨フォーマット**: .x (DirectX形式)、.mqo (メタセコイア)
- **ポリゴン数**: 低〜中程度（1,000〜10,000ポリゴン）
- **テクスチャサイズ**: 256x256、512x512、1024x1024など2のべき乗

### テクスチャ
- **推奨フォーマット**: .png（透過が必要な場合）、.jpg（写真など）
- **サイズ**: 2のべき乗（256x256、512x512、1024x1024など）
- **圧縮**: ゲーム実行時にメモリを節約するため、適切に圧縮

### サウンド
- **BGM**: .mp3 または .ogg（ループ対応）
- **効果音**: .wav（低遅延）
- **サンプリングレート**: 44.1kHz または 48kHz

## リソース管理のベストプラクティス

1. **命名規則**: わかりやすい名前を使用
   - 良い例: `player_walk.x`, `enemy_attack.wav`
   - 悪い例: `model1.x`, `sound.wav`

2. **整理**: サブディレクトリを作成して整理
   ```
   model/
   ├── characters/
   ├── enemies/
   └── stages/
   ```

3. **最適化**: 使用するリソースのみを読み込む
   ```cpp
   // ローディング画面でまとめて読み込み
   void LoadResources()
   {
       m_playerModel = MV1LoadModel("resources/model/player.x");
       m_playerTexture = LoadGraph("resources/texture/player.png");
       m_bgm = LoadSoundMem("resources/sound/stage1.mp3");
   }
   ```

4. **メモリ管理**: 使わなくなったリソースは削除
   ```cpp
   void UnloadResources()
   {
       MV1DeleteModel(m_playerModel);
       DeleteGraph(m_playerTexture);
       DeleteSoundMem(m_bgm);
   }
   ```

## フリー素材サイト

### 3Dモデル
- [ニコニ立体](https://3d.nicovideo.jp/)
- [Sketchfab](https://sketchfab.com/)（一部有料）

### テクスチャ
- [Textures.com](https://www.textures.com/)（無料枠あり）
- [OpenGameArt](https://opengameart.org/)

### サウンド
- [魔王魂](https://maou.audio/)
- [効果音ラボ](https://soundeffect-lab.info/)
- [DOVA-SYNDROME](https://dova-s.jp/)

## 注意事項

- リソースファイルは著作権に注意してください
- 商用利用する場合は、ライセンスを確認してください
- リソースファイルをGitリポジトリにコミットする場合、サイズに注意してください
  - 大きなファイル（>100MB）はGit LFSの使用を検討
