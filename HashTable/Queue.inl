/**
* @brief	キュークラス 実装
* @date		2022/10/17
*/

//===== インクルード =====
#include "Queue.h"

//===== 関数定義 =====

template<class DataType>
Queue<DataType>::Queue(void)
{
}

template<class DataType>
Queue<DataType>::~Queue(void)
{
}

template<class DataType>
size_t Queue<DataType>::GetSize(void) const
{
	return m_List.GetSize();
}

template<class DataType>
bool Queue<DataType>::Push(const DataType& Data)
{
	//*** 末尾イテレータを取得してデータを挿入
	auto Itr = m_List.GetConstEnd();
	return m_List.Insert(Itr, Data);
}

template<class DataType>
bool Queue<DataType>::Pop(DataType& Data)
{
	// 要素数のチェック
	// もし要素数が0ならイテレータからデータを読み取れない
	if (GetSize() == 0)
	{
		return false;
	}

	//*** 先頭イテレータを取得してデータをコピー
	auto Itr = m_List.GetConstBegin();
	Data = *Itr;

	// 削除
	return m_List.Delete(Itr);
}