export module GameSystem.Library;

/// <summary>
/// システム関連
/// </summary>
export namespace gameSystem
{
    /// <summary>
    /// DXライブラリの初期化を行う
    /// </summary>
    export class Library final
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Library();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Library() = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        /// <returns>-1:エラー|0:正常終了</returns>
        int Initialize();

    private:
        /// <summary>
        /// ウィンドウの設定を行う
        /// </summary>
        void SetupWindow();

        /// <summary>
        /// 3D関連の設定を行う
        /// </summary>
        void Setup3D();
    };
}
