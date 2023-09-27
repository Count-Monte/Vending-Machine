#include <stdio.h>
#include <stdlib.h>

#define NICKEL 5
#define DIME 10
#define QUATER 25
#define ONE 100
#define FIVE 500

int store[5] = {25, 25, 25, 0, 0}, price[5] = {NICKEL, DIME, QUATER, ONE, FIVE};
char names[5][10] = {"nickels", "dimes", "quaters", "ones", "fives"};

void print_deposit_menu() {
	printf("Menu for deposits:\n");
	printf("  'n' - deposit a nickel\n");
	printf("  'd' - deposit a dime\n");
	printf("  'q' - deposit a quater\n");
	printf("  'o' - deposit a one dollar bill\n");
	printf("  'f' - deposit a five dollar bill\n");
	printf("  'c' - cancel the purchase\n\n");
}

void print_store() {
	puts("Stock contains:");
	for(int i = 0; i < 5; i ++)
		printf("  %d %s\n", store[i], names[i]);
	puts("");
}

void calculate_best_refund(int amount) {
	printf("\nPlease take the change below.\n");
	if(!amount) puts("  No change due.");
	
	int id = 2, cnt;
	while(amount > 0 && id >= 0) {
		cnt = amount / price[id];
		if(cnt > store[id]) cnt = store[id];
		store[id] -= cnt;
		amount -= cnt * price[id];
		
		if(cnt) printf("  %d %s\n", cnt, names[id]);
		id --;
	}
	if(id < 0 && amount > 0) {
		puts("Machine is out of change.");
		puts("See store manager for remaining refund.");
		printf("Amount due is: ");
		if(amount >= 100) printf("%d dollars", amount / 100);
		if(amount >= 100 && amount % 100) printf(" and ");
		if(amount % 100) printf("%d cents", amount % 100);
		puts("");
	}
	puts("");
}

void print_total_store() {
	int sum = 0;
	for(int i = 0; i < 5; i ++) 
		sum += store[i] * price[i];
	printf("\nTotal: ");
	if(sum >= 100) printf("%d dollars", sum / 100);
	if(sum >= 100 & sum % 100) printf(" and ");
	if(sum % 100) printf("%d cents", sum % 100);
	puts("");
}

int main()
{
	int init_prc, cur_prc;
	char inputs[20];
	float purchase;
	char command;
	
	printf("Welcome to the vending machine change maker program\nChange maker initialized.\n");
	print_store();
	
	while (1) {
		printf("Enter the purchase price (xx.xx) or 'q' to quit: ");
		scanf("%s", inputs);
		if(inputs[0] == 'q') break;
		
		purchase = atof(inputs);
		init_prc = cur_prc = (int)(purchase * 100);
		
		if(cur_prc % 5) {
			printf("Illegal price: Must be a non-negative multiple of 5 cents.\n\n");
			continue;
		}
		
		puts("");		
		print_deposit_menu();
		
		while(1) {
			printf("Payment due: ");
			if(cur_prc >= 100) printf("%d dollars", cur_prc / 100);
			if(cur_prc >= 100 && cur_prc % 100) printf(" and ");
			if(cur_prc % 100) printf("%d cents", cur_prc % 100);
			puts("");
			
			printf("Indicate your deposit: ");
			scanf("%s", inputs);
			
			switch(inputs[0]) {
				case 'n': 	cur_prc -= NICKEL;	store[0] ++;	break;
				case 'd': 	cur_prc -= DIME;	store[1] ++;	break;
				case 'q': 	cur_prc -= QUATER;	store[2] ++;	break;
				case 'o': 	cur_prc -= ONE; 	store[3] ++;	break;
				case 'f': 	cur_prc -= FIVE;	store[4] ++;	break;
				case 'c':	calculate_best_refund(init_prc - cur_prc); break;
				default: printf("Illegal selection: %c\n", inputs[0]); break;
			}
			
			if(inputs[0] == 'c') break;
			
			//Refund the remaining
			if(cur_prc <= 0) {				
				cur_prc = -cur_prc;
				calculate_best_refund(cur_prc);
				break;
			}
		}
		print_store();
	}
	
	print_total_store();
	
	return 0;
}