export module Object.Map;

import <string>;
export import Object.GameObject;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// マップ/ステージオブジェクト
    /// </summary>
    export class Map final : public GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Map();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Map() override = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Initialize() override;

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update() override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() override;

    private:
        /// <summary>
        /// グリッドを描画
        /// </summary>
        void DrawGrid();
    };
}
