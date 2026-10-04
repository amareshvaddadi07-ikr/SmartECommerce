#ifndef dsa_h
#define dsa_h

#include "product.h"

typedef struct CartNode {
    Product data;
    struct CartNode* next;
} CartNode;

void cart_add(CartNode** head, Product p[],int count);
void cart_display(CartNode* head,Product p[],int count);
void cart_remove(CartNode** head);
float cart_total(CartNode* head,Product p[],int count);
void cart_free(CartNode** head);

typedef struct OrderNode {
    int customerId;
    int productId;
    int quantity;
    float amount;
    struct OrderNode* next;
} OrderNode;

void order_add(OrderNode** head, int customerId, int productId, int quantity, float amount);
void order_display(OrderNode* head, int customerId);
void order_free(OrderNode** head);

typedef struct BSTNode {
    int productId;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* BST_insert(BSTNode* root, int id);
BSTNode *BST_search(BSTNode* root, int id);
void BST_inorder(BSTNode* root);
void BST_free(BSTNode* root);

void searchByName(Product p[], int count);
void searchByCategory(Product p[], int count);

void sortByPrice(Product p[], int count);
void sortByRating(Product p[], int count);
void sortByName(Product p[], int count);

void recommend(Product p[], int count, OrderNode* head, int customerId);

#endif
