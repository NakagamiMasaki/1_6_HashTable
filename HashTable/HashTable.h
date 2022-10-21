/**
* @brief	ハッシュテーブル定義
* @date		2022/10/19
*/

#pragma once

//===== インクルード =====
#include <cstdint>
#include <type_traits>
#include "LinkedList.h"

//===== クラス定義 =====
/**
* @brief	ハッシュテーブル(チェイン法)
* @note		ハッシュ関数が返す値がバケットサイズを超えるとAssertが発生するので、バケットサイズは十分大きな値にしてください。
* @tparam	KeyType		キーの型
* @tparam	DataType	格納したいデータの型
* @tparam	HashFunc	ハッシュ関数(引数がKeyType または const KeyType& を1つとる(KeyType&&は許可しない)、戻り値がint32_tのもの)
* @tparam	BucketSize	バケットサイズ
*/
template<class KeyType, class DataType, class HashFunc, std::int32_t BucketSize>
class HashTable
{
	// BucketSizeが0より大きいことを確認する
	static_assert(BucketSize > 0, "BucketSize must greater than 0");

	// 関数オブジェクトHashFuncがint32_tでハッシュ値を返すか確認する
	static_assert(std::is_same<std::result_of<HashFunc(const KeyType&)>::type, std::int32_t>::value == true, 
				  "HashFunc must return hash value as int32_t");

	//=== 構造体定義
private:

	/**
	* @brief	キーとデータのペア
	*/
	struct Pair
	{
		//! キー
		KeyType		Key;

		//! データ
		DataType	Data;
	};

	//=== 型エイリアス
protected:

	//! 内部で使用するリストのイテレータの別名
	using ListItr = typename LinkedList<Pair>::ConstIterator;

	//=== メンバ変数
private:

	//! ハッシュテーブル
	LinkedList<Pair>	m_List[BucketSize];

	//! データ件数
	size_t		m_ElementCount;

	//=== メンバ関数
public:

	/**
	* @brief	デフォルトコンストラクタ
	*/
	HashTable(void);

	/**
	* @brief	コピーコンストラクタ
	*/
	HashTable(const HashTable&) = delete;

	/**
	* @brief	ムーブコンストラクタ
	*/
	HashTable(HashTable&&) = delete;

	/**
	* @brief	デストラクタ
	*/
	virtual ~HashTable(void);

	/**
	* @brief	データ件数を取得する。
	* @return	データ件数
	*/
	size_t GetSize(void) const;

	/**
	* @brief		データを挿入する
	* @note			指定したキーが既に存在していた場合、失敗となり何も起こりません
	* @param[in]	Key		キー(重複不可)
	* @param[in]	Data	格納したいデータ
	* @retval		true	成功
	* @retval		false	失敗
	*/
	bool Insert(const KeyType& Key, const DataType& Data);

	/**
	* @brief		データを削除する
	* @note			指定したキーが存在しなかった場合、失敗となり何も起こりません
	* @param[in]	Key		キー
	* @retval		true	成功
	* @retval		false	失敗
	*/
	bool Delete(const KeyType& Key);

	/**
	* @brief		データを検索して返す
	* @note			指定したキーが存在しなかった場合、失敗となり何も起こりません
	* @param[in]	Key		キー
	* @param[out]	Data	取得したデータの格納先
	* @retval		true	データがあった時
	* @retval		false	データがなかった時
	*/
	bool Find(const KeyType& Key, DataType& Data) const;

protected:

	/**
	* @brief		ハッシュ値を計算する
	* @param[in]	ハッシュ化したいキー
	* @return		ハッシュ値
	*/
	int32_t CalcHash(const KeyType& Key) const;

	/**
	* @brief		データをイテレータで取得する
	* @note			イテレータでデータを取得するので、この後に削除・コピーができる
	* @param[in]	Hash	CalcHash()で計算したハッシュ値
	* @param[in]	Key		キー
	* @retval		リストのイテレータ			Hash, Keyに該当するデータがある時
	* @retval		リストの末尾イテレータ		Hash, Keyに該当するデータがなかった時
	*/
	ListItr GetData(int32_t Hash, const KeyType& Key) const;

};

//===== インクルード =====
#include "HashTable.inl"
