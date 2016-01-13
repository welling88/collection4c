#include <stdio.h>
#include <stdlib.h>

#include "kvs.h"

typedef struct {
	long id;
	int play_total;
	int win_total;
}Record_t;

void print_record(Record_t* r) {
	printf("%d %d %d \n", r -> id, r -> play_total, r -> win_total);
}

void print_val(Kv_t* kv) {
	printf("%ld: ", kv -> key);
	print_record((Record_t *)(kv -> value));
}

void print_vals(Kvs_t* kvs) {
	for(int i = 0; i < kvs -> count; i++) {
		print_val(kvs -> kv[i]);
	}
}

int main(int argc, char* argv[]) {
	Kvs_t* player_record = init_kvs();

	Record_t r1;
	r1.id = 1;
	r1.play_total = 1000;
	r1.win_total = 300;
	Kv_t* r1_kv = kv(r1.id, &r1, sizeof(r1));
	player_record = add_kv(player_record, r1_kv);
	
	Record_t r2;
	r2.id = 2;
	r2.play_total = 900;
	r2.win_total = 500;
	Kv_t* r2_kv = kv(r2.id, &r2, sizeof(r2));
	player_record = add_kv(player_record, r2_kv);

	print_vals(player_record);
	printf("write to file\n");
	out(player_record, "data");
	free(player_record);
	player_record = NULL;

	printf("\nread from file\n");
	Kvs_t* players = in("data");
	print_vals(players);

	Record_t r3;
	r3.id = 3;
	r3.play_total = 100;
	r3.win_total = 700;
	Kv_t* r3_kv = kv(r3.id, &r3, sizeof(r3));
	players = add_kv(players, r3_kv);
	
	printf("\nadd one to cache\n");
	print_vals(players);

	printf("\nremove one from cache\n");
	remove_kv(players, 2);
	print_vals(players);

	printf("\nwrite to file\n");
	out(players, "data");

	free(players);
	players = NULL;

	printf("\nread from file\n");
	Kvs_t* players_another = in("data");
	print_vals(players_another);

	free(players_another);
	players_another = NULL;
}
