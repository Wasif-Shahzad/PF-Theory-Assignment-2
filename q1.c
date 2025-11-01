#include <stdio.h>

void add_book(int isbns[], char titles[][50], float prices[], int quantities[], int idx) {
    printf("--- Adding New Book ---\n");
    printf("Enter ISBN: ");
    int tmp;
    scanf("%d", &tmp);
    // checking if a duplicate isbn exists
    int duplicate = 0;
    for(int i = 0; i < idx; i++) {
        if(isbns[i] == tmp) {
            duplicate = 1;
            break;
        }
    }
    if(duplicate) {
        printf("Duplicate ISBN. Book not added.\n");
        return;
    }
    isbns[idx] = tmp;
    // no duplicate so continue taking input
    printf("Enter Title: ");
    scanf(" %[^\n]", titles[idx]);
    printf("Enter Price: ");
    scanf("%f", &prices[idx]);
    printf("Enter Quantity: ");
    scanf("%d", &quantities[idx]);
    printf("Book added successfully.\n");
    printf("---------------------\n");
}

void process_sale(int isbns[], int quantity[], int isbn, int qty_sold, int idx) {
    int ti = -1; // target index for the given isbn
    for(int i = 0; i < idx; i++) {
        if(isbns[i] == isbn) {
            ti = i;
            break;  
        }
    }
    if(ti == -1) {
        printf("ISBN not found. Sale cannot be processed.\n");
        return;
    }
    if(quantity[ti] < qty_sold) {
        printf("Insufficient stock. Sale cannot be processed.\n");
        return;
    }
    quantity[ti] -= qty_sold;
    printf("Sale processed successfully.\n");
}

void generate_report(int isbns[], char titles[][50], float prices[], int quantities[], int idx) {
    printf("---------------------\n");
    printf("Low Stock Report (Quantity < 5):\n");
    for(int i = 0; i < idx; i++) {
        if(quantities[i] < 5 && quantities[i] > 0) {
            printf("ISBN: %d, Title: %s, Price: %.2f, Quantity: %d\n", isbns[i], titles[i], prices[i], quantities[i]);
        }
    }
    printf("---------------------\n");
}

int main() {
    int isbns[100], quantities[100];
    float prices[100];
    char titles[100][50];
    int idx = 0; // current number of books
    int choice = -1;
    do {
        printf("What do you want to do?\n");
        printf("1. Add Book\n");
        printf("2. Process Sale\n");
        printf("3. Generate Low Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                add_book(isbns, titles, prices, quantities, idx);
                idx++;
                break;
            case 2: {
                int isbn, qty_sold;
                printf("Enter ISBN of the book to sell: ");
                scanf("%d", &isbn);
                printf("Enter quantity to sell: ");
                scanf("%d", &qty_sold);
                process_sale(isbns, quantities, isbn, qty_sold, idx);
                break;
            }
            case 3:
                generate_report(isbns, titles, prices, quantities, idx);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
}