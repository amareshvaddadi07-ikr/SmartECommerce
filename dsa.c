#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsa.h"

void cart_add(CartNode **head, Product p[], int count)
{
    int id, quantity;
    printf("Enter Product ID: ");
    scanf("%d", &id);
    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (p[i].id == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Product not found.\n");
        return;
    }
    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0 || quantity > p[index].stock)
    {
        printf("Invalid quantity.\n");
        return;
    }

    CartNode *newNode = (CartNode *)malloc(sizeof(CartNode));
    newNode->data = p[index];
    newNode->data.stock = quantity;
    newNode->next = *head;
    *head = newNode;

    printf("Product added to cart.\n");
}

void cart_display(CartNode *head, Product p[], int count)
{
    if (head == NULL)
    {
        printf("Cart is empty.\n");
        return;
    }
    float total = 0;

    printf("\nCart:\n");
    printf("-----------------------------------------------------\n");
    CartNode *current = head;
    while (current != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            if (p[i].id == current->data.id)
            {
                float amount = p[i].price * current->data.stock;

                printf("%s x %d = %.2f\n", p[i].name, current->data.stock, amount);
                total += amount;
                break;
            }
        }

        current = current->next;
    }

    printf("Total: %.2f\n", total);
}

float cart_total(CartNode *head, Product p[], int count)
{
    float total = 0;
    CartNode *current = head;
    while (current != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            if (p[i].id == current->data.id)
            {
                total += p[i].price * current->data.stock;
                break;
            }
        }
        current = current->next;
    }
    return total;
}

void cart_remove(CartNode **head)
{
    int id;
    printf("Enter Product ID to remove: ");
    scanf("%d", &id);

    CartNode *current = *head;
    CartNode *prev = NULL;
    while (current != NULL)
    {
        if (current->data.id == id)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Product removed from cart.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Product not found in cart.\n");
}

void cart_free(CartNode **head)
{
    CartNode *current = *head;
    while (current != NULL)
    {
        CartNode *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

void order_add(OrderNode **head, int customerId, int productId, int quantity, float amount)
{
    OrderNode *newNode = (OrderNode *)malloc(sizeof(OrderNode));
    newNode->customerId = customerId;
    newNode->productId = productId;
    newNode->quantity = quantity;
    newNode->amount = amount;
    newNode->next = *head;
    *head = newNode;
}

void order_display(OrderNode *head, int customerId)
{
    if (head == NULL)
    {
        printf("No orders found.\n");
        return;
    }

    int found = 0;
    printf("\nOrders:\n");
    printf("-----------------------------------------------------\n");
    OrderNode *current = head;
    while (current != NULL)
    {
        if (current->customerId == customerId)
        {
            printf("Product ID: %d, Quantity: %d, Amount: %.2f\n", current->productId, current->quantity, current->amount);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
    {
        printf("No purchase history.\n");
    }
}

void order_free(OrderNode **head)
{
    OrderNode *current = *head;
    while (current != NULL)
    {
        OrderNode *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

BSTNode *BST_insert(BSTNode *root, int id)
{
    if (root == NULL)
    {
        BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
        newNode->productId = id;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (id < root->productId)
    {
        root->left = BST_insert(root->left, id);
    }
    else if (id > root->productId)
    {
        root->right = BST_insert(root->right, id);
    }
    return root;
}

void BST_free(BSTNode *root)
{
    if (root != NULL)
    {
        BST_free(root->left);
        BST_free(root->right);
        free(root);
    }
}

void BST_inorder(BSTNode *root)
{
    if (root != NULL)
    {
        BST_inorder(root->left);
        printf("%d ", root->productId);
        BST_inorder(root->right);
    }
}

BSTNode *BST_search(BSTNode *root, int id)
{
    if (root == NULL || root->productId == id)
    {
        return root;
    }
    if (id < root->productId)
    {
        return BST_search(root->left, id);
    }
        return BST_search(root->right, id);
}

void searchByName(Product p[], int count)
{
    char name[50];
    printf("Enter product name to search: ");
    scanf("%49s", name);
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strstr(p[i].name, name) != NULL)
        {
            printf("Product ID: %d, Name: %s, Category: %s, Price: %.2f, Rating: %.1f, Stock: %d\n",
                   p[i].id, p[i].name, p[i].category, p[i].price, p[i].rating, p[i].stock);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No products found with the name '%s'.\n", name);
    }
}

void searchByCategory(Product p[], int count)
{
    char category[30];
    printf("Enter product category to search: ");
    scanf("%29s", category);
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strstr(p[i].category, category) != NULL)
        {
            printf("Product ID: %d, Name: %s, Category: %s, Price: %.2f, Rating: %.1f, Stock: %d\n",
                   p[i].id, p[i].name, p[i].category, p[i].price, p[i].rating, p[i].stock);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No products found in the category '%s'.\n", category);
    }
}

void sortByPrice(Product p[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < count; j++)
        {
            if (p[j].price < p[min].price)
            {
                min = j;
            }
        }
        Product temp = p[i];
        p[i] = p[min];
        p[min] = temp;
    }
    printf("Products sorted by price.\n");
}

void sortByRating(Product p[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < count; j++)
        {
            if (p[j].rating > p[max].rating)
            {
                max = j;
            }
        }
        Product temp = p[i];
        p[i] = p[max];
        p[max] = temp;
    }
    printf("Products sorted by rating.\n");
}

void sortByName(Product p[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(p[j].name, p[min].name) < 0)
            {
                min = j;
            }
        }
        Product temp = p[i];
        p[i] = p[min];
        p[min] = temp;
    }
    printf("Products sorted by name.\n");
}

void recommend(Product p[], int count, OrderNode *head, int customerId){
    int productId=-1;
    while(head!=NULL){
        if(head->customerId==customerId){
            productId=head->productId;
            break;
        }
        head=head->next;
    }
    if(productId==-1){
        printf("\nRecommended Products:\n");
    for(int i=0;i<count;i++){
        if(p[i].rating>=4.0){
                printf("Product ID: %d, Name: %s, Category: %s, Price: %.2f, Rating: %.1f, Stock: %d\n",
                       p[i].id, p[i].name, p[i].category, p[i].price, p[i].rating, p[i].stock);
            
        }
    }
    return;
}

char category[30] = "";
    for(int i=0;i<count;i++){
        if(p[i].id==productId){
            strcpy(category,p[i].category);
            break;
        }
    }
    printf("\nRecommended Products from category: %s\n",category);
    for(int i=0;i<count;i++){
        if(strcmp(p[i].category,category)==0 && p[i].id!=productId && p[i].rating>=4.0){
            printf("%d - %s - %s - %.2f - %.1f, Stock: %d\n",
                   p[i].id, p[i].name, p[i].category, p[i].price, p[i].rating, p[i].stock);
        }
    }
}
