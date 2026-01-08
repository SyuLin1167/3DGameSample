<h1 align="center">3D Game Sample</h1>
<div align="center">3Dゲームの基盤となるサンプルです。<p>2DJumpActionSampleを基に、3D空間でのゲーム開発のための基盤を提供します。</div>

<div align="center">
    <img src="http://img.shields.io/badge/license-MIT-blue.svg?style=flat">
</div>

## 🚀 使い方

### 1. リポジトリをクローン
```bash
git clone https://github.com/SyuLin1167/3DGameSample.git
```

### 2. DXライブラリのセットアップ
1. [DXライブラリ公式サイト](https://dxlib.xsrv.jp/)から最新版をダウンロード
2. ダウンロードしたファイルを解凍
3. `include/DxLib`ディレクトリにDXライブラリのヘッダーファイルとライブラリファイルをコピー

または、setup.batを実行してディレクトリ構造を作成してください。

### 3. Visual Studioで開く
1. `ProjectName/3DGameSample.sln`をVisual Studioで開く
2. プラットフォームを`x64`に設定
3. ビルドして実行

## 🎮 操作方法

### タイトル画面
- **SPACE**: ゲーム開始

### ゲーム画面
- **↑↓←→**: プレイヤー移動
- **R**: リザルト画面へ
- **ESC**: ゲーム終了

## 📁 プロジェクト構造

```
3DGameSample/
├── ProjectName/
│   ├── 3DGameSample.sln          # Visual Studioソリューションファイル
│   ├── code/                      # ソースコード
│   │   ├── main.cpp               # エントリーポイント
│   │   ├── GameSystem/            # ゲームシステム
│   │   │   ├── Execution/         # ゲーム実行管理
│   │   │   ├── Library/           # DXライブラリ初期化
│   │   │   ├── FrameRate/         # フレームレート管理
│   │   │   └── Camera/            # 3Dカメラ
│   │   ├── Scene/                 # シーン管理
│   │   │   ├── SceneBase/         # シーン基底クラス
│   │   │   ├── SceneManager/      # シーン管理
│   │   │   ├── Title/             # タイトルシーン
│   │   │   ├── Play/              # プレイシーン
│   │   │   └── Result/            # リザルトシーン
│   │   ├── Object/                # ゲームオブジェクト
│   │   │   ├── GameObject/        # オブジェクト基底クラス
│   │   │   ├── ObjectManager/     # オブジェクト管理
│   │   │   ├── Character/         # キャラクター
│   │   │   │   └── Player/        # プレイヤー
│   │   │   └── Map/               # ステージ/マップ
│   │   ├── Component/             # コンポーネント（拡張用）
│   │   └── Collision/             # 衝突判定（拡張用）
│   ├── project/                   # プロジェクト設定
│   │   └── project.vcxproj        # Visual Studioプロジェクトファイル
│   ├── include/                   # 外部ライブラリ
│   │   └── DxLib/                 # DXライブラリ（要インストール）
│   └── resources/                 # リソースファイル
│       ├── model/                 # 3Dモデル
│       ├── texture/               # テクスチャ
│       ├── sound/                 # サウンド
│       └── data/                  # データファイル
├── setup.bat                      # セットアップスクリプト
├── README.md
├── LICENSE
└── .gitignore
```

## 🔧 使用技術

このプロジェクトは以下の技術を使用しています：

* **C++20モジュール機能** (.ixx形式)
* **DXライブラリ** - 3D描画、入力処理
* **コンポーネント指向設計**
* **シーン管理システム**
* **オブジェクト管理システム**
* **3Dカメラシステム**
* **フレームレート制御**

## 📚 主な機能

### 実装済み
- ✅ 基本的な3D描画（球体、箱、グリッド）
- ✅ シーン管理（タイトル、プレイ、リザルト）
- ✅ プレイヤーの移動制御
- ✅ 3Dカメラシステム
- ✅ フレームレート管理
- ✅ オブジェクト管理システム

### 今後の拡張予定
- ⬜ 3D衝突判定システム（Box Collider, Sphere Collider）
- ⬜ コンポーネントシステムの実装
- ⬜ 3Dモデルの読み込みと表示
- ⬜ アニメーションシステム
- ⬜ パーティクルシステム
- ⬜ サウンド機能の統合
- ⬜ UI システム

## 🎯 開発のポイント

このサンプルは以下の点に重点を置いて設計されています：

1. **拡張性**: 新しいシーンやオブジェクトを簡単に追加できる構造
2. **モジュール性**: C++20のモジュール機能を活用した明確な依存関係
3. **保守性**: 基底クラスとマネージャーによる一貫した構造
4. **学習性**: シンプルで理解しやすいコード構成

## 💡 カスタマイズ方法

### 新しいシーンを追加する
1. `code/Scene/`に新しいシーンディレクトリを作成
2. `SceneBase`を継承したクラスを実装
3. `SceneType`列挙型に新しいシーンタイプを追加
4. `SceneManager::CreateScene()`に新しいシーンの生成処理を追加

### 新しいオブジェクトを追加する
1. `code/Object/`に新しいオブジェクトディレクトリを作成
2. `GameObject`を継承したクラスを実装
3. `ObjectManager::Initialize()`でオブジェクトを追加

## 📝 ライセンス

このプロジェクトはMITライセンスの下で公開されています。

## 🤝 貢献

プルリクエストを歓迎します！大きな変更の場合は、まずissueを開いて変更内容を議論してください。

## 📧 連絡先

問題や提案がある場合は、GitHubのissueを作成してください。

## 🙏 謝辞

このプロジェクトは[2DJumpActionSample](https://github.com/SyuLin1167/2DJumpActionSample)を基盤として作成されました。
