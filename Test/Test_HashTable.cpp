/**
* @brief	ハッシュテーブル 自動テスト
* @date		2022/10/20
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include <functional>
#include <string>
#include "../HashTable/HashTable.h"

/**
* @brief	ハッシュテーブルの自動テスト
*/
namespace ex06_HashTable
{

class RemainderHash
{
public:

	int32_t operator()(int key)
	{
		return key % 10;
	}
};

class RoundHash
{
public:

	// 0 ~ 9になるように丸める
	int32_t operator()(int key)
	{
		return key < 0 ? 0 : 10 <= key ? 9 : key;
	}
};

class Hash
{
public:

	// 0 ~ 9になるように丸める
	int32_t operator()(int key)
	{
		return std::hash<int>()(key) % 10;
	}
};

template<class T>
class HashTableTest : public ::testing::Test
{

};

typedef ::testing::Types<RemainderHash, RoundHash, Hash> HashFuncs;
TYPED_TEST_CASE(HashTableTest, HashFuncs);

/**
* @brief	算出方法の異なる適切なハッシュ関数を渡したときのそれぞれの挙動
* @details	ID:1
*			算出方法が異なるハッシュ関数を利用する時、挿入、検索、削除が正常に動作することを確認します
*			挿入、検索、削除でtrueが返れば成功です。
*/
TYPED_TEST(HashTableTest, HashFunction)
{
	// ハッシュテーブル
	HashTable<int, std::string, TypeParam, 10> Table;

	//*** 挿入→検索→削除の順に試す
	// データ挿入
	EXPECT_TRUE(Table.Insert(0, "Test0"));
	ASSERT_EQ(1, Table.GetSize());		// 要素数をチェック

	// 検索
	std::string Result;
	EXPECT_TRUE(Table.Find(0, Result));
	ASSERT_EQ(1, Table.GetSize());		// 要素数をチェック

	// 削除
	EXPECT_TRUE(Table.Delete(0));
	ASSERT_EQ(0, Table.GetSize());		// 要素数をチェック
}

}
