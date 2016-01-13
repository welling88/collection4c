#include <stdio.h>
#include <stdbool.h>
#include "userbase.h"

#define VALUE_BUF_SIZE 32

Kvs_t* load(const char* path) {
	return in(path);
}

bool save(Kvs_t* kvs, const char* path) {
	return out(kvs, path);
}

/**
 * 添加一条记录
 */
Kvs_t* add_record(Kvs_t* kvs, Record_t* pRecord) {
	Kv_t* kv = make_kv(pRecord -> id, pRecord, sizeof(Record_t));
	return add_kv(kvs, kv);
}

char* record_to_string(Value_t value) {
	Record_t* p = (Record_t *)value;
	char* buf = malloc(VALUE_BUF_SIZE);
	snprintf(buf, VALUE_BUF_SIZE, "%ld: \t%d \t%d\n", p -> id, p -> play_total, p -> win_total);
	return buf;
}

char* records_to_string(Kvs_t* kvs) {
	return kvs_to_string(kvs, record_to_string);
}

/**
 * 递增修改某记录的总玩
 */
void incr_record_play(Kvs_t* kvs, long id, int incr) {
	if(incr <= 0) return;

	Kv_t* kv = find_kv(kvs, (Key_t)id);
	if(kv == NULL) return;
	
	((Record_t *)kv -> value) -> play_total += incr;
}

/**
 * 递增修改某记录的总赢
 */
void incr_record_win(Kvs_t* kvs, long id, int incr) {
	if(incr <= 0) return;

	Kv_t* kv = find_kv(kvs, (Key_t)id);
	if(kv == NULL) return;
	
	((Record_t *)kv -> value) -> win_total += incr;
}

/**
 * 清理某记录的总玩和总赢
 */
void clear_record(Kvs_t* kvs, long id) {
	Kv_t* kv = find_kv(kvs, (Key_t)id);
	if(kv == NULL) return;

	((Record_t *)kv -> value) -> play_total = 0;
	((Record_t *)kv -> value) -> win_total = 0;
}

/**
 * 添加一个参数
 */
Kvs_t* add_param(Kvs_t* kvs, Param_t* pParam) {
	Kv_t* kv = make_kv(pParam -> id, pParam, sizeof(Param_t));
	return add_kv(kvs, kv);
}

char* param_to_string(Value_t value) {
	Param_t* p = (Param_t *)value;
	char* buf = malloc(VALUE_BUF_SIZE);
	snprintf(buf, VALUE_BUF_SIZE, "%ld: \t%f\n", p -> id, p -> probability);
	return buf;
}

char* params_to_string(Kvs_t* kvs) {
	return kvs_to_string(kvs, param_to_string);
}

/**
 * 修改新参数列表里某id的几率
 */
bool update_probability(Kvs_t* kvs, long id, double probability) {
	if(probability < 0 || probability > 1) return false;
	
	Kv_t* kv = find_kv(kvs, (Key_t)id);
	if(kv == NULL) return false;

	((Param_t *)kv -> value) -> probability = probability;
	return true;
}
