
/**
 * author: caiwei
 * since: 2016-1-11
 * doc: 定义一个管理键值对<key, value>对象，键为长整型，而值为通用类型
 */
#include <stdbool.h>

#ifndef KVS_H
#define KVS_H

typedef long Key_t;
typedef void* Value_t;

typedef struct {
	Key_t key;

	size_t size;
	Value_t value; 
} Kv_t;

typedef struct {
	int count;			// 计数
	int capacity;		// 容量
	Key_t usable_key;   // 下一个可以使用的键
	Kv_t* kv[];			// 指针数组
} Kvs_t;

/**
 * 初始化一个空的指针对象池(必须传入一个)
 */
Kvs_t* init_kvs();

/**
 * 从指针对象池中查找键为key的元素; 没找到会返回NULL
 */
Kv_t* find_kv(Kvs_t* kvs, Key_t key);

/**
 * 从对象池中查找第index个元素( index <- [0, kvs -> count) ), 没找到会返回NULL
 */
Kv_t* get_kv(Kvs_t* kvs, int index);

/**
 * 更新一个对象
 */
bool update_kv(Kvs_t* kvs, Kv_t* kv);

/**
 * 添加一个新对象或者在已存在键的时候更新这个对象(kvs对象有可能会切换到新地址)
 */
Kvs_t* add_kv(Kvs_t* kvs, Kv_t* kv);

/**
 * 依据键删除指定的对象
 */
void remove_kv(Kvs_t* kvs, Key_t key);

/**
 * 创建一个键值对
 */
Kv_t* kv(Key_t key, Value_t value, size_t val_size);

/**
 * 将键值对写入到二进制文件中
 */
bool out(Kvs_t* kvs, const char* path);

/**
 * 从二进制文件中读取数据到内存中
 */
Kvs_t* in(const char* path);

#endif
