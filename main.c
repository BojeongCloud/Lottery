#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_OF_POUCH 500


#define EXIT 0

#define TRUE 1
#define FALSE 0

#define GOLD_COUNT 1
#define SILVER_COUNT 3
#define BRONZE_COUNT 10

#define GOLD 3
#define SILVER 2
#define BRONZE 1
#define LOSER 0

#define PRINT_SILVER 1

#define FILE_NAME "saved.bin"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

static int gold;
static int silver;

struct lot {
	int prize;
	int is_drawn;
};

void init_lot_pouch(struct lot **pouch);
void draw_lot(struct lot *pouch);
int save_lot_pouch(struct lot *pouch);

int main(int argc, char *argv[]) {
	
	struct lot *pouch;
	
	init_lot_pouch(&pouch);

	draw_lot(pouch);
	
	save_lot_pouch(pouch);
	
	return 0;
}

void init_lot_pouch(struct lot **pouch) {
	FILE *saved_data;
	saved_data = fopen(FILE_NAME, "rb");
	*pouch = malloc(sizeof(struct lot) * SIZE_OF_POUCH);
	
	if(saved_data == NULL) {
		printf("No input file: saved.bin\n");
		printf("This is normal if you are running this software for the first time\n");
	
		int i;
		for(i = 0; i < SIZE_OF_POUCH; i++) {
			(*pouch)[i].is_drawn = FALSE;
			(*pouch)[i].prize = LOSER;
		}

		srand(time(0));
		
		gold = rand() % 500;
		if((*pouch)[gold].prize < GOLD) {
			(*pouch)[gold].prize = GOLD;
		}
		
		int silver_count = 0;
		while(silver_count < SILVER_COUNT) {
			silver = rand() % 500;
			if((*pouch)[silver].prize < SILVER) {
				(*pouch)[silver].prize = SILVER;
				silver_count++;
			}
		}
		
		int bronze;
		int bronze_count = 0;
		while(bronze_count < BRONZE_COUNT) {
			bronze = rand() % 500;
			if((*pouch)[bronze].prize < BRONZE) {
				(*pouch)[bronze].prize = BRONZE;
				bronze_count++;
			}
		}
	} else {
		fread((*pouch), sizeof(struct lot), SIZE_OF_POUCH, saved_data);
		fread(&gold, sizeof(int), 1, saved_data);
		fread(&silver, sizeof(int), 1, saved_data);
	}
	
	fclose(saved_data);
}

void draw_lot(struct lot *pouch) {
	int selected = !EXIT;
	struct lot *drawn_lot; 
	
	while(selected != EXIT) {
		printf("\n후후후... 과연 어떤 상품을 기대하고 나에게 왔는지는 모르겠지만,\n");
		printf("네가 원하는 것을 얻어가는 것은 그리 쉽진 않을 것이야,\n\n");
		
		printf("힌트는 원한다면 줄 수 있지만, 악마를 먼저 소환보는 것은 어때?\n");
		printf("반면 천사는 그리 쓸만한 정보는 주지 않을걸?\n\n"); 
		
		printf("선택한 숫자를 입력해주세요(0을 입력해서 종료): ");
		scanf("%d", &selected);
		
		if(1 <= selected && selected <= 500) {
			drawn_lot = &pouch[selected - 1];
								
			if(drawn_lot->is_drawn != FALSE) {
				printf("\n이미 사용한 숫자입니다. 다른 숫자를 입력해주세요.\n");
				continue; 
			}
			
			printf("...");
			system("timeout 1 >nul") ;
			printf("...");
			system("timeout 1 >nul") ;
			printf("...");
			system("timeout 1 >nul") ;
			
			printf("\n\n");
			printf(">> ------------ <<\n");
			switch(drawn_lot->prize) {
				case GOLD:
					printf(">> 경품추첨결과 << 축하합니다! \"1등\"입니다!!!\n");
					break;
				case SILVER:
					printf(">> 경품추첨결과 << 축하합니다! \"2등\"입니다!!!\n");
					break;
				case BRONZE:
					printf(">> 경품추첨결과 << 축하합니다! \"3등\"입니다!!!\n");
					break;
				case LOSER:
					printf(">> 경품추첨결과 << 아쉽네요..! \"꽝\"입니다!!!\n");
					break;
			}
			printf(">> ------------ <<\n");
			
			drawn_lot->is_drawn = TRUE;
		} else if(selected == 1004) {
			printf("솔직히 천사(=1004)라는 힌트는 너무 쉬웠지?\n");
			printf("그래도 상으로 이건 알려줄게\n"); 
			printf("2등 상품 중 하나는 ");
			
			if((silver + 1) % 2 == 0) {
				printf("\"짝수\"라고 한다.\n");
			} else {
				printf("\"홀수\"라고 한다.\n");
			}
		} else if(selected == 666) {
			printf("\n호오? 이런걸 입력해보다니 너는 꽤나 정상은 아닌듯 하구나?\n");
			printf("상으로 힌트를 주지 1등 상품은 ");
			int i;
			for(i = 10; i > 2; i--) {
				if((gold + 1) % i == 0) {
					printf("\"%d의 배수\"라고 한다.\n", i);
					break;
				}
			}
		} else {
			printf("1부터 500까지의 숫자를 입력해주세요\n");
		}
		
//		system("timeout 3 >nul") ;
//		system("cls");
	}
}

int save_lot_pouch(struct lot *pouch) {
	FILE *saved_data;
	saved_data = fopen(FILE_NAME, "wb");
	
	fwrite(pouch, sizeof(struct lot), SIZE_OF_POUCH, saved_data);
	fwrite(&gold, sizeof(int), 1, saved_data);
	fwrite(&silver, sizeof(int), 1, saved_data);
	
	fclose(saved_data);
}
