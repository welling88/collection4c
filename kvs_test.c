#include <stdio.h>
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

	// write to file 
	out(player_record, "data");

	printf("--------\n");

	// read from file
	Kvs_t* players = in("data");
	print_vals(players);
}
