#include<stdio.h>
#include "product.h"

int findProduct(Product p[], int count,int id){
    for(int i=0;i<count;i++){
        if(p[i].id==id){
            return i;
        }
    }
    return -1;
}

void product_add(Product p[],int *count){
    if(*count >= max_products){
        printf("Product limit reached.\n");
        return;
    }

    Product p1;

    printf("Enter Product ID: ");
    scanf("%d",&p1.id);

    if(findProduct(p,*count,p1.id)!=-1){
        printf("Product ID already exists.\n");
        return;
    }

    printf("Enter Product Name: ");
    scanf(" %49[^\n]",p1.name);

    printf("Enter Category: ");
    scanf(" %29[^\n]",p1.category);

    printf("Enter Price: ");
    scanf(" %f", &p1.price);

    printf("Enter Rating: ");
    scanf(" %f", &p1.rating);

    printf("Enter Stock: ");
    scanf(" %d", &p1.stock);

    p[*count]=p1;
    (*count)++;

    printf("Product added Successfully.\n");
}

void product_display(Product p[],int count){
    if(count==0){
        printf("No products available.\n");
        return;
    }

        printf("\n%-5s %-20s %-15s %-10s %-8s %-8s\n",
           "ID", "Name", "Category", "Price", "Rating", "Stock");

        printf("\n-----------------------------------------------------\n");

        for(int i=0;i<count;i++){
            printf("%-5d %-20s %-15s %-10.2f %-8.1f %-8d\n",
               p[i].id,
               p[i].name,
               p[i].category,
               p[i].price,
               p[i].rating,
               p[i].stock);

        }

}

void product_update(Product p[],int count){
    int id;
    printf("Enter Product ID to update: ");
    scanf("%d",&id);

    int index=findProduct(p,count,id);
    if(index==-1){
        printf("Product not found.\n");
        return;
    }

    printf("Enter new Product Name: ");
    scanf(" %49[^\n]",p[index].name);

    printf("Enter new Category: ");
    scanf(" %29[^\n]",p[index].category);

    printf("Enter new Price: ");
    scanf(" %f", &p[index].price);

    printf("Enter new Rating: ");
    scanf(" %f", &p[index].rating);

    printf("Enter new Stock: ");
    scanf(" %d", &p[index].stock);

    printf("Product updated successfully.\n");
}

void product_delete(Product p[], int *count){
    int id;
    printf("Enter Product ID to delete: ");
    scanf("%d",&id);

    int index=findProduct(p,*count,id);
    if(index==-1){
        printf("Product not found.\n");
        return;
    }

    for(int i=index;i<*count-1;i++){
        p[i]=p[i+1];
    }
    (*count)--;

    printf("Product deleted successfully.\n");
}