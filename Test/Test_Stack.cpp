/**
* @brief	スタックのテスト
* @date		2022/10/17
*/

#include "gtest/gtest.h"
#include "../HashTable/Stack.h"

//===== 名前空間 =====
/**
* @brief	スタックの自動テスト
*/
namespace ex05_Stack
{

//===== クラス定義 =====
/**
* @brief	スタックのテスト用フィクスチャ
*			はじめから3件データが追加されたキューをメンバに持つ
*/
class StackFixture : public ::testing::Test
{
protected:

	// データが3件入っているスタック
	// 前から順に0, 1, 2と入る
	// なのでポップすると2, 1, 0と出てくる
	Stack<int> m_Stack;	

protected:

	void SetUp(void)
	{
		// データを追加
		m_Stack.Push(0);
		m_Stack.Push(1);
		m_Stack.Push(2);
	}

	void TearDown(void)
	{
	}
};

//===== 型エイリアス ======
using StackPushF = StackFixture;
using StackPopF  = StackFixture;

#pragma region ***** データ数の取得 *****

/**
* @brief	リストが空である場合の戻り値
* @details	ID: スタック-0
*			データ件数の取得のテストです
*			リストが空の時に呼び出した時の挙動をチェックします
*			0が返れば成功です
*/
TEST(StackGetSize, NoItem)
{
	Stack<int> stack;

	// 挙動チェック
	EXPECT_EQ(0, stack.GetSize());
}

/**
* @brief	要素をプッシュした後の戻り値
* @details	ID: スタック-1
*			データ件数の取得のテストです
*			要素をプッシュしたあとに呼び出した時の挙動をチェックします
*			1が返れば成功です
*/
TEST(StackGetSize, OneItemExist)
{
	Stack<int> stack;

	// データを1件追加する
	ASSERT_TRUE(stack.Push(0));

	// 挙動チェック
	EXPECT_EQ(1, stack.GetSize());
}

/**
* @brief	要素をポップした後の戻り値
* @details	ID: スタック-2
*			データ件数の取得のテストです
*			要素をポップしたあとに呼び出した時の挙動をチェックします
*			0が返れば成功です
*/
TEST(StackGetSize, AfterPop)
{
	Stack<int> stack;

	// プッシュする
	ASSERT_TRUE(stack.Push(0));

	// ポップする
	int Ret = 0;
	ASSERT_TRUE(stack.Pop(Ret));

	// 挙動チェック
	EXPECT_EQ(0, stack.GetSize());
}

/**
* @brief	要素のプッシュに失敗した後の戻り値
* @details	ID: スタック-3
*			データ件数の取得のテストです
*			要素のプッシュに失敗したあとに呼び出した時の挙動をチェックします
*			0が返れば成功です
*/
TEST(StackGetSize, AfterPushFailed)
{
	//*** プッシュに失敗するのはメモリ割り当てに失敗した時なので、スキップ
#if 1
	SUCCEED();
#else
	Stack<int> stack;

	// プッシュする
	ASSERT_FALSE(stack.Push(0));

	// 挙動チェック
	EXPECT_EQ(0, stack.GetSize());
#endif
}

/**
* @brief	プッシュを2回行った後の戻り値
* @details	ID: スタック-4
*			データ件数の取得のテストです
*			プッシュを2回行ったあとに呼び出した時の挙動をチェックします
*			2が返れば成功です
*/
TEST(StackGetSize, AfterPushSecondTime)
{
	Stack<int> stack;

	// 2回プッシュする
	ASSERT_TRUE(stack.Push(0));
	ASSERT_TRUE(stack.Push(1));

	// 挙動チェック
	EXPECT_EQ(2, stack.GetSize());
}

/**
* @brief	プッシュを2回行った後、１回ポップした後の戻り値
* @details	ID: スタック-5
*			データ件数の取得のテストです
*			プッシュを2回行ったあと、1回ポップした後に呼び出した時の挙動をチェックします
*			1が返れば成功です
*/
TEST(StackGetSize, AfterPushSecondPop)
{
	Stack<int> stack;

	// 2回プッシュする
	ASSERT_TRUE(stack.Push(0));
	ASSERT_TRUE(stack.Push(1));

	// 1回ポップする
	int Ret = 0;
	ASSERT_TRUE(stack.Pop(Ret));

	// 挙動チェック
	EXPECT_EQ(1, stack.GetSize());
}

/**
* @brief	リストが空である場合に、ポップを行った後の戻り値
* @details	ID: スタック-6
*			データ件数の取得のテストです
*			リストが空の時に、ポップを行った後に呼び出した時の挙動をチェックします
*			1が返れば成功です
*/
TEST(StackGetSize, PopEmptyStack)
{
	Stack<int> stack;

	// 1回ポップする
	// 空なので失敗する
	int Ret = 0;
	ASSERT_FALSE(stack.Pop(Ret));

	// 挙動チェック
	EXPECT_EQ(0, stack.GetSize());
}

#pragma endregion
#pragma region ***** プッシュ *****

/**
* @brief	リストが空である場合に、プッシュした際の挙動
* @details	ID: スタック-8
*			プッシュのテストです
*			リストが空の時に、プッシュを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST(StackPush, Empty)
{
	Stack<int> stack;

	// 挙動チェック
	EXPECT_TRUE(stack.Push(0));

	// 末尾に追加されているこをチェック
	// StackのPop()は末尾から取り出すので
	// Popして確認してみる
	// ポップする
	int Ret = -1;					// Popして得られる値が0のはずなので-1で初期化する
	ASSERT_TRUE(stack.Pop(Ret));
	
	EXPECT_EQ(0, Ret);				// 得られたデータを確認する
}

/**
* @brief	リストに複数の要素がある場合に、プッシュした際の挙動
* @details	ID: スタック-9
*			プッシュのテストです
*			リストに複数の要素がある時に、プッシュを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST_F(StackPushF, SomeDataExist)
{
	// 挙動チェック
	EXPECT_TRUE(m_Stack.Push(3));

	// 末尾に追加されていることをチェック
	// StackのPop()は末尾から取り出すので
	// Popして確認してみる
	// ポップする
	int Ret = -1;					// Popして得られる値が3のはずなので-1で初期化する
	ASSERT_TRUE(m_Stack.Pop(Ret));
	
	EXPECT_EQ(3, Ret);				// 得られたデータを確認する
}

#pragma endregion
#pragma region ***** ポップ *****

/**
* @brief	リストが空である場合に、ポップした際の挙動
* @details	ID: スタック-11
*			ポップのテストです
*			リストが空の時に、ポップを行った時の挙動をチェックします
*			falseが返れば成功です
*/
TEST(StackPop, Empty)
{
	Stack<int> stack;

	// ポップする
	int Ret = 0;
	EXPECT_FALSE(stack.Pop(Ret));

	// 要素数に変化がないことを確認する
	EXPECT_EQ(0, stack.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、ポップした際の挙動
* @details	ID: スタック-12
*			ポップのテストです
*			リストに複数の要素がある時に、ポップを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST_F(StackPopF, SomeItemExist)
{

	// データが3件あることを確認する
	ASSERT_EQ(3, m_Stack.GetSize());

	// ポップする
	int Ret = 0;
	EXPECT_TRUE(m_Stack.Pop(Ret));

	// 末尾(2)が得られていることを確認する
	EXPECT_EQ(2, Ret);

	// データが2件になっていることを確認する
	EXPECT_EQ(2, m_Stack.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、ポップした際の挙動
* @details	ID: スタック-13
*			ポップのテストです
*			リストに複数の要素がある時に、ポップを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST_F(StackPopF, Pop)
{
	// データが3件あることを確認する
	ASSERT_EQ(3, m_Stack.GetSize());

	int TestData[3] = { 2, 1, 0 };

	// ポップする
	for (int i = 0; i < 3; ++i)
	{
		int Ret = -1;
		EXPECT_TRUE(m_Stack.Pop(Ret));
		EXPECT_EQ(TestData[i], Ret);
	}

	// データが0件になっていることを確認する
	EXPECT_EQ(0, m_Stack.GetSize());
}

#pragma endregion

}	// ex05_Stack
