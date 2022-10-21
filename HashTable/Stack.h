/**
* @brief	スタッククラス 定義
* @date		2022/10/17
*/

#pragma once

//===== インクルード =====
#include "LinkedList.h"

//===== クラス定義 =====
/**
* @brief	スタック
* @tparam	DataType 格納したいデータ
*/
template<class DataType>
class Stack
{
	//=== メンバ変数
private:

	//! スタック用の双方向リスト
	LinkedList<DataType> m_List;

	//=== メンバ関数
public:

	/**
	* @brief	デフォルトコンストラクタ
	*/
	Stack(void);

	/**
	* @brief	コピーコンストラクタ
	* @note		意図しないコピーを防ぐため、delete宣言しています。
	*/
	Stack(const Stack<DataType>&) = delete;

	/**
	* @brief	ムーブコンストラクタ
	* @note		意図しないムーブを防ぐため、delete宣言しています。
	*/
	Stack(Stack<DataType>&&) = delete;

	/**
	* @brief	デストラクタ
	*/
	virtual ~Stack(void);

	/**
	* @brief	データ件数を取得します
	* @return	データ件数
	*/
	size_t GetSize(void) const;

	/**
	* @brief		データを末尾に追加します
	* @param[in]	Data	追加したいデータ
	* @retval		true	成功
	* @retval		false	失敗
	*/
	bool Push(const DataType& Data);

	/**
	* @brief		データをスタック末尾から取得し、取得したデータをスタックから削除します
	* @param[out]	Data	取得したデータの格納先
	* @retval		true	成功
	* @retval		false	失敗
	*/
	bool Pop(DataType& Data);
};

//===== インクルード =====
#include "Stack.inl"
