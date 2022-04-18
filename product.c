#include <stdio.h>
#include <string.h>
#include "product.h"

int selectMenu(){
	int menu;
	printf("\n*** 가격계산기 ***\n");
	printf("1. 조회\n");
	printf("2. 추가\n");
	printf("3. 수정\n");
	printf("4. 삭제\n");
	printf("5. 파일저장\n");
	printf("6. 이름검색\n");
	printf("0. 종료\n\n");
	printf("=> 원하는 메뉴는? ");
	scanf("%d", &menu);
	return menu;
}

int createProduct(Product *p){
	printf("제품명은? \n");
	scanf("%s", p->name);
	printf("설명은? \n");
	scanf("%s", p->description);
	printf("중량은? \n");
	scanf("%s", p->weight);
	printf("가격은? \n");
	scanf("%d", &p->price);
	printf("배송방법은? (1:새벽배송/2.택배배송)\n");
	scanf("%d", &p->type);
	printf("=> 추가됨\n");
	return 1;
}

void readProduct(Product p){
	printf("%-s %-s %-s %-d %-d ", p.name, p.description, p.weight, p.price, p.type);
}

void listProduct(Product *p, int count){
	printf("제품명     설명 중량   가격   배송방법\n");
	printf("=====================================\n");
	for(int i = 0; i < count; i++){
		if(p[i].price == -1) continue;
		printf("%d ", i+1);
		readProduct(p[i]);
		printf("\n");
	}
	printf("\n");
}

int selectDataNo(Product *p, int count){
	int no;
	listProduct(p, count);
	printf("번호는 (취소: 0)? ");
       	scanf("%d", &no);
	return no;
}

int updateProduct(Product *p){
	printf("제품명은? \n");
	scanf("%s", p->name);
	printf("설명은? \n");
	scanf("%s", p->description);
	printf("중량은? \n");
	scanf("%s", p->weight);
	printf("가격은? \n");
	scanf("%d", &p->price);
	printf("배송방법은? (1:새벽배송/2.택배배송)\n");
	scanf("%d", &p->type);
	printf("=> 수정됨!\n");
	return 1;
}
 int deleteProduct(Product *p){
	 p->price = -1;
	 p->type = -1;
	 return 1;
 }

void saveData(Product *p, int count){
	FILE *fp;
	fp = fopen("product.txt", "wt");
	for (int i = 0; i <count; i++){
		if (p[i].price == -1) continue;
		fprintf(fp, "%-s %-s %-s %-d %-d ", p[i].name, p[i].description, p[i].weight, p[i].price, p[i].type);
	}
	fclose(fp);
	printf("=> 저장됨!\n");
}

int loadData(Product *p){
	int count = 0, i = 0;
	FILE *fp;
	fp = fopen("product.txt", "rt");
	for (; i < 100; i++){
		fscanf(fp, "%s", p[i].name);
		if (feof(fp)) break;
		fscanf(fp, "%s", p[i].description);
		fscanf(fp, "%s", p[i].weight);
		fscanf(fp, "%d", &p[i].price);
		fscanf(fp, "%d", &p[i].type);
	}
	fclose(fp);
	printf("=> 로딩성공!\n");
	return i;
}
void searchProduct(Product *p, int count){
	int scnt = 0;
	char search[20];
	printf("검색할 이름? ");
	scanf("%s", search);

	printf("제품명     설명 중량   가격   배송방법\n");
	printf("====================================\n");
	for (int i = 0; i < count; i ++){
		if (p[i].price == -1) continue;
		if (strstr(p[i].name, search)){
			readProduct(p[i]);
			scnt++;
		}
	}
	if (scnt == 0) printf("=> 검색된 데이터 없음!");
	printf("\n");
}


int main(void){
	int count = 0;
	int result = 0;
	Product plist[20];
	int index = 0;
	int menu;

	count = loadData(plist);
	index = count;

	while(1){
		menu = selectMenu();
		if (menu == 0) break;
		if (menu == 1){
			if (count > 0)
			       	listProduct(plist, index);
		}
		else if (menu == 2)
		       	count += createProduct(&plist[index++]);
		else if (menu == 3){
			int no = selectDataNo(plist, index);
			if (no == 0){
				printf("=> 취소됨!\n");
				continue;
			}
			updateProduct(&plist[no-1]);
		}
		else if (menu == 4){
			int no = selectDataNo(plist, index);
			if (no == 0){
				printf("=> 취소됨!\n");
				continue;
			}
			int deleteok;
			printf("정말로 삭제하시겠습니까?(삭제: 1)");
			scanf("%d", &deleteok);
			if(deleteok == 1){
				if(deleteProduct(&plist[no-1])) count--;
			}
			printf("=> 삭제됨!\n");
		}
		else if (menu == 5)
			saveData(plist, index);
		else if (menu == 6)
			searchProduct(plist, index);
	}
	printf("종료됨!\n");
	return 0;
}
