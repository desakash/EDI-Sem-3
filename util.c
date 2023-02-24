#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fileapi.h>

void askRestart()
{
    printf("Restart is required for changes to take effect\n");
    int choice;
    while (1)
    {
        printf("\n");
        printf("1. Restart Now\n2. Restart Later\n");
        printf("Select: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("shutdown /r /t 0");
            break;
        case 2:
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}

char *getAppCode(char *name)
{
    FILE *fp;
    char row[100];
    char *found;
    int flag = 0;
    fp = fopen("data/applications.csv", "r");

    while (feof(fp) != true)
    {
        fgets(row, 1000, fp);
        found = strtok(row, ",");
        while (found != NULL)
        {
            if (strcmp(found, name) == 0)
            {
                flag = 1;
                found = strtok(NULL, ",");
                continue;
            }
            if (flag == 1)
            {
                flag = 0;
                return found;
            }
            found = strtok(NULL, ",");
        }
    }
}

char *getFromcsv(char *key)
{
    FILE *fp;
    char row[1000];
    char *found;
    int flag = 0;
    fp = fopen("data/locations.csv", "r");

    while (feof(fp) != true)
    {
        fgets(row, 1000, fp);
        found = strtok(row, ",");
        while (found != NULL)
        {
            if (strcmp(found, key) == 0)
            {
                flag = 1;
                found = strtok(NULL, ",");
                continue;
            }
            if (flag == 1)
            {
                flag = 0;
                return found;
            }
            found = strtok(NULL, ",");
        }
    }
}

void setRegistry(char *name, int value)
{
    char *path = getFromcsv(name);
    char main[1000] = "powershell Set-ItemProperty -Path '";
    strcat(main, path);
    strcat(main, "' -Name '");
    strcat(main, name);
    strcat(main, "' -Type DWord -Value ");
    char val[10];
    sprintf(val, "%d", value);
    strcat(main, val);
    system(main);
}

int getDiskSpace()
{
    BOOL fResult;
    unsigned __int64 i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
    fResult = GetDiskFreeSpaceEx("C:",(PULARGE_INTEGER)&i64FreeBytesToCaller,(PULARGE_INTEGER)&i64TotalBytes,(PULARGE_INTEGER)&i64FreeBytes);
    if (fResult)
    {
        printf("Free space on drive = %I64u MB\n", i64FreeBytes / (1024 * 1024));
    }
    int freeSpace=(int)i64FreeBytes / (1024 * 1024);

    return freeSpace;
}

int spaceAvailable(char *AppCode)
{
    FILE *fp;
    char row[1000];
    char *found;
    int flag = 0;
    fp = fopen("data/locations.csv", "r");

    while (feof(fp) != true)
    {
        fgets(row, 1000, fp);
        found = strtok(row, ",");
        while (found != NULL)
        {
            if (strcmp(found, AppCode) == 0)
            {
                flag = 1;
                found = strtok(NULL, ",");
                continue;
            }
            if (flag == 1)
            {
                flag = 0;
            }
            found = strtok(NULL, ",");
        }
    }
    printf("\nRequired Disk Space : %s MB",found);
    if (atoi(found) <= getDiskSpace())
    {
        printf("Disk Requirement Met...Proceeding to Install");
        return 1;
    }
    printf("\nInsufficient Disk Space...Software can not be Installed");
    return 0;
}

void processInstall(char *AppID)
{
    char *AppCode = getAppCode(AppID);
    if (!spaceAvailable(AppCode))
    {
        return;
    }

    char command[1000] = "powershell winget install -e --accept-source-agreements --accept-package-agreements --silent ";
    strcat(command, AppCode);
    system(command);
}

void installFeatures()
{
    system("powershell Write-Host 'Hello'");
}

void legacyPanels()
{
    system("powershell Write-Host 'Hello'");
}