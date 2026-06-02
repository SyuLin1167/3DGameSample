module;
#include <DxLib.h>

export module Object.GameObject;

import <string>;

/// <summary>
/// オブジェクト関連
/// </summary>
export namespace object
{
    /// <summary>
    /// オブジェクトのタグ
    /// </summary>
    export enum class ObjectTag
    {
        None,
        Player,
        Enemy,
        Stage,
    };

    /// <summary>
    /// ゲームオブジェクトの基底クラス
    /// </summary>
    export class GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        GameObject();

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~GameObject() = default;

        /// <summary>
        /// 初期化処理
        /// </summary>
        virtual void Initialize() = 0;

        /// <summary>
        /// 更新処理
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// 描画処理
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// 位置を設定
        /// </summary>
        /// <param name="pos">位置</param>
        void SetPosition(const VECTOR& pos) { m_position = pos; }

        /// <summary>
        /// 回転を設定
        /// </summary>
        /// <param name="rot">回転(ラジアン)</param>
        void SetRotation(const VECTOR& rot) { m_rotation = rot; }

        /// <summary>
        /// スケールを設定
        /// </summary>
        /// <param name="scale">スケール</param>
        void SetScale(const VECTOR& scale) { m_scale = scale; }

        /// <summary>
        /// タグを設定
        /// </summary>
        /// <param name="tag">タグ</param>
        void SetTag(ObjectTag tag) { m_tag = tag; }

        /// <summary>
        /// 位置を取得
        /// </summary>
        /// <returns>位置</returns>
        VECTOR GetPosition() const { return m_position; }

        /// <summary>
        /// 回転を取得
        /// </summary>
        /// <returns>回転(ラジアン)</returns>
        VECTOR GetRotation() const { return m_rotation; }

        /// <summary>
        /// スケールを取得
        /// </summary>
        /// <returns>スケール</returns>
        VECTOR GetScale() const { return m_scale; }

        /// <summary>
        /// タグを取得
        /// </summary>
        /// <returns>タグ</returns>
        ObjectTag GetTag() const { return m_tag; }

        /// <summary>
        /// アクティブかどうかを取得
        /// </summary>
        /// <returns>アクティブならtrue</returns>
        bool IsActive() const { return m_isActive; }

        /// <summary>
        /// アクティブ状態を設定
        /// </summary>
        /// <param name="active">アクティブ状態</param>
        void SetActive(bool active) { m_isActive = active; }

    protected:
        VECTOR m_position;      // 位置
        VECTOR m_rotation;      // 回転(ラジアン)
        VECTOR m_scale;         // スケール
        ObjectTag m_tag;        // タグ
        bool m_isActive;        // アクティブかどうか
    };
}
