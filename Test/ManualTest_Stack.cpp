/**
* @brief	スタックの手動テスト
* @date		2022/10/17
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include "../HashTable/Stack.h"
#include "ManualTest_Stack.h"

/**
* @brief	スタックの手動テスト
*/
namespace ex05_Stack
{

/**
* @brief	constのメソッドであるか
* @details	ID: スタック-7
*			データ件数の取得のテストです
*			constのスタックから呼び出して、コンパイルエラーにならないか確認します。
*			コンパイルエラーにならなければ成功です。
*/
TEST(StackGetSize, IsConst)
{
#ifdef STACK_GETSIZE_IS_CONST
	const Stack<int> stack;

	// constなスタックから呼び出してみる
	EXPECT_EQ(0, stack.GetSize());
#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID: スタック-10
*			プッシュのテストです
*			constのスタックから呼び出して、コンパイルエラーになることを確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(StackPush, NotConst)
{
#ifdef STACK_PUSH_IS_NOT_CONST
	const Stack<int> stack;

	// constなスタックから呼び出してみる
	stack.Push(0);
#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID: スタック-14
*			データ件数の取得のテストです
*			constのスタックから呼び出して、コンパイルエラーになることを確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(StackPop, NotConst)
{
#ifdef STACK_POP_IS_NOT_CONST
	const Stack<int> stack;

	// constなスタックから呼び出してみる
	int Ret = 0;
	stack.Pop(Ret);
#else
	SUCCEED();
#endif
}

}	// ex06_Stack
