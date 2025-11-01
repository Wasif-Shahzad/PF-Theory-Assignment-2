#include <stdio.h>
#include <string.h>
#include <ctype.h>

void customer_info(char name[], char cnic[]) {
    printf("\n--- Customer Information ---\n");
    printf("Enter customer name: ");
    scanf(" %[^\n]", name);
    printf("Enter customer CNIC: ");
    scanf(" %[^\n]", cnic);
    printf("Customer information saved.\n");
    printf("----------------------------\n");
}

void display_inventory(int codes[], int quantities[], float prices[], int num_products) {
    printf("\n--- Supermarket Inventory ---\n");
    printf("Product Code\tQuantity in Stock\tPrice per Product\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < num_products; i++) {
        printf("%3d\t\t%d\t\t\t$%.2f\n", codes[i], quantities[i], prices[i]);
    }
    printf("---------------------------------------------------------\n");
}

void add_to_cart(int prod_codes[], int prod_quantities[], float prod_prices[], int num_products,
                 int cart_codes[], int cart_quantities[], float cart_prices[], int current_cart_idx) {
    
    int code_to_buy;
    int qty_to_buy;

    printf("\n--- Add Item to Cart ---\n");
    display_inventory(prod_codes, prod_quantities, prod_prices, num_products);
    
    printf("Enter Product Code to buy: ");
    scanf("%d", &code_to_buy);
    printf("Enter Quantity to buy: ");
    scanf("%d", &qty_to_buy);

    int product_index = -1;
    for (int i = 0; i < num_products; i++) {
        if (prod_codes[i] == code_to_buy) {
            product_index = i;
            break;
        }
    }

    if (product_index == -1) {
        printf("Error: Product code %3d not found.\n", code_to_buy);
        return;
    }

    if (prod_quantities[product_index] < qty_to_buy) {
        printf("Error: Insufficient stock for Product %3d.\n", code_to_buy);
        printf("Only %d available. Purchase cannot be completed.\n", prod_quantities[product_index]);
        return;
    }

    prod_quantities[product_index] -= qty_to_buy;

    cart_codes[current_cart_idx] = prod_codes[product_index];
    cart_quantities[current_cart_idx] = qty_to_buy;
    cart_prices[current_cart_idx] = prod_prices[product_index];

    printf("Success: %d x Product %3d added to cart.\n", qty_to_buy, code_to_buy);
    printf("Remaining stock: %d\n", prod_quantities[product_index]);
    printf("---------------------------\n");
}

void display_total_bill(int cart_quantities[], float cart_prices[], int cart_idx,
                        float* subtotal, float* discount, float* final_total, int* bill_calc_flag) {
    
    *subtotal = 0.0;
    *discount = 0.0;
    *final_total = 0.0;

    for (int i = 0; i < cart_idx; i++) {
        *subtotal += cart_prices[i] * cart_quantities[i];
    }

    printf("\n--- Total Bill Calculation ---\n");
    printf("Subtotal: \t\t$%.2f\n", *subtotal);

    char response[10];
    char promo_code[20];
    char valid_promo[] = "Eid2025"; 

    printf("Do you have a voucher? (yes/no): ");
    scanf(" %s", response);

    for(int i = 0; i < 5; i++) {
        response[i] = tolower(response[i]);
    }

    if (strcmp(response, "yes") == 0) {
        printf("Enter promo code: ");
        scanf(" %s", promo_code);
        if (strcmp(promo_code, valid_promo) == 0) {
            *discount = *subtotal * 0.25;
            printf("Promo code '%s' applied successfully!\n", valid_promo);
        } else {
            printf("Invalid promo code.\n");
        }
    }

    *final_total = *subtotal - *discount;

    printf("Discount: \t\t-$%.2f\n", *discount);
    printf("Final Total: \t\t$%.2f\n", *final_total);
    printf("--------------------------------\n");
    *bill_calc_flag = 1;
}

void show_invoice(char name[], char cnic[], float subtotal, float discount, float final_total,
                  int customer_info_set, int bill_calculated) {
    
    printf("\n========== FINAL INVOICE ==========\n");

    if (customer_info_set == 0) {
        printf("Customer Details: Not Provided\n");
    } else {
        printf("Customer Name: \t%s\n", name);
        printf("Customer CNIC: \t%s\n", cnic);
    }

    printf("\n--- Bill Details ---\n");
    
    if (bill_calculated == 0) {
        printf("Bill has not been calculated yet.\n");
    } else {
        printf("Subtotal: \t$%.2f\n", subtotal);
        printf("Discount: \t-$%.2f\n", discount);
        printf("---------------------\n");
        printf("FINAL TOTAL: \t$%.2f\n", final_total);
    }
    
    printf("===================================\n");
    printf("Thank you for shopping!\n");
}

int main() {
    int product_codes[] = {1, 2, 3, 4};
    int quantities[] = {50, 10, 20, 8};
    float prices[] = {100.0, 200.0, 300.0, 150.0};
    int num_products = 4;

    char customer_name[100];
    char customer_cnic[20];
    int customer_info_set = 0;

    int cart_codes[100];
    int cart_quantities[100];
    float cart_prices[100];
    int cart_idx = 0;

    float subtotal = 0.0;
    float discount = 0.0;
    float final_total = 0.0;
    int bill_calculated = 0;

    int choice = -1;

    do {
        printf("\n--- Supermarket Management System ---\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart (Updates inventory)\n");
        printf("4. Display Total Bill (Apply promo code)\n");
        printf("5. Show Final Invoice\n");
        printf("6. Exit\n");
        printf("---------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customer_info(customer_name, customer_cnic);
                customer_info_set = 1;
                break;
            case 2:
                display_inventory(product_codes, quantities, prices, num_products);
                break;
            case 3:
                add_to_cart(product_codes, quantities, prices, num_products,
                            cart_codes, cart_quantities, cart_prices, cart_idx);
                cart_idx++;
                break;
            case 4:
                display_total_bill(cart_quantities, cart_prices, cart_idx,
                                   &subtotal, &discount, &final_total, &bill_calculated);
                break;
            case 5:
                show_invoice(customer_name, customer_cnic, subtotal, discount, final_total,
                             customer_info_set, bill_calculated);
                break;
            case 6:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }

    } while (choice != 6);
}