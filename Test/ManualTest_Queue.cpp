/**
* @brief	キューの手動テスト
* @date		2022/10/18
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include "../HashTable/Queue.h"
#include "ManualTest_Queue.h"

/**
* @brief	キューの手動テスト
*/
namespace ex05_Queue
{

/**
* @brief	constのメソッドであるか
* @details	ID: キュー-7
*			データ件数の取得のテストです
*			constのキューから呼び出して、コンパイルエラーにならないか確認します。
*			コンパイルエラーにならなければ成功です。
*/
TEST(StackGetSize, IsConst)
{
#ifdef QUEUE_GETSIZE_IS_CONST
	const Queue<int> queue;

	// constなキューから呼び出してみる
	EXPECT_EQ(0, queue.GetSize());
#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID: キュー-10
*			プッシュのテストです
*			constのキューから呼び出して、コンパイルエラーになることを確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(StackPush, NotConst)
{
#ifdef QUEUE_PUSH_IS_NOT_CONST
	const Queue<int> queue;

	// constなキューから呼び出してみる
	queue.Push(0);
#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID: キュー-14
*			データ件数の取得のテストです
*			constのキューから呼び出して、コンパイルエラーになることを確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(StackPop, NotConst)
{
#ifdef QUEUE_POP_IS_NOT_CONST
	const Queue<int> queue;

	// constなキューから呼び出してみる
	int Ret = 0;
	queue.Pop(Ret);
#else
	SUCCEED();
#endif
}

}	// ex06_Stack
