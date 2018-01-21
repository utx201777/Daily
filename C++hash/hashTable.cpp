#include "hashTable.h"

HashTable::HashTable(int tSize)
{
	tableSize = tSize;
	ht.resize(tSize);
	std::for_each(ht.begin(), ht.end(), [](htItem* &r){r = new htItem(); });
}

HashTable::~HashTable()
{

	for (int i = 0; i < tableSize; ++i)
	{
		htItem * tmp = ht[i];
		htItem * next = tmp->next;
		while (tmp)
		{
			delete tmp;
			tmp = next;
			if (tmp == nullptr)
				break;
			next = next->next;
		}		
	}
}

uint HashTable::htCapacity()
{
	return tableSize;
}

uint HashTable::bkdrHash(std::string key)
{
	uint seed = 131;
	uint hash = 0;
	uint idx = 0;
	char k = key[idx];
	while (k != '\n' && k != 0)
	{
		hash = hash * seed + k;
		k = key[++idx];
	}
	return (hash & 0x7FFFFFFF);
}

uint HashTable::htIndex(std::string key){
	uint hashedKey = bkdrHash(key);	
	return (uint)hashedKey % this->tableSize;
}

bool HashTable::htSet(std::string key, uint fid){
	uint i = htIndex(key);	
	htItem *item = ht[i];	
	while (item->next)
	{
		//已经存在的话则直接更新值
		if (key == item->next->key_string){
			item->next->fid = fid;
			return true;
		}
		else{
			item = item->next;
		}
	}
	item->next = new htItem();
	item->next->fid = fid;
	item->next->key_string = key;
	item->next->next = nullptr;
	return true;
}

htItem* HashTable::htGet(std::string key){
    uint i = htIndex(key);
	
    htItem *item = ht[i]->next;
    while (item)
    {
        if (key == item->key_string){
            return item;            
        }
        item = item->next;
    }
    return nullptr;
}

bool HashTable::htDel(std::string key){
    uint i = htIndex(key);
	
    htItem *item = ht[i];
    while (item->next){
		// 找到，删除节点
        if (key == item->next->key_string){
            htItem *tmp = item->next;
            item->next = tmp->next;
			delete tmp;
            return true;
        }
        item = item->next;
    }
    return false;
}

void HashTable::printHashTable()
{
    htItem *item;
	for (uint i = 0; i < tableSize; i++)
    {
        item = ht[i]->next;
		std::cout << i << ":\n";
        while (item)
        {            
			std::cout << item->key_string << " => " << item->fid << std::endl;
            item = item->next;
        }		
    }
}

/*
HashTable ht(4);
ht.htSet("abc", 1);
ht.htSet("asbc", 2);
ht.htSet("abdc", 3);
ht.htSet("abfc", 4);
ht.htSet("asbc", 5);
ht.printHashTable();
*/