#include<stdio.h>
#include "file.h"

void product_save(Product p[], int count){
    FILE *fp=fopen("data/products.dat","wb");
    if(fp==NULL){
        printf("Could not save products.\n");
        return;
    }
    fwrite(&count,sizeof(int),1,fp);
    fwrite(p,sizeof(Product),count,fp);
    fclose(fp);
}

int product_load(Product p[]){
    FILE *fp=fopen("data/products.dat","rb");
    if(fp==NULL){
        return 0;
    }
    int count;
    fread(&count,sizeof(int),1,fp);
    fread(p,sizeof(Product),count,fp);
    fclose(fp);
    return count;
}

void customer_save(Customer c[], int count){
    FILE *fp=fopen("data/customers.dat","wb");
    if(fp==NULL){
        printf("Could not save customers.\n");
        return;
    }
    fwrite(&count,sizeof(int),1,fp);
    fwrite(c,sizeof(Customer),count,fp);
    fclose(fp);
}

int customer_load(Customer c[]){
    FILE *fp=fopen("data/customers.dat","rb");
    if(fp==NULL){
        return 0;
    }
    int count;
    fread(&count,sizeof(int),1,fp);
    fread(c,sizeof(Customer),count,fp);
    fclose(fp);
    return count;
}

void order_save(OrderNode* head){
    FILE *fp=fopen("data/orders.dat","wb");
    if(fp==NULL){
        printf("Could not save orders.\n");
        return;
    }
    OrderNode* current=head;
    while(current!=NULL){
        fwrite(&current->customerId,sizeof(int),1,fp);
        fwrite(&current->productId,sizeof(int),1,fp);
        fwrite(&current->quantity,sizeof(int),1,fp);
        fwrite(&current->amount,sizeof(float),1,fp);
        current=current->next;
    }
    fclose(fp);
}

void order_load(OrderNode** head){
    FILE *fp=fopen("data/orders.dat","rb");
    if(fp==NULL){
        return;
    }
    int customerId, productId, quantity;
    float amount;
    while(fread(&customerId,sizeof(int),1,fp)==1){
        fread(&productId,sizeof(int),1,fp);
        fread(&quantity,sizeof(int),1,fp);
        fread(&amount,sizeof(float),1,fp);
        order_add(head,customerId,productId,quantity,amount);
    }
    fclose(fp);
}