
#include "kvs.h"

#ifndef USERBASE_H
#define USER_BASE_H

typedef struct {
	long id;
	int play_total;
	int win_total;
} Record_t;

typedef struct {
	long id;
	double probability;
} Param_t;

typedef struct {
	long id;
	int vip;
	long since;
} PsDescribe_t;

/**
 * 加载所有记录
 */
Kvs_t* load(const char* path);

/**
 * 保存所有记录
 */
bool save(Kvs_t* kvs, const char* path);

/**
 * 添加一条记录
 */
Kvs_t* add_record(Kvs_t* kvs, Record_t* pRecord);

/**
 * 将单条记录用字符串表述
 */
char* record_to_string(Value_t value);

/**
 * 将所有的记录都用字符串表示
 */
char* records_to_string(Kvs_t* kvs);

/**
 * 递增修改某记录的总玩
 */
void incr_record_play(Kvs_t* kvs, long id, int incr_play);

/**
 * 递增修改某记录的总赢
 */
void incr_record_win(Kvs_t* kvs, long id, int incr_win);

/**
 * 清理某记录的总玩和总赢
 */
void clear_record(Kvs_t* kvs, long id);

/**
 * 添加一个参数
 */
Kvs_t* add_param(Kvs_t* kvs, Param_t* pParam);

/**
 * 将单条记录用字符串表述
 */
char* param_to_string(Value_t value);

/**
 * 将所有的记录都用字符串表示
 */
char* params_to_string(Kvs_t* kvs);

/**
 * 修改新参数列表里某id的几率, probability <- [0, 1]
 */
bool update_probability(Kvs_t* kvs, long id, double probability);

#endif
