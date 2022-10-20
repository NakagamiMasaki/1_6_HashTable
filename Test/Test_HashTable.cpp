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

/**
* @brief 10で割った余りをハッシュとして返す
*/
class RemainderHash
{
public:

	int32_t operator()(int key)
	{
		return key % 10;
	}
};

/**
* @brief	ハッシュ値が0~9になるように丸めて返す
*/
class RoundHash
{
public:

	// 0 ~ 9になるように丸める
	int32_t operator()(int key)
	{
		return key < 0 ? 0 : 10 <= key ? 9 : key;
	}
};

/**
* @brief	std::hash()で計算したハッシュ値を10で割ったときの余りを返す
*/
class Hash
{
public:

	// 0 ~ 9になるように丸める
	int32_t operator()(int key)
	{
		return std::hash<int>()(key) % 10;
	}
};

/**
* @brief ハッシュテーブルの型付けテスト用クラス
*/
template<class T>
class HashTableTypedTest : public ::testing::Test
{
};

class HashTableFixture : public ::testing::Test
{
	//=== メンバ変数
protected:

	// データが3件入っているハッシュテーブル
	// KeyType  : int
	// DataType : std::string
	// Key | Data
	//  0  | "Test0"
	//  1  | "Test1"
	//  2  | "Test2"
	HashTable<int, std::string, RemainderHash, 10> m_Table;

	//=== メンバ関数
protected:

	void SetUp(void)
	{
		//*** ハッシュテーブルにデータを3件追加する
		m_Table.Insert(0, "Test0");
		m_Table.Insert(1, "Test1");
		m_Table.Insert(2, "Test2");
	}

	void TearDown(void)
	{
	}

};

/**
* @brief	ハッシュテーブルのクラスの挙動テスト用クラス
*/
template<class T>
using HashTableBehaviorTest = HashTableTypedTest<T>;

typedef ::testing::Types<RemainderHash, RoundHash, Hash> HashFuncs;
TYPED_TEST_CASE(HashTableBehaviorTest, HashFuncs);

#pragma region ***** クラスの挙動 *****

/**
* @brief	算出方法の異なる適切なハッシュ関数を渡したときのそれぞれの挙動
* @details	ID:1
*			算出方法が異なるハッシュ関数を利用する時、挿入、検索、削除が正常に動作することを確認します
*			挿入、検索、削除でtrueが返れば成功です。
*/
TYPED_TEST(HashTableBehaviorTest, HashFunction)
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

#pragma endregion 
#pragma region ***** データ数の取得 *****

/**
* @brief	リストが空である場合の戻り値
* @details	ID:2
*			データ数の取得の機能のテストです
*			リストが空の時、データ件数を取得した時の挙動を確認します。
*			0が返れば成功です。
*/
TEST(HashTableGetDataNum, Empty)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	要素を挿入した後の戻り値
* @details	ID:3
*			データ数の取得の機能のテストです
*			要素を挿入したあとに、データ件数を取得した時の挙動を確認します。
*			1が返れば成功です。
*/
TEST(HashTableGetDataNum, Insert)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	要素を挿入し、そのキーで削除した後の戻り値
* @details	ID:4
*			データ数の取得の機能のテストです
*			要素を挿入したあとその要素を削除し、データ件数を取得した時の挙動を確認します。
*			0が返れば成功です。
*/
TEST(HashTableGetDataNum, InsertDelete)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// 削除
	ASSERT_TRUE(Table.Delete(0));

	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	既に存在するキーで要素の挿入をし失敗した後の戻り値
* @details	ID:5
*			データ数の取得の機能のテストです
*			要素を挿入したあと同じキーで要素を挿入し失敗したあとにデータ件数を取得した時の挙動を確認します。
*			1が返れば成功です。
*/
TEST(HashTableGetDataNum, InsertSecondTime)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// さらに挿入
	ASSERT_FALSE(Table.Insert(0, "Test0_1"));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	リストに要素がある時に存在しないキーを指定し要素の削除に失敗した際の戻り値
* @details	ID:6
*			データ数の取得の機能のテストです
*			要素を挿入したあと異なるキーで要素を削除し失敗したあとにデータ件数を取得した時の挙動を確認します。
*			1が返れば成功です。
*/
TEST(HashTableGetDataNum, InsertDeleteFailed)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// 違うキーで削除
	ASSERT_FALSE(Table.Delete(1));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	リストが空である場合に、削除を行った後の戻り値
* @details	ID:7
*			データ数の取得の機能のテストです
*			リストが空の時に削除を行って失敗したあとに、データ件数を取得した時の挙動を確認します。
*			0が返れば成功です。
*/
TEST(HashTableGetDataNum, EmptyDeleteFailed)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 空の状態で削除
	ASSERT_FALSE(Table.Delete(0));

	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	要素２つが内部でチェインになっていない時の戻り値
* @details	ID:8
*			データ数の取得の機能のテストです
*			要素2つがチェインになっていない時に、データ件数を取得した時の挙動を確認します。
*			2が返れば成功です。
*/
TEST(HashTableGetDataNum, NotChain)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 追加
	ASSERT_TRUE(Table.Insert(0, "Test0"));
	ASSERT_TRUE(Table.Insert(1, "Test1"));

	EXPECT_EQ(2, Table.GetSize());
}

/**
* @brief	要素２つが内部でチェインになっていない時に一方を削除した後の戻り値
* @details	ID:9
*			データ数の取得の機能のテストです
*			要素2つがチェインになっていない時に一方を削除し、データ件数を取得した時の挙動を確認します。
*			1が返れば成功です。
*/
TEST(HashTableGetDataNum, NotChainDelete)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 追加
	ASSERT_TRUE(Table.Insert(0, "Test0"));
	ASSERT_TRUE(Table.Insert(1, "Test1"));

	// 削除
	ASSERT_TRUE(Table.Delete(0));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	要素２つが内部でチェインになった後の戻り値
* @details	ID:10
*			データ数の取得の機能のテストです
*			要素2つがチェインになった後に、データ件数を取得した時の挙動を確認します。
*			2が返れば成功です。
*/
TEST(HashTableGetDataNum, Chain)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 追加
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	EXPECT_EQ(2, Table.GetSize());
}

/**
* @brief	要素２つが内部でチェインになっている時に一方を削除した後の戻り値
* @details	ID:11
*			データ数の取得の機能のテストです
*			要素2つがチェインになった後に一方を削除し、データ件数を取得した時の挙動を確認します。
*			1が返れば成功です。
*/
TEST(HashTableGetDataNum, ChainDelete)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 追加
	ASSERT_TRUE(Table.Insert(0, "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// 削除
	ASSERT_TRUE(Table.Delete(0));

	EXPECT_EQ(2, Table.GetSize());
}

#pragma endregion
}
