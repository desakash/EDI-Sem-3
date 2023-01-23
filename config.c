#include<stdio.h>
#include<stdlib.h>

int main()
{
   int choice;
    while (1)
    {
        printf("1. Features\n2. Fixes\n3. Legacy Window Panels\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cls");
            system("install.exe");
            break;
        case 2:
            system("cls");
            system("tweeks.exe");
            break;
        case 3:
            system("cls");
            system("config.exe");
            break;
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}