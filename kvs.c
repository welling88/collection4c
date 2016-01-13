
/**
 * author: caiwei
 * since: 2016-1-11
 * doc: 定义一个管理键值对<key, value>对象，键必须为长整型，而值为通用类型
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "kvs.h"

#define EMPTY_COUNT 16

static Kvs_t* init_with_capacity(int capacity) {
	Kvs_t* kvs = malloc(sizeof(Kvs_t) + capacity * sizeof(Kv_t *));
	kvs -> count = 0;
	kvs -> capacity = capacity;
	kvs -> usable_key = 1;
	for(int i = 0; i < kvs -> capacity; i++) {
		kvs -> kv[i] = NULL;
	}
	return kvs;
}

Kvs_t* init_kvs() {
	return init_with_capacity(EMPTY_COUNT);
}

Kv_t* find_kv(Kvs_t* kvs, Key_t key) {
	for(int i = 0; i < kvs -> count; i++) {
		if(key == kvs -> kv[i] -> key) {
			return kvs -> kv[i];
		}
	}
	return NULL;		
}

Kv_t* get_kv(Kvs_t*, int index) {
	if(index < 0 || index >= kvs -> count) {
		return NULL;
	}
	return (Kv_t *)kvs -> kv[index];
}

bool update_kv(Kvs_t* kvs, Kv_t* kv) {
	Kv_t* kv_raw = find_kv(kvs, kv -> key);
	if(kv_raw == NULL) return false;

	kv_raw = kv;
	kv_raw -> key = kv -> key;

	return true;
} 

Kvs_t* add_kv(Kvs_t* kvs, Kv_t* kv) {
	if(kvs -> usable_key <= kv -> key) {
		kvs -> usable_key = kv -> key + 1;
	}

	Kv_t* kv_raw = find_kv(kvs, kv -> key);
	if(kv_raw != NULL) {
		update_kv(kvs, kv);
		return kvs;
	} else {
		if(kvs -> count < kvs ->capacity) {
			kvs -> kv[kvs -> count] = kv;
			kvs -> count = kvs -> count + 1;
			return kvs;
		} else {
			Kvs_t* kvs_new = init_with_capacity(kvs -> capacity + EMPTY_COUNT);
			int i = 0;
			for(i = 0; i < kvs -> count; i++) {
				kvs_new -> kv[i] = kvs -> kv[i];
			}
			kvs_new -> count = kvs -> count;
			kvs_new -> usable_key = kvs -> usable_key;

			free(kvs);
			kvs = NULL;

			kvs_new -> kv[kvs_new -> count] = kv;
			kvs_new -> count = kvs_new -> count + 1;
			return kvs_new;
		}
	}
	return kvs;
}

void remove_kv(Kvs_t* kvs, Key_t key) {
	int i = 0;
	for(i = 0; i < kvs -> count; i++) {
		if(key == kvs -> kv[i] -> key) {		
			free(kvs -> kv[i]);
			kvs -> kv[i] = NULL;
			break;
		}
	}

	for(int j = i; j < kvs -> count - 1; j++) {
		kvs -> kv[j] = kvs -> kv [j+1];
	}

	kvs -> count = kvs -> count - 1;
}

Kv_t* kv(Key_t key, Value_t value, size_t val_size) {
	Kv_t* keyval = malloc(sizeof(Kv_t));
	keyval -> key = key;
	
	keyval -> size = val_size;
	keyval -> value = malloc(keyval -> size);
	memcpy(keyval -> value, value, keyval -> size);

	return keyval;
}

bool out(Kvs_t* kvs, const char* path) {
	FILE* outstream;
	if ((outstream = fopen(path, "wb")) == NULL) {
		return false;
	}

	int count = kvs -> count;
	fwrite(&count, sizeof(int), 1, outstream);

	size_t size;
	for(int i = 0; i < kvs -> count; i++) {
		Key_t key = kvs -> kv[i] -> key;
		fwrite(&key, sizeof(Key_t), 1, outstream);
		size = kvs -> kv[i] -> size;
		fwrite(&size, sizeof(size_t), 1, outstream);
		fwrite(kvs -> kv[i] -> value, size, 1, outstream);
	}

	fclose(outstream);
	return true;
}

Kvs_t* in(const char* path) {
	FILE* instream;
	if ((instream = fopen(path, "rb")) == NULL) {
		return NULL;
	}
	
	Kvs_t* kvs = init_kvs();

	int count;
	fread(&count, sizeof(int), 1, instream);

	Key_t key;
	size_t size;
	for(int i = 0; i < count; i++) {
		fread(&key, sizeof(Key_t), 1, instream);
		fread(&size, sizeof(size_t), 1, instream);

		Value_t value = malloc(size);
		fread(value, size, 1, instream);

		kvs = add_kv(kvs, kv(key, value, size));
	}

	fclose(instream);
	return kvs;
}
