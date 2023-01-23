#include <stdio.h>
#include <stdlib.h>

int main()
{
    int choice;
    while (1)
    {
        printf("1. Browsers\n2. Communications\n3. Development\n4. Document\n5. Pro Tools\n6. Microsoft Tools\n7. Multimedia\n8. Utilities\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cls");
            system("browsers.exe");
            break;
        case 2:
            system("cls");
            system("communications.exe");
            break;
        case 3:
            system("cls");
            system("development.exe");
            break;
        case 4:
            system("cls");
            system("document.exe");
            break;
        case 5:
            system("cls");
            system("protools.exe");
            break;
        case 6:
            system("cls");
            system("microsofttools.exe");
            break;
        case 7:
            system("cls");
            system("multimedia.exe");
            break;
        case 8:
            system("cls");
            system("utilities.exe");
            break;
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}