#include <stdio.h>
#include <string.h>

#include "dsa.h"
#include "product.h"
#include "customer.h"
#include "file.h"


void adminMenu(Product p[], int *productCount, BSTNode **root)
{
    int choice;

    do
    {
        printf("\n------ Admin Menu -------\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Category\n");
        printf("7. Sort Products by Price\n");
        printf("8. Sort Products by Rating\n");
        printf("9. Sort Products by Name\n");
        printf("10. Search by ID\n");
        printf("11. Display Inorder\n");
        printf("0. Logout\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int oldCount = *productCount;

            product_add(p, productCount);

            if (*productCount > oldCount)
            {
                *root = BST_insert(
                    *root,
                    p[*productCount - 1].id
                );

                product_save(p, *productCount);
            }

            break;
        }

        case 2:
            product_display(p, *productCount);
            break;

        case 3:
            product_update(p, *productCount);
            product_save(p, *productCount);
            break;

        case 4:
            product_delete(p, productCount);

            BST_free(*root);
            *root = NULL;

            for (int i = 0; i < *productCount; i++)
            {
                *root = BST_insert(
                    *root,
                    p[i].id
                );
            }

            product_save(p, *productCount);
            break;

        case 5:
            searchByName(p, *productCount);
            break;

        case 6:
            searchByCategory(p, *productCount);
            break;

        case 7:
            sortByPrice(p, *productCount);
            product_display(p, *productCount);
            product_save(p, *productCount);
            break;

        case 8:
            sortByRating(p, *productCount);
            product_display(p, *productCount);
            product_save(p, *productCount);
            break;

        case 9:
            sortByName(p, *productCount);
            product_display(p, *productCount);
            product_save(p, *productCount);
            break;

        case 10:
        {
            int id;

            printf("Enter Product ID: ");
            scanf("%d", &id);

            if (BST_search(*root, id) != NULL)
            {
                printf("Product ID found.\n");
            }
            else
            {
                printf("Product ID not found.\n");
            }

            break;
        }

        case 11:
            printf("Inorder:\n");
            BST_inorder(*root);
            printf("\n");
            break;

        case 0:
            printf("Logging out...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 0);
}


void customerMenu(Product p[],
                  int productCount,
                  OrderNode **orderHead,
                  int customerId)
{
    CartNode *head = NULL;

    int choice;

    do
    {
        printf("\n------ Customer Menu -------\n");
        printf("1. View Products\n");
        printf("2. Search by Name\n");
        printf("3. Search by Category\n");
        printf("4. Sort by Price\n");
        printf("5. Sort by Rating\n");
        printf("6. Sort by Name\n");
        printf("7. Add to Cart\n");
        printf("8. View Cart\n");
        printf("9. Remove from Cart\n");
        printf("10. Checkout\n");
        printf("11. Purchase History\n");
        printf("12. Recommendations\n");
        printf("0. Logout\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            product_display(p, productCount);
            break;

        case 2:
            searchByName(p, productCount);
            break;

        case 3:
            searchByCategory(p, productCount);
            break;

        case 4:
            sortByPrice(p, productCount);
            product_display(p, productCount);
            break;

        case 5:
            sortByRating(p, productCount);
            product_display(p, productCount);
            break;

        case 6:
            sortByName(p, productCount);
            product_display(p, productCount);
            break;

        case 7:
            if (productCount > 0)
            {
                cart_add(&head, p, productCount);
            }
            else
            {
                printf("No products available.\n");
            }
            break;

        case 8:
            cart_display(head, p, productCount);
            break;

        case 9:
            if (head == NULL)
            {
                printf("Cart is empty.\n");
            }
            else
            {
                cart_remove(&head);
            }
            break;

        case 10:
        {
            if (head == NULL)
            {
                printf("Cart is empty.\n");
                break;
            }

            cart_display(head, p, productCount);

            int confirm;

            printf("Confirm purchase? (1 for Yes, 0 for No): ");
            scanf("%d", &confirm);

            if (confirm == 1)
            {
                CartNode *current = head;

                while (current != NULL)
                {
                    for (int i = 0; i < productCount; i++)
                    {
                        if (p[i].id == current->data.id)
                        {
                            p[i].stock -= current->data.stock;

                            float amount =
                                p[i].price *
                                current->data.stock;

                            order_add(
                                orderHead,
                                customerId,
                                p[i].id,
                                current->data.stock,
                                amount
                            );

                            break;
                        }
                    }

                    current = current->next;
                }

                printf("Purchase successful!\n");

                product_save(p, productCount);
                order_save(*orderHead);

                cart_free(&head);
            }
            else
            {
                printf("Purchase cancelled.\n");
            }

            break;
        }

        case 11:
            order_display(*orderHead, customerId);
            break;

        case 12:
            recommend(
                p,
                productCount,
                *orderHead,
                customerId
            );
            break;

        case 0:
            cart_free(&head);
            printf("Logging out...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 0);
}


int main()
{
    Product products[max_products] = {0};
    Customer customers[max_customers] = {0};

    int productCount = 0;
    int customerCount = 0;

    OrderNode *orderHead = NULL;
    BSTNode *root = NULL;

    
    productCount = product_load(products);
    customerCount = customer_load(customers);
    order_load(&orderHead);

    /* Build BST from loaded products */
    for (int i = 0; i < productCount; i++)
    {
        root = BST_insert(
            root,
            products[i].id
        );
    }

    int choice;

    do
    {
        printf("\n------ SMART E COMMERCE -------\n");
        printf("1. Admin Login\n");
        printf("2. Customer Registration\n");
        printf("3. Customer Login\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char adminPass[30];

            printf("Enter Admin Password: ");
            scanf("%29s", adminPass);

            if (strcmp(adminPass, "admin123") == 0)
            {
                printf("Admin Login Successful.\n");

                adminMenu(
                    products,
                    &productCount,
                    &root
                );
            }
            else
            {
                printf("Wrong Password.\n");
            }

            break;
        }

        case 2:
            c_registration(
                customers,
                &customerCount
            );

            customer_save(
                customers,
                customerCount
            );

            break;

        case 3:
        {
            int customerId =
                c_login(
                    customers,
                    customerCount
                );

            if (customerId != -1)
            {
                customerMenu(
                    products,
                    productCount,
                    &orderHead,
                    customerId
                );
            }
            else
            {
                printf("Login failed.\n");
            }

            break;
        }

        case 0:
            product_save(
                products,
                productCount
            );

            customer_save(
                customers,
                customerCount
            );

            order_save(orderHead);

            BST_free(root);
            order_free(&orderHead);

            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}