#ifndef file_h
#define file_h

#include "product.h"
#include "customer.h"
#include "dsa.h"

void product_save(Product p[], int count);
int product_load(Product p[]);

void customer_save(Customer c[], int count);
int customer_load(Customer c[]);

void order_save(OrderNode *head);
void order_load(OrderNode **head);

#endif

