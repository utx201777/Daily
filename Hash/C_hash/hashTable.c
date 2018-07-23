#include "hashTable.h"

/*初始化HashTable*/
void htInit(htItem **ht, uint length){
    int i;
    for (i = 0; i<length; i++){
        ht[i] = (htItem*)malloc(sizeof(htItem));
        memset(ht[i], 0, sizeof(htItem));
    }
    ht[0]->fid = length;
}

/** get hashTable elements 进行对应的hash值的搜索，如果找到则返回该节点*/
htItem* htGet(char *key, htItem **ht){
    uint i = htIndex(key, ht);
    htItem *item = ht[i]->next;
    htItem *tmp = (htItem*)malloc(sizeof(htItem));
    memset(tmp, 0, sizeof(htItem));
    while (item)
    {
        if (strcmp(key, item->key_string) == 0){
            return item;
            tmp->fid = item->fid;
            tmp->key_string = item->key_string;
            return tmp;
        }
        item = item->next;
    }
    return NULL;
}

/** set hashTable element 插入新的hash值*/
uint htSet(char *key, uint fid, htItem **ht){
    uint i = htIndex(key, ht);
    htItem *item = ht[i];
    while (item->next)
    {
    //已经存在的话则直接更新值
        if (strcmp(key, item->next->key_string) == 0){
            item->next->fid = fid;
            return 0;
        }
        else{
            item = item->next;
        }
    }
    item->next = (htItem*)malloc(sizeof(htItem));
    item->next->fid = fid;
    item->next->key_string = key;
    item->next->next = NULL;
    return 0;
}

/** delete one element of hashtable  删除hash值*/
int htDel(char *key, htItem **ht){
    uint i = htIndex(key, ht);
    htItem *item = ht[i];
    while (item->next){
        if (strcmp(key, item->next->key_string) == 0){
            htItem *tmp = item->next;
            item->next = tmp->next;
            free(tmp);
            return 0;
        }
        item = item->next;
    }
    return -1;
}

/** BKDR hash function  对字符串进行散列，得到一个整数的hash值*/
uint bkdrHash(char *key)
{
    uint seed = 131;
    uint hash = 0;
    while (*key != '\n' && *key != 0)
    {
        hash = hash * seed + (*key++);
    }
    return (hash & 0x7FFFFFFF);
}

/** get the index of hash table  根据得到的hash值选择一个槽位置*/
uint htIndex(char *key, htItem **ht){
    uint hashedKey = bkdrHash(key);
    uint length = (ht[0]->fid - 1);
    return (uint)hashedKey % length + 1;
}

/** get element number in the hashtable */
uint htLen(htItem **ht){
    uint alength = ht[0]->fid;
    uint i, length = 0;
    for (i = 1; i < alength; i++){
        if (ht[i]->next) {
            length++;
        }
    }
    return length;
}

/** get capacity of hashtable */
uint htCapacity(htItem **ht)
{
    return ht[0]->fid;
}

void print_hashTable(htItem **ht)
{
    uint length = ht[0]->fid;
    uint i;
    htItem *item;
    for (i = 1; i < length; i++)
    {
        item = ht[i]->next;
        while (item)
        {
            printf("%s => %d\n", item->key_string, item->fid);
            item = item->next;
        }
    }
}