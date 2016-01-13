
#include <stdio.h>

#include "userbase.h"

int main(int argc, char* argv[]) {
	Kvs_t* records = load("psRecord");

	Record_t r1;
	r1.id = 11;
	r1.play_total = 0;
	r1.win_total = 0;

	records = add_record(records, &r1);

	Record_t r2;
	r2.id = 12;
	r2.play_total = 0;
	r2.win_total = 0;

	records = add_record(records, &r2);

	incr_record_play(records, 11, 100);

	incr_record_play(records, 12, 1000);
	incr_record_win(records, 12, 400);

	char* str0 = records_to_string(records);
	printf("%s\n", str0);

	save(records, "psRecord");

	free(records);
	records = NULL;

	Kvs_t* records_new = load("psRecord");
	
	char* str1 = records_to_string(records_new);
	printf("%s\n", str1);

	free(records_new);
	records_new = NULL;

	Kvs_t* params = load("psParam");
	
	Param_t p1;
	p1.id = 5;
	p1.probability = 0.8;

	char* str3 = param_to_string(&p1);
	printf("%s", str3);


	for(int i = 0; i < 10; i ++) {
		Param_t p;
		p.id = i;
		p.probability = 0.05 * i;
		params = add_param(params, &p);
	}

	char* str2 = params_to_string(params);
	printf("%s\n", str2);

	free(params);
	params = NULL;
}
