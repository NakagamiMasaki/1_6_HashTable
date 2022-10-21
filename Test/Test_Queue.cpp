/**
* @brief	キューのテスト
* @date		2022/10/18
*/

#include "gtest/gtest.h"
#include "../HashTable/Queue.h"

//===== 名前空間 =====
/**
* @brief	スタックの自動テスト
*/
namespace ex05_Queue
{

//===== クラス定義 =====
/**
* @brief	キューのテスト用フィクスチャ
*			はじめから3件データが追加されたキューをメンバに持つ
*/
class QueueFixture : public ::testing::Test
{
protected:

	// データが3件入っているスタック
	// 前から順に0, 1, 2と入る
	// なのでポップすると0, 1, 2と出てくる
	Queue<int> m_Queue;

protected:

	void SetUp(void)
	{
		// データを追加
		m_Queue.Push(0);
		m_Queue.Push(1);
		m_Queue.Push(2);
	}

	void TearDown(void)
	{
	}
};

//===== 型エイリアス =====
using QueuePushF = QueueFixture;
using QueuePopF  = QueueFixture;

#pragma region ***** データ数の取得 *****

/**
* @brief	リストが空である場合の戻り値
* @details	ID: キュー-0
*			データ件数の取得のテストです
*			リストが空の時に呼び出した時の挙動をチェックします
*			0が返れば成功です
*/
TEST(QueueGetSize, NoItem)
{
	Queue<int> queue;

	// 挙動チェック
	EXPECT_EQ(0, queue.GetSize());
}

/**
* @brief	要素をプッシュした後の戻り値
* @details	ID: キュー-1
*			データ件数の取得のテストです
*			要素をプッシュしたあとに呼び出した時の挙動をチェックします
*			1が返れば成功です
*/
TEST(QueueGetSize, OneItemExist)
{
	Queue<int> queue;

	// データを1件追加する
	ASSERT_TRUE(queue.Push(0));

	// 挙動チェック
	EXPECT_EQ(1, queue.GetSize());
}

/**
* @brief	要素をポップした後の戻り値
* @details	ID:キュー-2
*			データ件数の取得のテストです
*			要素をポップしたあとに呼び出した時の挙動をチェックします
*			0が返れば成功です
*/
TEST(QueueGetSize, AfterPop)
{
	Queue<int> queue;

	// プッシュする
	ASSERT_TRUE(queue.Push(0));

	// ポップする
	int Ret = 0;
	ASSERT_TRUE(queue.Pop(Ret));

	// 挙動チェック
	EXPECT_EQ(0, queue.GetSize());
}

/**
* @brief	要素のプッシュに失敗した後の戻り値
* @details	ID: キュー-3
*			データ件数の取得のテストです
*			要素のプッシュに失敗したあとに呼び出した時の挙動をチェックします
*			0が返れば成功です
*/
TEST(QueueGetSize, AfterPushFailed)
{
	//*** プッシュに失敗するのはメモリ割り当てに失敗した時なので、スキップ
#if 1
	SUCCEED();
#else
	Queue<int> queue;

	// プッシュする
	ASSERT_FALSE(queue.Push(0));

	// 挙動チェック
	EXPECT_EQ(0, queue.GetSize());
#endif
}

/**
* @brief	プッシュを2回行った後の戻り値
* @details	ID: キュー-4
*			データ件数の取得のテストです
*			プッシュを2回行ったあとに呼び出した時の挙動をチェックします
*			2が返れば成功です
*/
TEST(QueueGetSize, AfterPushSecondTime)
{
	Queue<int> queue;

	// 2回プッシュする
	ASSERT_TRUE(queue.Push(0));
	ASSERT_TRUE(queue.Push(1));

	// 挙動チェック
	EXPECT_EQ(2, queue.GetSize());
}

/**
* @brief	プッシュを2回行った後、１回ポップした後の戻り値
* @details	ID: キュー-5
*			データ件数の取得のテストです
*			プッシュを2回行ったあと、1回ポップした後に呼び出した時の挙動をチェックします
*			1が返れば成功です
*/
TEST(QueueGetSize, AfterPushSecondPop)
{
	Queue<int> queue;

	// 2回プッシュする
	ASSERT_TRUE(queue.Push(0));
	ASSERT_TRUE(queue.Push(1));

	// 1回ポップする
	int Ret = 0;
	ASSERT_TRUE(queue.Pop(Ret));

	// 挙動チェック
	EXPECT_EQ(1, queue.GetSize());
}

/**
* @brief	リストが空である場合に、ポップを行った後の戻り値
* @details	ID: キュー-6
*			データ件数の取得のテストです
*			リストが空の時に、ポップを行った後に呼び出した時の挙動をチェックします
*			1が返れば成功です
*/
TEST(QueueGetSize, PopEmptyStack)
{
	Queue<int> queue;

	// 1回ポップする
	// 空なので失敗する
	int Ret = 0;
	ASSERT_FALSE(queue.Pop(Ret));

	// 挙動チェック
	EXPECT_EQ(0, queue.GetSize());
}

#pragma endregion
#pragma region ***** プッシュ *****

/**
* @brief	リストが空である場合に、プッシュした際の挙動
* @details	ID: キュー-8
*			プッシュのテストです
*			リストが空の時に、プッシュを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST(QueuePush, Empty)
{
	Queue<int> queue;

	// 挙動チェック
	EXPECT_TRUE(queue.Push(0));

	// 末尾に追加されているこをチェック
	// キューのPop()は先頭から取り出すので
	// Popして確認してみる
	// ポップする
	int Ret = -1;					// Popして得られる値が0のはずなので-1で初期化する
	ASSERT_TRUE(queue.Pop(Ret));

	EXPECT_EQ(0, Ret);				// 得られたデータを確認する
}

/**
* @brief	リストに複数の要素がある場合に、プッシュした際の挙動
* @details	ID: キュー-9
*			プッシュのテストです
*			リストに複数の要素がある時に、プッシュを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST_F(QueuePushF, SomeDataExist)
{
	// 挙動チェック
	EXPECT_TRUE(m_Queue.Push(3));

	// 末尾に追加されていることをチェック
	// キューのPop()は先頭から取り出すので
	// 4回Popして確認してみる
	// ポップする
	int Ret = -1;					// Popして得られる値がどれも0以上なので-1で初期化する
	for (int i = 0; i < 4; ++i)
	{
		ASSERT_TRUE(m_Queue.Pop(Ret));
	}

	EXPECT_EQ(3, Ret);				// 得られたデータを確認する
}

#pragma endregion
#pragma region ***** ポップ *****

/**
* @brief	リストが空である場合に、ポップした際の挙動
* @details	ID: キュー-11
*			ポップのテストです
*			リストが空の時に、ポップを行った時の挙動をチェックします
*			falseが返れば成功です
*/
TEST(QueuePop, Empty)
{
	Queue<int> queue;

	// ポップする
	int Ret = 0;
	EXPECT_FALSE(queue.Pop(Ret));

	// 要素数に変化がないことを確認する
	EXPECT_EQ(0, queue.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、ポップした際の挙動
* @details	ID: キュー-12
*			ポップのテストです
*			リストに複数の要素がある時に、ポップを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST_F(QueuePopF, SomeItemExist)
{
	// データが3件あることを確認する
	ASSERT_EQ(3, m_Queue.GetSize());

	// ポップする
	int Ret = -1;
	EXPECT_TRUE(m_Queue.Pop(Ret));

	// 先頭(0)が得られていることを確認する
	EXPECT_EQ(0, Ret);

	// データが2件になっていることを確認する
	EXPECT_EQ(2, m_Queue.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、ポップした際の挙動
* @details	ID: キュー-13
*			ポップのテストです
*			リストに複数の要素がある時に、ポップを行った時の挙動をチェックします
*			trueが返れば成功です
*/
TEST_F(QueuePopF, Pop)
{
	// データが3件あることを確認する
	ASSERT_EQ(3, m_Queue.GetSize());

	int TestData[3] = { 0, 1, 2 };

	// ポップする
	for (int i = 0; i < 3; ++i)
	{
		int Ret = -1;
		EXPECT_TRUE(m_Queue.Pop(Ret));
		EXPECT_EQ(TestData[i], Ret);
	}

	// データが0件になっていることを確認する
	EXPECT_EQ(0, m_Queue.GetSize());
}

#pragma endregion

}	// ex05_Queue