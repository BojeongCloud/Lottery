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
		printf("\n������... ���� � ��ǰ�� ����ϰ� ������ �Դ����� �𸣰�����,\n");
		printf("�װ� ���ϴ� ���� ���� ���� �׸� ���� ���� ���̾�,\n\n");
		
		printf("��Ʈ�� ���Ѵٸ� �� �� ������, �Ǹ��� ���� ��ȯ���� ���� �?\n");
		printf("�ݸ� õ��� �׸� ������ ������ ���� ������?\n\n"); 
		
		printf("������ ���ڸ� �Է����ּ���(0�� �Է��ؼ� ����): ");
		scanf("%d", &selected);
		
		if(1 <= selected && selected <= 500) {
			drawn_lot = &pouch[selected - 1];
								
			if(drawn_lot->is_drawn != FALSE) {
				printf("\n�̹� ����� �����Դϴ�. �ٸ� ���ڸ� �Է����ּ���.\n");
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
					printf(">> ��ǰ��÷��� << �����մϴ�! \"1��\"�Դϴ�!!!\n");
					break;
				case SILVER:
					printf(">> ��ǰ��÷��� << �����մϴ�! \"2��\"�Դϴ�!!!\n");
					break;
				case BRONZE:
					printf(">> ��ǰ��÷��� << �����մϴ�! \"3��\"�Դϴ�!!!\n");
					break;
				case LOSER:
					printf(">> ��ǰ��÷��� << �ƽ��׿�..! \"��\"�Դϴ�!!!\n");
					break;
			}
			printf(">> ------------ <<\n");
			
			drawn_lot->is_drawn = TRUE;
		} else if(selected == 1004) {
			printf("������ õ��(=1004)��� ��Ʈ�� �ʹ� ������?\n");
			printf("�׷��� ������ �̰� �˷��ٰ�\n"); 
			printf("2�� ��ǰ �� �ϳ��� ");
			
			if((silver + 1) % 2 == 0) {
				printf("\"¦��\"��� �Ѵ�.\n");
			} else {
				printf("\"Ȧ��\"��� �Ѵ�.\n");
			}
		} else if(selected == 666) {
			printf("\nȣ��? �̷��� �Է��غ��ٴ� �ʴ� �ϳ� ������ �ƴѵ� �ϱ���?\n");
			printf("������ ��Ʈ�� ���� 1�� ��ǰ�� ");
			int i;
			for(i = 10; i > 2; i--) {
				if((gold + 1) % i == 0) {
					printf("\"%d�� ���\"��� �Ѵ�.\n", i);
					break;
				}
			}
		} else {
			printf("1���� 500������ ���ڸ� �Է����ּ���\n");
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
