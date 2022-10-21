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

//===== �N���X��` =====

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

/**
* @brief	�n�b�V���e�[�u���̃e�X�g�p�t�B�N�X�`��
*/
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

//===== �^�G�C���A�X =====

/**
* @brief	�n�b�V���e�[�u���̃N���X�̋����e�X�g�p�N���X
*/
template<class T>
using HashTableBehaviorTest = HashTableTypedTest<T>;

/**
* @brief	�n�b�V���e�[�u���e�X�g�p�t�B�N�X�`���̕ʖ�
*/
using HashTableInsertF = HashTableFixture;
using HashTableDeleteF = HashTableFixture;
using HashTableFindF   = HashTableFixture;

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

	EXPECT_EQ(1, Table.GetSize());
}

#pragma endregion
#pragma region ***** �f�[�^�̑}�� *****

/**
* @brief	���X�g����ł���ꍇ�ɁA�}�������ۂ̋���
* @details	ID:13
*			�f�[�^�̑}���̋@�\�̃e�X�g�ł�
*			���X�g����̎��Ƀf�[�^��}���������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST(HashTableInsert, Empty)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �ǉ�
	EXPECT_TRUE(Table.Insert(0, "Test0_0"));

	// �f�[�^�����������Ă��邩�`�F�b�N
	EXPECT_EQ(1, Table.GetSize());
}

/**
* @brief	���X�g�ɕ����̗v�f������ꍇ�ɁA�L�[���d�����Ȃ��ő}�������ۂ̋���
* @details	ID:14
*			�f�[�^�̑}���̋@�\�̃e�X�g�ł�
*			���X�g�ɕ����̗v�f�����鎞�ɃL�[���d�����Ȃ��悤�Ƀf�[�^��}���������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableInsertF, NotDuplicated)
{
	// �d�����Ȃ��悤�ɒǉ�
	EXPECT_TRUE(m_Table.Insert(3, "Test3"));

	// �f�[�^�����������Ă��邩�`�F�b�N
	EXPECT_EQ(4, m_Table.GetSize());
}

/**
* @brief	���X�g�ɕ����̗v�f������ꍇ�ɁA�L�[���d�����đ}�����悤�Ƃ����ۂ̋���
* @details	ID:15
*			�f�[�^�̑}���̋@�\�̃e�X�g�ł�
*			���X�g�ɕ����̗v�f�����鎞�ɃL�[���d������悤�Ƀf�[�^��}���������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableInsertF, Duplicated)
{
	// �d������悤�ɑ}��
	EXPECT_FALSE(m_Table.Insert(0, "Test0_1"));

	// �f�[�^�����������Ă��Ȃ����`�F�b�N
	EXPECT_EQ(3, m_Table.GetSize());
}

/**
* @brief	���Ƀ��X�g�ɂ���v�f�ƃn�b�V���l�������ɂȂ�L�[�ő}�������ۂ̋���
* @details	ID:16
*			�f�[�^�̑}���̋@�\�̃e�X�g�ł�
*			���X�g�ɕ����̗v�f�����鎞�Ƀn�b�V���l�������ɂȂ�L�[�Ńf�[�^��}���������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableInsertF, Synonym)
{
	// �n�b�V���l���d������悤�ɑ}��
	// �L�[�̒l��10�Ŋ������Ƃ��̗]����n�b�V���ɂ��Ă���̂�
	// 10��n����0�Ɠ����n�b�V���ɂȂ�
	EXPECT_TRUE(m_Table.Insert(10, "Test0_1"));

	// �f�[�^�����������Ă��邩�`�F�b�N
	EXPECT_EQ(4, m_Table.GetSize());
}

/**
* @brief	��x�}�����A�폜������ēx�����L�[�ő}�������ۂ̋���
* @details	ID:16
*			�f�[�^�̑}���̋@�\�̃e�X�g�ł�
*			��x�}�����A�폜������ɓ����L�[�ő}���������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST(HashTableInsert, InsertDeleteInsert)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 1��ڂ̑}��
	EXPECT_TRUE(Table.Insert(0, "Test0"));

	// �폜����
	ASSERT_TRUE(Table.Delete(0));
	ASSERT_EQ(0, Table.GetSize());			// �v�f���`�F�b�N

	// 2��ڂ̑}��
	EXPECT_TRUE(Table.Insert(0, "Test0"));
	EXPECT_EQ(1, Table.GetSize());			// �v�f���`�F�b�N
}

#pragma endregion
#pragma region ***** �f�[�^�̍폜 *****

/**
* @brief	���X�g����ł���ꍇ�ɁA�폜��������悤�Ƃ����ۂ̋���
* @details	ID:19
*			�f�[�^�̍폜�̋@�\�̃e�X�g�ł�
*			��̎��Ƀf�[�^���폜�������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST(HashTableDelete, Empty)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �폜
	EXPECT_FALSE(Table.Delete(0));

	// �v�f���`�F�b�N
	// �ςɑ����Ă��茸���Ă��肵�ĂȂ����H
	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	���X�g�ɕ����̗v�f������ꍇ�ɁA���݂���L�[�Ŏw�肵�č폜�����ۂ̋���
* @details	ID:20
*			�f�[�^�̍폜�̋@�\�̃e�X�g�ł�
*			�����̗v�f������Ƃ��ɁA���݂���L�[�Ńf�[�^���폜�������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableDeleteF, SomeDataExist)
{
	// �폜
	EXPECT_TRUE(m_Table.Delete(0));

	// �v�f���`�F�b�N
	EXPECT_EQ(2, m_Table.GetSize());
}

/**
* @brief	���X�g�ɕ����̗v�f������ꍇ�ɁA���݂��Ȃ��L�[�Ŏw�肵�č폜���悤�Ƃ����ۂ̋���
* @details	ID:21
*			�f�[�^�̍폜�̋@�\�̃e�X�g�ł�
*			�����̗v�f������Ƃ��ɁA���݂��Ȃ��L�[�Ńf�[�^���폜�������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableDeleteF, SomeDataExitNotExistKey)
{
	// �폜
	EXPECT_FALSE(m_Table.Delete(3));

	// �v�f���`�F�b�N
	EXPECT_EQ(3, m_Table.GetSize());
}

/**
* @brief	��x�폜�����L�[�ōēx�폜���悤�Ƃ����ۂ̋���
* @details	ID:22
*			�f�[�^�̍폜�̋@�\�̃e�X�g�ł�
*			��x�폜�����L�[�ł�����x�폜�������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST(HashTableDelete, DeleteScondTime)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// 1�x�폜
	ASSERT_TRUE(Table.Delete(0));
	
	// �v�f���`�F�b�N
	ASSERT_EQ(0, Table.GetSize());

	// 2��ڂ̍폜
	EXPECT_FALSE(Table.Delete(0));

	// �v�f���`�F�b�N
	EXPECT_EQ(0, Table.GetSize());
}

/**
* @brief	�`�F�C���ɂȂ��Ă���v�f������1�̃L�[���w�肵�č폜�����ۂ̋���
* @details	ID:23
*			�f�[�^�̍폜�̋@�\�̃e�X�g�ł�
*			�`�F�C���ɂȂ��Ă���v�f�̂�����1���폜�������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST(HashTableDelete, ChainElement)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// �Е����폜
	EXPECT_TRUE(Table.Delete(0));
}

/**
* @brief	�`�F�C���ɂȂ��Ă���v�f�ƃn�b�V���l�����������A���݂��Ȃ��L�[���w�肵�č폜�����ۂ̋���
* @details	ID:24
*			�f�[�^�̍폜�̋@�\�̃e�X�g�ł�
*			�`�F�C���ɂȂ��Ă���v�f�ƃn�b�V���l�����������A���݂��Ȃ��L�[�ō폜�������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST(HashTableDelete, ChainElementNotExistKey)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// ���݂��Ȃ��L�[�ō폜
	EXPECT_FALSE(Table.Delete(20));
	EXPECT_EQ(2, Table.GetSize());
}

/**
* @brief	�`�F�C���ɂȂ��Ă���v�f�����ɍ폜���Ă������ۂ̋���
* @details	ID:25
*			�f�[�^�̍폜�̋@�\�̃e�X�g�ł�
*			�`�F�C���ɂȂ��Ă���v�f�����ɍ폜�������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST(HashTableDelete, ChainElementDeleteInOrder)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// �}��
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// ���Ԃɍ폜
	EXPECT_TRUE(Table.Delete(0));
	EXPECT_TRUE(Table.Delete(10));

	// �v�f���̃`�F�b�N
	EXPECT_EQ(0, Table.GetSize());
}

#pragma endregion
#pragma region ***** �f�[�^�̌��� *****

/**
* @brief	���X�g����ł���ꍇ�ɁA�L�[���w�肵�Č��������ۂ̋���
* @details	ID:27
*			�f�[�^�̌����̋@�\�̃e�X�g�ł�
*			���X�g����̎��Ɍ����������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST(HashTableFind, Empty)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// ����
	std::string Result;
	EXPECT_FALSE(Table.Find(0, Result));
}

/**
* @brief	���X�g�ɕ����̗v�f������ꍇ�ɁA���݂���L�[�Ŏw�肵�Č��������ۂ̋���
* @details	ID:28
*			�f�[�^�̌����̋@�\�̃e�X�g�ł�
*			���X�g�ɕ����v�f���鎞�ɁA���݂���L�[�Ō����������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableFindF, SomeDataExist)
{
	// �����v�f���邱�Ƃ��m�F
	ASSERT_GT(m_Table.GetSize(), 2u);

	// ����
	std::string Result;
	EXPECT_TRUE(m_Table.Find(0, Result));
}

/**
* @brief	���X�g�ɕ����̗v�f������ꍇ�ɁA���݂��Ȃ��L�[�Ŏw�肵�Č��������ۂ̋���
* @details	ID:29
*			�f�[�^�̌����̋@�\�̃e�X�g�ł�
*			���X�g�ɕ����v�f���鎞�ɁA���݂��Ȃ��L�[�Ō����������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableFindF, NotExistKey)
{
	// �����v�f���邱�Ƃ��m�F
	ASSERT_GT(m_Table.GetSize(), 2u);

	// ����
	std::string Result;
	EXPECT_FALSE(m_Table.Find(3, Result));
}

/**
* @brief	���X�g�ɕ����̗v�f������ꍇ�ɁA�����L�[��2�A���Ō��������ۂ̋���
* @details	ID:30
*			�f�[�^�̌����̋@�\�̃e�X�g�ł�
*			���X�g�ɕ����v�f���鎞�ɁA�����L�[�Ō����������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST_F(HashTableFindF, SameKey)
{
	// �����v�f���邱�Ƃ��m�F
	ASSERT_GT(m_Table.GetSize(), 2u);

	// 1��ڂ̌���
	std::string Result;
	EXPECT_TRUE(m_Table.Find(0, Result));
	EXPECT_EQ("Test0", Result);

	// 2��ڂ̌���
	Result.clear();
	EXPECT_TRUE(m_Table.Find(0, Result));
	EXPECT_EQ("Test0", Result);

}

/**
* @brief	���ɍ폜���ꂽ�L�[�Ō��������ۂ̋���
* @details	ID:31
*			�f�[�^�̌����̋@�\�̃e�X�g�ł�
*			���ɍ폜���ꂽ�L�[�Ō����������̋������m�F���܂��B
*			false���Ԃ�ΐ����ł��B
*/
TEST(HashTableFind, DeletedKey)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 1���f�[�^��}��
	ASSERT_TRUE(Table.Insert(0, "Test0"));

	// �폜
	ASSERT_TRUE(Table.Delete(0));

	// ����
	std::string Result;
	EXPECT_FALSE(Table.Find(0, Result));
}

