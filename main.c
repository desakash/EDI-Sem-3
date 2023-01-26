#include <stdio.h>
#include <stdlib.h>
#include "install.h"
#include "tweeks.h"

void runinstall()
{
    int choice;
    while (1)
    {
        printf("1. Browsers\n2. Communications\n3. Development\n4. Pro Tools\n5. Multimedia\n6. Utilities\n7. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            browsers();
            break;
        case 2:
            communications();
            break;
        case 3:
            development();
            break;
        case 4:
            proTools();
            break;
        case 5:
            multimedia();
            break;
        case 6:
            utilities();
            break;
        case 7:
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}

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
            break;
        case 3:
            changeDNS();
            break;
        case 4:
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}

int main()
{
    system("powershell -ExecutionPolicy Bypass -File .\\scripts\\checkChocolatey.ps1");
    system("powershell -ExecutionPolicy Bypass -File .\\scripts\\wingetInstall.ps1");
    int choice;
    while (1)
    {
        printf("\n1. Installs\n2. Tweaks\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            runinstall();
            break;
        case 2:
            runtweeks();
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}