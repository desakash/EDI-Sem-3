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
    fResult = GetDiskFreeSpaceEx("C:", (PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes);
    if (fResult)
    {
        printf("Free space on drive = %I64u MB\n", i64FreeBytes / (1024 * 1024));
    }
    int freeSpace = (int)i64FreeBytes / (1024 * 1024);

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
    printf("\nRequired Disk Space : %s MB", found);
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
    int choice;
    while (1)
    {
        printf("\n");
        printf("1. Windows Subsystem for Linux\n2. Hyper-V Virtualization\n3. .Net Framework\n4. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'VirtualMachinePlatform' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Windows-Subsystem-Linux' -All -NoRestart");
            system("powershell Write-Host 'WSL is now installed and configured.'");
            askRestart();
            break;
        case 2:
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'HypervisorPlatform' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Hyper-V-All' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Hyper-V' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Hyper-V-Tools-All' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Hyper-V-Management-PowerShell' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Hyper-V-Hypervisor' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Hyper-V-Services' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'Microsoft-Hyper-V-Management-Clients' -All -NoRestart");
            system("cmd /c bcdedit /set hypervisorschedulertype classic");
            system("powershell Write-Host 'HyperV is now installed and configured.'");
            askRestart();
            break;
        case 3:
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'NetFx4-AdvSrvs' -All -NoRestart");
            system("powershell Enable-WindowsOptionalFeature -Online -FeatureName 'NetFx3' -All -NoRestart");
            system("powershell Write-Host '.Net Framework is now installed and configured.'");
            askRestart();
            return;
        case 4:
            return;
        default:
            printf("Invalid Choice");
            break;
        }
    }
}

void legacyPanels()
{
    int choice;
    while (1)
    {
        printf("\n");
        printf("1. Control Panel\n2. Network Connections\n3. Power Panel\n4. Sound Settings\n5. System Properties\n6. User Accounts\n7. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cmd /c control");
            break;
        case 2:
            system("cmd /c ncpa.cpl");
            break;
        case 3:
            system("cmd /c powercfg.cpl");
            break;
        case 4:
            system("cmd /c mmsys.cpl");
            break;
        case 5:
            system("cmd /c sysdm.cpl");
            break;
        case 6:
            system("cmd /c 'control userpasswords2'");
            break;
        case 7:
            return;
        default:
            printf("Invalid Choice");
            break;
        }
    }
}