/**
* @brief	�`�F�C���ɂȂ��Ă���v�f�̓���1�̃L�[���w�肵�Č��������ۂ̋���
* @details	ID:32
*			�f�[�^�̌����̋@�\�̃e�X�g�ł�
*			�`�F�C���ɂȂ��Ă���v�f�̓��̈���Ō����������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST(HashTableFind, Chain)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 2���f�[�^��}��
	ASSERT_TRUE(Table.Insert(0,  "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// ����
	std::string Result;
	EXPECT_TRUE(Table.Find(0, Result));
	EXPECT_EQ("Test0_0", Result);
}

/**
* @brief	�`�F�C���ɂȂ��Ă���v�f������1�̍폜������ɁA�c���Ă���v�f�����������ۂ̋���
* @details	ID:33
*			�f�[�^�̌����̋@�\�̃e�X�g�ł�
*			�`�F�C���ɂȂ��Ă���v�f�̓��̈�����폜���A�c���Ă���v�f�������������̋������m�F���܂��B
*			true���Ԃ�ΐ����ł��B
*/
TEST(HashTableFind, DeleteChainOther)
{
	// �n�b�V���e�[�u��
	HashTable<int, std::string, RemainderHash, 10> Table;

	// 2���f�[�^��}��
	ASSERT_TRUE(Table.Insert(0, "Test0_0"));
	ASSERT_TRUE(Table.Insert(10, "Test0_1"));

	// �Е����폜
	ASSERT_TRUE(Table.Delete(0));

	// ����
	std::string Result;
	EXPECT_TRUE(Table.Find(10, Result));
	EXPECT_EQ("Test0_1", Result);
}

#pragma endregion

}
