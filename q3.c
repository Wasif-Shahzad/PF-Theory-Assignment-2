#include <stdio.h>

void update_sector(int grid[101][101]) {
    int x, y;
    printf("Enter coordinates to update (x y): ");
    scanf("%d %d", &x, &y);
    if(x <= 0 || y <= 0 || x > 100 || y > 100) {
        printf("Invalid coordinates. Must be between 1 and 100.\n");
        return;
    }
    int set = 0;
    printf("Enter 1 if you want to set a flag or 0 if you want to clear a flag: ");
    scanf("%d", &set);
    int flag = -1;
    printf("Enter flag to be updated (0-2): ");
    scanf("%d", &flag);
    if(flag < 0 || flag > 2) {
        printf("Invalid flag. Must be between 0 and 2.\n");
        return;
    }
    if(set) {
        grid[x][y] |= (1 << flag);
        printf("Flag %d set at (%d, %d).\n", flag, x, y);
    } else {
        if(!(grid[x][y] & (1 << flag))) {
            printf("Flag %d is not set at (%d, %d). Cannot clear.\n", flag, x, y);
            return;
        }
        grid[x][y] ^= (1 << flag);
        printf("Flag %d cleared at (%d, %d).\n", flag, x, y);
    }
}

void query_status(int x, int y, int grid[101][101]) {
    if(x <= 0 || y <= 0 || x > 100 || y > 100) {
        printf("Invalid coordinates. Must be between 1 and 100.\n");
        return;
    }
    printf("------Status for Sector (%d, %d)------\n", x, y);
    printf("Power status: ");
    if(grid[x][y] & 1) {
        // set the 0th bit as 2^0 = 1
        printf("Power ON\n");
    } else {
        printf("Power OFF\n");
    }
    printf("Overload Warning: ");
    if(grid[x][y] & 2) {
        // set the 1st bit as 2^1 = 2
        printf("OVERLOAD\n");
    } else {
        printf("Normal\n");
    }
    printf("Maintenance Required: ");
    if(grid[x][y] & 4) {
        // set the 2nd bit as 2^2 = 4
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    printf("-----------------------------------\n");
}

int diagnose(int grid[101][101]) {
    int count = 0;
    for(int i = 1; i <= 100; i++) {
        for(int j = 1; j <= 100; j++) {
            if((grid[i][j] & 2) || (grid[i][j] & 4)) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int grid[101][101] = {0};
    int choice = -1;
    do {
        printf("What do you want to do?\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Diagnose Grid\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                update_sector(grid);
                break;
            case 2: {
                int x, y;
                printf("Enter coordinates to query (x y): ");
                scanf("%d %d", &x, &y);
                query_status(x, y, grid);
                break;
            }
            case 3: {
                int issues = diagnose(grid);
                printf("Total sectors with issues (overload or maintenance required): %d\n", issues);
                break;
            }
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
}