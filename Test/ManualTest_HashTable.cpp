/**
* @brief	ハッシュテーブル 手動テスト
* @date		2022/10/20
*/

//===== インクルード =====
#include "gtest/gtest.h"
#include <functional>
#include <string>
#include "../HashTable/HashTable.h"
#include "ManualTest_HashTable.h"

/**
* @brief	ハッシュテーブルのテスト
*/
namespace ex06_HashTable
{

/**
* @brief	不適切なハッシュ関数
*			引数 int&&, 戻り値 float なのでともに互換性がない
*/
class InvalidHashFunc
{
public:

	/**
	* @brief	不適切なハッシュ関数
	*/
	float operator()(int&& key)
	{
		return static_cast<float>(key % 10);
	}
};

/**
* @brief	int型のキーをとるハッシュテーブル用のハッシュ関数
*/
class HashFunc
{
public:

	/**
	* @brief	int型のキーをとるハッシュテーブル用の関数
	*/
	int32_t operator()(int key)
	{
		return key % 10;
	}
};

/**
* @brief	不適切なハッシュ関数がテンプレート引数で渡された時
* @details	ID:0
*			不適切なハッシュ関数を渡したときのクラスの挙動を確認します。
*			コンパイルエラーとなれば成功です。
*/
TEST(HashTableBehaviorTest, InvalidHashFunction)
{
#ifdef HASH_TABLE_INVALID_HASH_FUNC

	// 引数型、戻り値の型ともに適合しない型のハッシュ関数を渡す
	// (引数 int&&, 戻り値 float)
	HashTable<int, float, InvalidHashFunc, 10> Table;

#else
	SUCCEED();
#endif
}

/**
* @brief	constのメソッドであるか
* @details	ID:12
*			データ数の取得の機能のテストです
*			constなハッシュテーブルから呼び出してコンパイルエラーにならないか確認します。
*			コンパイルエラーにならなければ成功です。
*/
TEST(HashTableGetDataNum, IsConst)
{
#ifdef HASH_TABLE_GETSIZE_IS_CONST

	// cosntなハッシュテーブル
	const HashTable<int, float, HashFunc, 10> Table;

	// constなハッシュテーブルから呼び出す
	Table.GetSize();

#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID:18
*			データの挿入の機能のテストです
*			constなハッシュテーブルから呼び出してコンパイルエラーになるか確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(HashTableInsert, IsNotConst)
{
#ifdef HASH_TABLE_INSERT_IS_NOT_CONST

	// cosntなハッシュテーブル
	const HashTable<int, float, HashFunc, 10> Table;

	// constなハッシュテーブルから呼び出す
	Table.Insert(0, 0.0f);

#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID:18
*			データの挿入の機能のテストです
*			constなハッシュテーブルから呼び出してコンパイルエラーになるか確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(HashTableInsert, IsNotConst)
{
#ifdef HASH_TABLE_INSERT_IS_NOT_CONST

	// cosntなハッシュテーブル
	const HashTable<int, float, HashFunc, 10> Table;

	// constなハッシュテーブルから呼び出す
	Table.Insert(0, 0.0f);

#else
	SUCCEED();
#endif
}

/**
* @brief	非constのメソッドであるか
* @details	ID:26
*			データの削除の機能のテストです
*			constなハッシュテーブルから呼び出してコンパイルエラーになるか確認します。
*			コンパイルエラーになれば成功です。
*/
TEST(HashTableDelete, IsNotConst)
{
#ifdef HASH_TABLE_DELETE_IS_NOT_CONST

	// cosntなハッシュテーブル
	const HashTable<int, float, HashFunc, 10> Table;

	// constなハッシュテーブルから呼び出す
	Table.Delete(0);

#else
	SUCCEED();
#endif
}

/**
* @brief	constのメソッドであるか
* @details	ID:34
*			データの検索の機能のテストです
*			constなハッシュテーブルから呼び出してコンパイルエラーにならないか確認します。
*			コンパイルエラーにならなければ成功です。
*/
TEST(HashTableFind, IsConst)
{
#ifdef HASH_TABLE_FIND_IS_CONST

	// cosntなハッシュテーブル
	const HashTable<int, float, HashFunc, 10> Table;

	// constなハッシュテーブルから呼び出す
	float Result;
	Table.Find(0, Result);

#else
	SUCCEED();
#endif
}

}	// ex06_HashTable