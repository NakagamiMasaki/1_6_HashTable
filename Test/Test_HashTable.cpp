/**
* @brief	�n�b�V���e�[�u�� �����e�X�g
* @date		2022/10/20
*/

//===== �C���N���[�h =====
#include "gtest/gtest.h"
#include <functional>
#include <string>
#include "../HashTable/HashTable.h"

/**
* @brief	�n�b�V���e�[�u���̎����e�X�g
*/
namespace ex06_HashTable
{

/**
* @brief 10�Ŋ������]����n�b�V���Ƃ��ĕԂ�
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
* @brief	�n�b�V���l��0~9�ɂȂ�悤�Ɋۂ߂ĕԂ�
*/
class RoundHash
{
public:

	// 0 ~ 9�ɂȂ�悤�Ɋۂ߂�
	int32_t operator()(int key)
	{
		return key < 0 ? 0 : 10 <= key ? 9 : key;
	}
};

/**
* @brief	std::hash()�Ōv�Z�����n�b�V���l��10�Ŋ������Ƃ��̗]���Ԃ�
*/
class Hash
{
public:

	// 0 ~ 9�ɂȂ�悤�Ɋۂ߂�
	int32_t operator()(int key)
	{
		return std::hash<int>()(key) % 10;
	}
};

/**
* @brief �n�b�V���e�[�u���̌^�t���e�X�g�p�N���X
*/
template<class T>
class HashTableTypedTest : public ::testing::Test
{
};

class HashTableFixture : public ::testing::Test
{
	//=== �����o�ϐ�
protected:

	// �f�[�^��3�������Ă���n�b�V���e�[�u��
	// KeyType  : int
	// DataType : std::string
	// Key | Data
	//  0  | "Test0"
	//  1  | "Test1"
	//  2  | "Test2"
	HashTable<int, std::string, RemainderHash, 10> m_Table;

	//=== �����o�֐�
protected:

	void SetUp(void)
	{
		//*** �n�b�V���e�[�u���Ƀf�[�^��3���ǉ�����
		m_Table.Insert(0, "Test0");
		m_Table.Insert(1, "Test1");
		m_Table.Insert(2, "Test2");
	}

	void TearDown(void)
	{
	}

};

/**
* @brief	�n�b�V���e�[�u���̃N���X�̋����e�X�g�p�N���X
*/
template<class T>
using HashTableBehaviorTest = HashTableTypedTest<T>;

typedef ::testing::Types<RemainderHash, RoundHash, Hash> HashFuncs;
TYPED_TEST_CASE(HashTableBehaviorTest, HashFuncs);

#pragma region ***** �N���X�̋��� *****

/**
* @brief	�Z�o���@�̈قȂ�K�؂ȃn�b�V���֐���n�����Ƃ��̂��ꂼ��̋���
* @details	ID:1
*			�Z�o���@���قȂ�n�b�V���֐��𗘗p���鎞�A�}���A�����A�폜������ɓ��삷�邱�Ƃ��m�F���܂�
*			�}���A�����A�폜��true���Ԃ�ΐ����ł��B
*/
TYPED_TEST(HashTableBehaviorTest, HashFunction)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, TypeParam, 10> Table;

	//*** �}�����������폜�̏��Ɏ���
	// �f�[�^�}��
	EXPECT_TRUE(Table.Insert(0, "Test0"));
	ASSERT_EQ(1, Table.GetSize());		// �v�f�����`�F�b�N

	// ����
	std::string Result;
	EXPECT_TRUE(Table.Find(0, Result));
	ASSERT_EQ(1, Table.GetSize());		// �v�f�����`�F�b�N

	// �폜
	EXPECT_TRUE(Table.Delete(0));
	ASSERT_EQ(0, Table.GetSize());		// �v�f�����`�F�b�N
}

#pragma endregion 
#pragma region ***** �f�[�^���̎擾 *****

