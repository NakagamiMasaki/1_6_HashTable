/**
* @brief	ハッシュテーブル実装
* @date		2022/10/19
*/

//===== インクルード =====
#include "HashTable.h"

//===== 関数定義 =====

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
HashTable<KeyType, DataType, HashFunc, BucketSize>::HashTable(void)
	: m_ElementCount(0)
{
}

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
HashTable<KeyType, DataType, HashFunc, BucketSize>::~HashTable(void)
{
}

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
size_t HashTable<KeyType, DataType, HashFunc, BucketSize>::GetSize(void) const
{
	return m_ElementCount;
}

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
bool HashTable<KeyType, DataType, HashFunc, BucketSize>::Insert(const KeyType& Key, const DataType& Data)
{
	// ハッシュ値計算
	auto Hash = CalcHash(Key);

	//*** キーが重複していないかチェック
	// もし重複していたら、末尾以外のイテレータが返ってくる
	auto Itr = GetData(Hash, Key);
	if (m_List[Hash].GetConstEnd() != Itr)
	{
		return false;
	}

	// 末尾イテレータが返ってきた時は重複していないので、そのままリストのInsertに渡す
	Pair InsertData{ Key, Data };
	if (!m_List[Hash].Insert(Itr, InsertData))
	{
		// 失敗した時
		return false;
	}
	// 挿入に成功した時
	// 要素数の更新
	++m_ElementCount;

	return true;
}

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
bool HashTable<KeyType, DataType, HashFunc, BucketSize>::Delete(const KeyType& Key)
{
	// ハッシュ値計算
	auto Hash = CalcHash(Key);

	//*** データがあるかチェック
	// もしデータが無ければ、末尾のイテレータが返ってくる
	auto Itr = GetData(Hash, Key);
	if (m_List[Hash].GetConstEnd() == Itr)
	{
		return false;
	}

	// 末尾以外のイテレータが返ってきた時は、そのままリストのDeleteに渡す
	if (!m_List[Hash].Delete(Itr))
	{
		// 失敗した時
		return false;
	}

	// 要素数の更新
	--m_ElementCount;

	return true;
}

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
bool HashTable<KeyType, DataType, HashFunc, BucketSize>::Find(const KeyType& Key, DataType& Data) const
{
	// ハッシュ値計算
	auto Hash = CalcHash(Key);

	//*** データがあるかチェック
	// もしデータが無ければ、末尾のイテレータが返ってくる
	auto Itr = GetData(Hash, Key);
	if (m_List[Hash].GetConstEnd() == Itr)
	{
		return false;
	}

	// 末尾以外のイテレータが返ってきた時は、そのまま返す
	Data = (*Itr).Data;

	return true;
}

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
int32_t HashTable<KeyType, DataType, HashFunc, BucketSize>::CalcHash(const KeyType& Key) const
{
	auto Hash = HashFunc()(Key);

	// ハッシュ値がBucketSizeを超えていないかチェック
	assert(Hash <= BucketSize && "BucketSize is too small.");

	return Hash;
}

template<class KeyType, class DataType, class HashFunc, int32_t BucketSize>
typename HashTable<KeyType, DataType, HashFunc, BucketSize>::ListItr HashTable<KeyType, DataType, HashFunc, BucketSize>::GetData(int32_t Hash, const KeyType& Key) const
{
	//*** ハッシュを元にキーに紐づいたデータを探す
	auto Itr       = m_List[Hash].GetConstBegin();
	const auto End = m_List[Hash].GetConstEnd();
	for (; Itr != End; ++Itr)
	{
		const auto& Data = *Itr;
		if (Data.Key == Key)
		{
			// 見つかった
			return Itr;
		}
	}

	// 見つけられなかった
	return End;
}