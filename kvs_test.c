#include <stdio.h>
#include <stdlib.h>

#include "kvs.h"

typedef struct {
	long id;
	int play_total;
	int win_total;
}Record_t;

char* record_to_string(Value_t r) {
	Record_t* pr = (Record_t*)r;
	char* buf = malloc(32);
	snprintf(buf, 32, "%d %d %d\n", pr -> id, pr -> play_total, pr -> win_total);
	return buf;
}

char* records_to_string(Kvs_t* kvs) {
	return kvs_to_string(kvs, record_to_string);
}

int main(int argc, char* argv[]) {
	Kvs_t* player_record = init_kvs();

	Record_t r1;
	r1.id = 1;
	r1.play_total = 1000;
	r1.win_total = 300;
	Kv_t* r1_kv = make_kv(r1.id, &r1, sizeof(r1));
	player_record = add_kv(player_record, r1_kv);
	
	Record_t r2;
	r2.id = 2;
	r2.play_total = 900;
	r2.win_total = 500;
	Kv_t* r2_kv = make_kv(r2.id, &r2, sizeof(r2));
	player_record = add_kv(player_record, r2_kv);

	
	char* s0 = records_to_string(player_record);
	printf("%s", s0);

	printf("write to file\n");
	out(player_record, "data");

	free(player_record);
	player_record = NULL;

	printf("\nread from file\n");
	Kvs_t* players = in("data");
	
	char* s1 = records_to_string(players);
	printf("%s", s1);

	Record_t r3;
	r3.id = 3;
	r3.play_total = 100;
	r3.win_total = 700;
	Kv_t* r3_kv = make_kv(r3.id, &r3, sizeof(r3));
	players = add_kv(players, r3_kv);
	
	printf("\nadd one to cache\n");
	char* s3 = records_to_string(players);
	printf("%s", s3);

	printf("\nremove one from cache\n");
	remove_kv(players, 2);
	char* s4 = records_to_string(players);
	printf("%s", s4);

	printf("\nwrite to file\n");
	out(players, "data");

	free(players);
	players = NULL;

	printf("\nread from file\n");
	Kvs_t* players_another = in("data");
	char* s5 = records_to_string(players_another);
	printf("%s", s5);

	free(players_another);
	players_another = NULL;
}