/**
* @brief	���X�g����ł���ꍇ�̖߂�l
* @details	ID:2
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			���X�g����̎��A�f�[�^�������擾�������̋������m�F���܂��B
*			0���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, Empty)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	�v�f��}��������̖߂�l
* @details	ID:3
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f��}���������ƂɁA�f�[�^�������擾�������̋������m�F���܂��B
*			1���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, Insert)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	�v�f��}�����A���̃L�[�ō폜������̖߂�l
* @details	ID:4
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f��}���������Ƃ��̗v�f���폜���A�f�[�^�������擾�������̋������m�F���܂��B
*			0���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, InsertDelete)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// �폜
	ASSERT_TRUE(Table.Delete(0));

	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	���ɑ��݂���L�[�ŗv�f�̑}���������s������̖߂�l
* @details	ID:5
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f��}���������Ɠ����L�[�ŗv�f��}�������s�������ƂɃf�[�^�������擾�������̋������m�F���܂��B
*			1���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, InsertSecondTime)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// ����ɑ}��
	ASSERT_FALSE(Table.Insert(0, "Test0_1"));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	���X�g�ɗv�f�����鎞�ɑ��݂��Ȃ��L�[���w�肵�v�f�̍폜�Ɏ��s�����ۂ̖߂�l
* @details	ID:6
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f��}���������ƈقȂ�L�[�ŗv�f���폜�����s�������ƂɃf�[�^�������擾�������̋������m�F���܂��B
*			1���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, InsertDeleteFailed)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// �Ⴄ�L�[�ō폜
	ASSERT_FALSE(Table.Delete(1));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	���X�g����ł���ꍇ�ɁA�폜���s������̖߂�l
* @details	ID:7
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			���X�g����̎��ɍ폜���s���Ď��s�������ƂɁA�f�[�^�������擾�������̋������m�F���܂��B
*			0���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, EmptyDeleteFailed)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// ��̏�Ԃō폜
	ASSERT_FALSE(Table.Delete(0));

	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	�v�f�Q�������Ń`�F�C���ɂȂ��Ă��Ȃ����̖߂�l
* @details	ID:8
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f2���`�F�C���ɂȂ��Ă��Ȃ����ɁA�f�[�^�������擾�������̋������m�F���܂��B
*			2���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, NotChain)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �ǉ�
	ASSERT_TRUE(Table.Insert(0, "Test0"));
	ASSERT_TRUE(Table.Insert(1, "Test1"));

	EXPECT_EQ(2, Table.GetSize());
}

/**
* @brief	�v�f�Q�������Ń`�F�C���ɂȂ��Ă��Ȃ����Ɉ�����폜������̖߂�l
* @details	ID:9
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f2���`�F�C���ɂȂ��Ă��Ȃ����Ɉ�����폜���A�f�[�^�������擾�������̋������m�F���܂��B
*			1���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, NotChainDelete)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �ǉ�
	ASSERT_TRUE(Table.Insert(0, "Test0"));
	ASSERT_TRUE(Table.Insert(1, "Test1"));

	// �폜
	ASSERT_TRUE(Table.Delete(0));

	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	�v�f�Q�������Ń`�F�C���ɂȂ�����̖߂�l
* @details	ID:10
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f2���`�F�C���ɂȂ�����ɁA�f�[�^�������擾�������̋������m�F���܂��B
*			2���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, Chain)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �ǉ�
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	EXPECT_EQ(2, Table.GetSize());
}

/**
* @brief	�v�f�Q�������Ń`�F�C���ɂȂ��Ă��鎞�Ɉ�����폜������̖߂�l
* @details	ID:11
*			�f�[�^���̎擾�̋@�\�̃e�X�g�ł�
*			�v�f2���`�F�C���ɂȂ�����Ɉ�����폜���A�f�[�^�������擾�������̋������m�F���܂��B
*			1���Ԃ�ΐ����ł��B
*/
TEST(HashTableGetDataNum, ChainDelete)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �ǉ�
	ASSERT_TRUE(Table.Insert(0, "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// �폜
	ASSERT_TRUE(Table.Delete(0));

	EXPECT_EQ(2, Table.GetSize());
}

#pragma endregion
}
