#ifndef customer_h
#define customer_h
#define max_customers 50

typedef struct
{
    int id;
    char name[50];
    char email[60];
    char pass[30];
}Customer;

void c_registration(Customer c[],int *count);
int c_login(Customer c[], int count);

#endif