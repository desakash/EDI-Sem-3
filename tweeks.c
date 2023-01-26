#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *getFromcsv(char *key)
{
    FILE *fp;
    char row[1000];
    char *found;
    int flag = 0;
    fp = fopen("locations.csv", "r");

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
    printf("\nmain: %s\n", main);
    system(main);
}

void essentialTweeks()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("1. Create Restore Point\n2. Disable Wifi Sense\n3. Disable Activity History\n4. Delete Temporary Files\n5. Run Disk Cleanup\n6. Disable Location Tracking\n7. Disable Storage Sense\n8. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("powershell Write-Host 'Creating Restore Point in case something bad happens'");
            system("powershell Enable-ComputerRestore -Drive '$env:SystemDrive'");
            system("powershell Checkpoint-Computer -Description 'Restore Point' -RestorePointType 'MODIFY_SETTINGS'");
            printf("\n");
            break;
        case 2:
            system("powershell -ExecutionPolicy Bypass -File '.\\scripts\\tweeks\\disableWifiSense.ps1'");
            printf("\n");
            break;
        case 3:
            system("powershell Write-Host 'Disabling Activity History'");
            setRegistry("EnableActivityFeed", 0);
            setRegistry("PublishUserActivities", 0);
            setRegistry("UploadUserActivities", 0);
            system("powershell Write-Host 'Disabled Activity History'");
            printf("\n");
            break;
        case 4:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\deleteTempFiles.ps1");
            printf("\n");
            break;
        case 5:
            system("powershell Write-Host 'Running Disk Cleanup on Drive C:...'");
            system("powershell cmd /c cleanmgr.exe /d C: /VERYLOWDISK");
            printf("\n");
            break;
        case 6:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\disableLocationTracking.ps1");
            printf("\n");
            break;
        case 7:
            system("powershell Write-Host 'Disabling Storage Sense'");
            char *path = getFromcsv("StoragePolicy");
            char main[1000] = "powershell Remove-Item -Path '";
            strcat(main, path);
            strcat(main, "' -Recurse -ErrorAction SilentlyContinue");
            system(main);
            printf("\n");
            break;
        case 8:
            printf("\n");
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}

void miscTweeks()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("1. Show File Extension\n2. Set Display For Performance\n3. Set Time to UTC\n4. Remove Cortana\n5. Disable Real Time Monitoring\n6. Disable notifications\n7. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("powershell  Write-Host 'Showing known file extensions...'");
            setRegistry("HideFileExt", 0);
            break;
        case 2:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\displayPerformance.ps1");
            break;
        case 3:
            system("powershell Write-Host 'Setting BIOS time to UTC...'");
            setRegistry("RealTimeIsUniversal", 1);
            break;
        case 4:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\removeCortana.ps1");
            break;
        case 5:
            system("powershell Write-Host 'Disabling Real Time Monitoring...'");
            system("powershell Set-MpPreference -DisableRealtimeMonitoring $True");
            break;
        case 6:
            system("powershell Write-Host 'Disabling Notifications...'");
            char *path = getFromcsv("Explorer");
            char main[1000] = "powershell New-Item -Path '";
            strcat(main, path);
            strcat(main, "' -Name 'Explorer' -force");
            system(main);
            char main2[1000] = "powershell New-ItemProperty -Path '";
            path = getFromcsv("DisableNotificationCenter");
            strcat(main2, path);
            strcat(main2, "' -Name 'DisableNotificationCenter' -PropertyType 'DWord' -Value 1");
            system(main2);
            break;
        case 7:
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}

void changeDNS()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("1. Google\n2. Cloud Flare\n3. Open DNS\n4. Cancel\n");
        printf("Select DNS Server: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\changeDNS.ps1 Google");
            break;
        case 2:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\changeDNS.ps1 Cloud");
            break;
        case 3:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\changeDNS.ps1 Open");
            break;
        case 4:
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}