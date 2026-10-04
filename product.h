#ifndef product_h
#define product_h
#define max_products 100

typedef struct 
{
    int id;
    char name[50];
    char category[30];
    float price;
    float rating;
    int stock;
}Product;

void product_add(Product p[],int *count);
void product_display(Product p[],int count);
void product_update(Product p[],int count);
void product_delete(Product p[], int *count);
int findProduct(Product p[],int count, int id);

#endif

