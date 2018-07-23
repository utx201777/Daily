#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/************************************************************************
   created: 2018/01/20
   class: HashTable
   author: linyi
   usage: 哈希表操作
************************************************************************/

using uint = unsigned int;

/** hash table element*/
struct htItem{
    htItem  *next;
    std::string key_string;
    uint fid;
	htItem() :next(nullptr), fid(0),key_string("default str") {};
};

class HashTable
{
public:
	HashTable(int tSize);
	~HashTable();
	uint htCapacity();	
	bool htSet(std::string key, uint fid);	// 插入一个hash值
	htItem* htGet(std::string key);	// 查找
	bool htDel(std::string key);	// 删除
	void printHashTable();		    // 打印
private:
	uint tableSize;	
	std::vector<htItem*> ht;
	uint bkdrHash(std::string key);	// 计算字符串hash值
	uint htIndex(std::string key);	// 计算属于哪一个槽
};

#endif