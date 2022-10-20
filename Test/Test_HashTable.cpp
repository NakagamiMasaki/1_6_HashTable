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



#pragma endregion
}
