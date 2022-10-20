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

	// 0 ~ 9�ɂȂ�悤�Ɋۂ߂�
	int32_t operator()(int key)
	{
		return key < 0 ? 0 : 10 <= key ? 9 : key;
	}
};

class Hash
{
public:

	// 0 ~ 9�ɂȂ�悤�Ɋۂ߂�
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
* @brief	�Z�o���@�̈قȂ�K�؂ȃn�b�V���֐���n�����Ƃ��̂��ꂼ��̋���
* @details	ID:1
*			�Z�o���@���قȂ�n�b�V���֐��𗘗p���鎞�A�}���A�����A�폜������ɓ��삷�邱�Ƃ��m�F���܂�
*			�}���A�����A�폜��true���Ԃ�ΐ����ł��B
*/
TYPED_TEST(HashTableTest, HashFunction)
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

}
