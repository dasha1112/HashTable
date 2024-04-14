#include "gtests.h"
#include "HashTable.h"
#include "HashTableNode.h"

// Тестирование конструктора
TEST(THashTable, Constructor) 
{
  THashTable<int, int> table (5);
  EXPECT_EQ(table.GetCount(), 0);
  EXPECT_EQ(table.GetSize(), 5);
}

// Тестирование метода Find
TEST(THashTableFind, ElementFound) {
  THashTable<int, int> table(10);
  int key = 5;
  int value = 10;
  table.Add(&key, &value);

  THashNode<int, int>* found = table.Find(&key);
  EXPECT_NE(found, nullptr);
}

TEST(THashTableFind, ElementNotFound) {
  THashTable<int, int> table(10);
  int key = 5;

  THashNode<int, int>* found = table.Find(&key);
  EXPECT_EQ(found, nullptr);
}

// Тестирование метода Add
TEST(THashTableAdd, ElementAdded) {
  THashTable<int, int> table(10);
  int key = 5;
  int value = 10;

  table.Add(&key, &value);

  THashNode<int, int>* found = table.Find(&key);
  EXPECT_NE(found, nullptr);
}

TEST(THashTableAdd, MultipleElementsAdded) {
  THashTable<int, int> table(10);
  int key1 = 5;
  int value1 = 10;
  table.Add(&key1, &value1);

  int key2 = 15;
  int value2 = 20;
  table.Add(&key2, &value2);

  int key3 = 25;
  int value3 = 30;
  table.Add(&key3, &value3);

  THashNode<int, int>* found1 = table.Find(&key1);
  THashNode<int, int>* found2 = table.Find(&key2);
  THashNode<int, int>* found3 = table.Find(&key3);

  EXPECT_NE(found1, nullptr);
  EXPECT_NE(found2, nullptr);
  EXPECT_NE(found3, nullptr);
}

//Тестирование метода Delete
TEST(THashTableDelete, ElementFoundAndDeleted) {
  THashTable<int, int> table(10);
  int key = 5;
  int value = 10;
  table.Add(&key, &value);

  table.Delete(&key);

  THashNode<int, int>* found = table.Find(&key);
  EXPECT_EQ(found, nullptr);
}

TEST(THashTableDelete, ElementNotFound) {
  THashTable<int, int> table(10);
  int key1 = 5;
  int value1 = 10;
  table.Add(&key1, &value1);

  int key2 = 15;
  table.Delete(&key2);

  THashNode<int, int>* found = table.Find(&key1);
  EXPECT_NE(found, nullptr);

}

// Тестирование конструктора копирования 
TEST(THashTableCopyConstructor, DeepCopy) {

  THashTable<int, int> originalTable(10);
  int key1 = 5;
  int value1 = 10;
  originalTable.Add(&key1, &value1);

  THashTable<int, int> copiedTable(originalTable);

  EXPECT_EQ(originalTable.GetSize(), copiedTable.GetSize());
  EXPECT_EQ(originalTable.GetCount(), copiedTable.GetCount());

  THashNode<int, int>* found = copiedTable.Find(&key1);
  EXPECT_NE(found, nullptr);
}

TEST(THashTableCopyConstructor, MultyCopy) {

  THashTable<int, int> originalTable(10);
  int key1 = 5;
  int value1 = 10;
  originalTable.Add(&key1, &value1);
  int key2 = 7;
  int value2 = 13;
  originalTable.Add(&key2, &value2);

  THashTable<int, int> copiedTable(originalTable);

  EXPECT_EQ(originalTable.GetSize(), copiedTable.GetSize());
  EXPECT_EQ(originalTable.GetCount(), copiedTable.GetCount());

  THashNode<int, int>* found1 = copiedTable.Find(&key1);
  THashNode<int, int>* found2 = copiedTable.Find(&key2);
  EXPECT_NE(found1, nullptr);
  EXPECT_NE(found2, nullptr);
}

// Тестирование оператора []
TEST(THashTableOperator, AccessExistingElement) {
  THashTable<int, std::string> table(10);
  int key = 5;
  std::string value = "TestValue";

  table.Add(&key, &value);

  THashNode<int, std::string>& node = table[&key];

  EXPECT_EQ(*node.GetValue(), value);
}

TEST(THashTableOperator, AddNewElementForNonExistingKey) {
  THashTable<int, std::string> table(10);
  int key = 5;

  THashNode<int, std::string>& newNode = table[&key];

  EXPECT_EQ(*newNode.GetKey(), key);
  EXPECT_EQ(*newNode.GetValue(), "");
}