#include <stdio.h>

void swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(char message[]) {
    int n = 0;
    while(message[n] != '\0' && message[n] != '\n' && message[n] != '\r') {
        n++;
    }
    for(int i = 0; i < n / 2; i++) {
        swap(&message[i], &message[n - i - 1]);
    }
}

void encodeMessage(char message[]) {
    int n = 0;
    while(message[n] != '\0' && message[n] != '\n' && message[n] != '\r') {
        n++;
    }
    reverse(message);
    for(int i = 0; i < n; i++) {
        int ascii = (int)message[i];
        ascii ^= (1 << (2-1));
        ascii ^= (1 << (5-1));
        message[i] = (char)ascii;
    }
}

void decodeMessage(char message[]) {
    int n = 0;
    while(message[n] != '\0' && message[n] != '\n' && message[n] != '\r') {
        n++;
    }
    for(int i = 0; i < n; i++) {
        int ascii = (int)message[i];
        ascii ^= (1 << (5-1));
        ascii ^= (1 << (2-1));
        message[i] = (char)ascii;
    }
    reverse(message);
}

int main() {
    int choice = -1;
    char message[500];
    do {
        printf("What do you want to do? \n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice == 1) {
            printf("Enter message to encode: ");
            scanf(" %[^\n]", message);
            encodeMessage(message);
            printf("Encoded Message: %s\n", message);
        } else if(choice == 2) {
            printf("Enter message to decode: ");
            scanf(" %[^\n]", message);
            decodeMessage(message);
            printf("Decoded Message: %s\n", message);
        } else if(choice != 3) {
            printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
}
