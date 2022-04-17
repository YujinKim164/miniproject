typedef struct{
	char name[10];
	char description[100];
	char weight[10];
	int price;
	int type;
}Product;

int createProduct(Product *p);
void listProduct(Product *p, int count);
void readProduct(Product p);
int selectDataNo(Product *p, int count);
int updateProduct(Product *p);
int deleteProduct(Product *p);
void saveData(Product *p, int count);
int loadData(Product *p);
void searchProduct(Product *p, int count);
