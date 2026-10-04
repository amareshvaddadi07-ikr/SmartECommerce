#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "customer.h"

void c_registration(Customer c[],int *count){
    if(*count >= max_customers)
    {
        printf("Customer Limit reached.\n");
        return;
    }
Customer c1;

c1.id=*count+1;
printf("\nEnter Name: ");
scanf(" %49[^\n]",c1.name);

printf("Enter Email:");
scanf(" %59s",c1.email);

printf("Enter Password: ");
scanf(" %29s",c1.pass);

c[*count]=c1;
(*count)++;

printf("Registration Successful. Your customer Id is %d\n",c1.id);
}

int c_login(Customer c[],int count)
{
    char email[60];
    char pass[30];

    printf("\nEnter Email: ");
    scanf("%59s",email);

    printf("Enter password: ");
    scanf("%29s",pass);

    for(int i=0;i<count;i++){
        if(strcmp(c[i].email,email)==0 && strcmp(c[i].pass,pass)==0){
            printf("Login Succesful.Welcome %s!\n",c[i].name);
            return c[i].id;
        }
    }
    printf("Invalid email or password.\n");
    return -1;
}