/* ************************************************************************** */
/*                                                                            */
/*   gacha.c                                                                  */
/*                                                                            */
/*   By: Rashoru-Infinity <65536toaru@gmail.com>                              */
/*                                                                            */
/*   Created: 2021/09/05 04:06:02 by Rashoru-Infinity                         */
/*   Updated: 2021/09/05 04:06:02 by Rashoru-Infinity                         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void do_single(int max_try, double rate) {
	double current_rate = 1;

	while (max_try-- > 0) {
		current_rate *= 1 - rate;
		printf("%f\n", 1 - current_rate);
	}
}

static int fact(int x) {
	int i = 1;
	while (x > 0) {
		i *= x--;
	}
	return i;
}

static int fact_middle(int x, int offset) {
	int i = 1;
	int min = x - offset;
	while (x > min) {
		i *= x--;
	}
	return i;
}

static double get_spec_hit(int max, int spec_count, double p) {
	return fact_middle(max, spec_count) / fact(spec_count)
			* pow(p, spec_count) * pow(1 - p, max - spec_count);
}

static void do_multiple(int max_try, double rate, int quantity) {
	int curr_quantity;
	int curr_try = 1;
	while (curr_try <= max_try) {
		curr_quantity = quantity;
		double opp = 1;
		while (--curr_quantity >= 0) {
			opp -= get_spec_hit(curr_try, curr_quantity, rate);
		}
		printf("%f\n", opp);
		curr_try++;
	}
}

int main(int argc, char ** argv) {
	int max_try; 
	double rate;
	int quantity;

	if (argc != 3 && argc != 4) {
		printf("Usage : %s [tries] [rate] [times(option)]\n", argv[0]);
		return 0;
	}
	max_try = atoi(argv[1]); 
	rate = atof(argv[2]);
	if (max_try <= 0 || !(0 <= rate && rate <= 1)) {
		printf("Invalid Arguments!\n");
		return 0;
	}
	if (argc == 4) {
		quantity = atoi(argv[3]);
		if (quantity < 0) {
			printf("Invalid Arguments!\n");
			return 0;
		}
	}
	if (argc == 3) {
		do_single(max_try, rate);
	}
	if (argc == 4) {
		do_multiple(max_try, rate, quantity);
	}
	return 0;
}
