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

//===== 定数定義 =====
static const uint32_t CRC32Table[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

//===== クラス定義 =====

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
class CRC32Hash
{
public:

	// 0 ~ 9になるように丸める
	int32_t operator()(int key)
	{
		uint32_t Hash = 0;

		Hash = 0 ^ 0xFFFFFFFF;
		Hash = ((Hash >> 8) & 0x00FFFFFF) ^ CRC32Table[(Hash ^ key) & 0xFF];
		
		return Hash;
	}
};

/**
* @brief ハッシュテーブルの型付けテスト用クラス
*/
template<class T>
class HashTableTypedTest : public ::testing::Test
{
};

/**
* @brief	ハッシュテーブルのテスト用フィクスチャ
*/
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

//===== 型エイリアス =====

/**
* @brief	ハッシュテーブルのクラスの挙動テスト用クラス
*/
template<class T>
using HashTableBehaviorTest = HashTableTypedTest<T>;

/**
* @brief	ハッシュテーブルテスト用フィクスチャの別名
*/
using HashTableInsertF = HashTableFixture;
using HashTableDeleteF = HashTableFixture;
using HashTableFindF   = HashTableFixture;

typedef ::testing::Types<RemainderHash, CRC32Hash, std::hash<int> > HashFuncs;
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

	EXPECT_EQ(1, Table.GetSize());
}

#pragma endregion
#pragma region ***** データの挿入 *****

