#include <stdio.h>
#include <stdlib.h>
#include "tweeks.h"

void runtweeks()
{
    int choice;
    while (1)
    {
        printf("1. Essential Tweeks\n2. Misc. Tweeks\n3. Change DNS\n4. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            essentialTweeks();
            break;
        case 2:
            miscTweeks();
            // system("tweeks.exe");
            break;
        case 3:
            system("cls");
            // system("config.exe");
            break;
        case 4:
            system("cls");
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n1. Tweeks\n2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            runtweeks();
            break;
        case 2:
            return 0;
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}