/**
* @brief	リストが空である場合に、挿入した際の挙動
* @details	ID:13
*			データの挿入の機能のテストです
*			リストが空の時にデータを挿入した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST(HashTableInsert, Empty)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 追加
	EXPECT_TRUE(Table.Insert(0, "Test0_0"));

	// データ件数が増えているかチェック
	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、キーが重複しないで挿入した際の挙動
* @details	ID:14
*			データの挿入の機能のテストです
*			リストに複数の要素がある時にキーが重複しないようにデータを挿入した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST_F(HashTableInsertF, NotDuplicated)
{
	// 複数要素があることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// 重複しないように追加
	EXPECT_TRUE(m_Table.Insert(3, "Test3"));

	// データ件数が増えているかチェック
	EXPECT_EQ(4, m_Table.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、キーが重複して挿入しようとした際の挙動
* @details	ID:15
*			データの挿入の機能のテストです
*			リストに複数の要素がある時にキーが重複するようにデータを挿入した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST_F(HashTableInsertF, Duplicated)
{
	// 複数要素があることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// 重複するように挿入
	EXPECT_FALSE(m_Table.Insert(0, "Test0_1"));

	// データ件数が増えていないかチェック
	EXPECT_EQ(3, m_Table.GetSize());
}

/**
* @brief	既にリストにある要素とハッシュ値が同じになるキーで挿入した際の挙動
* @details	ID:16
*			データの挿入の機能のテストです
*			リストに複数の要素がある時にハッシュ値が同じになるキーでデータを挿入した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST_F(HashTableInsertF, Synonym)
{
	// 複数要素があることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// ハッシュ値が重複するように挿入
	// キーの値を10で割ったときの余りをハッシュにしているので
	// 10を渡すと0と同じハッシュになる
	EXPECT_TRUE(m_Table.Insert(10, "Test0_1"));

	// データ件数が増えているかチェック
	EXPECT_EQ(4, m_Table.GetSize());
}

/**
* @brief	一度挿入し、削除した後再度同じキーで挿入した際の挙動
* @details	ID:17
*			データの挿入の機能のテストです
*			一度挿入し、削除した後に同じキーで挿入した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST(HashTableInsert, InsertDeleteInsert)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 1回目の挿入
	EXPECT_TRUE(Table.Insert(0, "Test0"));

	// 削除する
	ASSERT_TRUE(Table.Delete(0));
	ASSERT_EQ(0, Table.GetSize());			// 要素数チェック

	// 2回目の挿入
	EXPECT_TRUE(Table.Insert(0, "Test0"));
	EXPECT_EQ(1, Table.GetSize());			// 要素数チェック
}

#pragma endregion
#pragma region ***** データの削除 *****

/**
* @brief	リストが空である場合に、削除操作をしようとした際の挙動
* @details	ID:19
*			データの削除の機能のテストです
*			空の時にデータを削除した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST(HashTableDelete, Empty)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 削除
	EXPECT_FALSE(Table.Delete(0));

	// 要素数チェック
	// 変に増えてたり減ってたりしてないか？
	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、存在するキーで指定して削除した際の挙動
* @details	ID:20
*			データの削除の機能のテストです
*			複数の要素があるときに、存在するキーでデータを削除した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST_F(HashTableDeleteF, SomeDataExist)
{
	// 複数要素があることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// 削除
	EXPECT_TRUE(m_Table.Delete(0));

	// 要素数チェック
	EXPECT_EQ(2, m_Table.GetSize());
}

/**
* @brief	リストに複数の要素がある場合に、存在しないキーで指定して削除しようとした際の挙動
* @details	ID:21
*			データの削除の機能のテストです
*			複数の要素があるときに、存在しないキーでデータを削除した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST_F(HashTableDeleteF, SomeDataExitNotExistKey)
{
	// 複数要素があることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// 削除
	EXPECT_FALSE(m_Table.Delete(3));

	// 要素数チェック
	EXPECT_EQ(3, m_Table.GetSize());
}

/**
* @brief	一度削除したキーで再度削除しようとした際の挙動
* @details	ID:22
*			データの削除の機能のテストです
*			一度削除したキーでもう一度削除した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST(HashTableDelete, DeleteScondTime)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// 1度削除
	ASSERT_TRUE(Table.Delete(0));
	
	// 要素数チェック
	ASSERT_EQ(0, Table.GetSize());

	// 2回目の削除
	EXPECT_FALSE(Table.Delete(0));

	// 要素数チェック
	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	チェインになっている要素うちの1つのキーを指定して削除した際の挙動
* @details	ID:23
*			データの削除の機能のテストです
*			チェインになっている要素のうちの1つを削除した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST(HashTableDelete, ChainElement)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// 片方を削除
	EXPECT_TRUE(Table.Delete(0));
}

/**
* @brief	チェインになっている要素とハッシュ値が同じだが、存在しないキーを指定して削除した際の挙動
* @details	ID:24
*			データの削除の機能のテストです
*			チェインになっている要素とハッシュ値が同じだが、存在しないキーで削除した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST(HashTableDelete, ChainElementNotExistKey)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// 存在しないキーで削除
	EXPECT_FALSE(Table.Delete(20));
	EXPECT_EQ(2, Table.GetSize());
}

/**
* @brief	チェインになっている要素を順に削除していった際の挙動
* @details	ID:25
*			データの削除の機能のテストです
*			チェインになっている要素を順に削除した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST(HashTableDelete, ChainElementDeleteInOrder)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 挿入
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// 順番に削除
	EXPECT_TRUE(Table.Delete(0));
	EXPECT_TRUE(Table.Delete(10));

	// 要素数のチェック
	EXPECT_EQ(0, Table.GetSize());
}

#pragma endregion
#pragma region ***** データの検索 *****

/**
* @brief	リストが空である場合に、キーを指定して検索した際の挙動
* @details	ID:27
*			データの検索の機能のテストです
*			リストが空の時に検索した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST(HashTableFind, Empty)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 検索
	std::string Result;
	EXPECT_FALSE(Table.Find(0, Result));
}

/**
* @brief	リストに複数の要素がある場合に、存在するキーで指定して検索した際の挙動
* @details	ID:28
*			データの検索の機能のテストです
*			リストに複数要素ある時に、存在するキーで検索した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST_F(HashTableFindF, SomeDataExist)
{
	// 複数要素があることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// 検索
	std::string Result;
	EXPECT_TRUE(m_Table.Find(0, Result));
}

/**
* @brief	リストに複数の要素がある場合に、存在しないキーで指定して検索した際の挙動
* @details	ID:29
*			データの検索の機能のテストです
*			リストに複数要素ある時に、存在しないキーで検索した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST_F(HashTableFindF, NotExistKey)
{
	// 複数要素あることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// 検索
	std::string Result;
	EXPECT_FALSE(m_Table.Find(3, Result));
}

/**
* @brief	リストに複数の要素がある場合に、同じキーで2連続で検索した際の挙動
* @details	ID:30
*			データの検索の機能のテストです
*			リストに複数要素ある時に、同じキーで検索した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST_F(HashTableFindF, SameKey)
{
	// 複数要素あることを確認
	ASSERT_GE(m_Table.GetSize(), 2u);

	// 1回目の検索
	std::string Result;
	EXPECT_TRUE(m_Table.Find(0, Result));
	EXPECT_EQ("Test0", Result);

	// 2回目の検索
	Result.clear();
	EXPECT_TRUE(m_Table.Find(0, Result));
	EXPECT_EQ("Test0", Result);

}

/**
* @brief	既に削除されたキーで検索した際の挙動
* @details	ID:31
*			データの検索の機能のテストです
*			既に削除されたキーで検索した時の挙動を確認します。
*			falseが返れば成功です。
*/
TEST(HashTableFind, DeletedKey)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 1件データを挿入
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// 削除
	ASSERT_TRUE(Table.Delete(0));

	// 検索
	std::string Result;
	EXPECT_FALSE(Table.Find(0, Result));
}

/**
* @brief	チェインになっている要素の内の1つのキーを指定して検索した際の挙動
* @details	ID:32
*			データの検索の機能のテストです
*			チェインになっている要素の内の一方で検索した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST(HashTableFind, Chain)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 2件データを挿入
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// 検索
	std::string Result;
	EXPECT_TRUE(Table.Find(0, Result));
	EXPECT_EQ("Test0_0", Result);
}

/**
* @brief	チェインになっている要素うちの1つの削除した後に、残っている要素を検索した際の挙動
* @details	ID:33
*			データの検索の機能のテストです
*			チェインになっている要素の内の一方を削除し、残っている要素を検索した時の挙動を確認します。
*			trueが返れば成功です。
*/
TEST(HashTableFind, DeleteChainOther)
{
	// ハッシュテーブル
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 2件データを挿入
	ASSERT_TRUE(Table.Insert(0, "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// 片方を削除
	ASSERT_TRUE(Table.Delete(0));

	// 検索
	std::string Result;
	EXPECT_TRUE(Table.Find(10, Result));
	EXPECT_EQ("Test0_1", Result);
}

#pragma endregion

}
