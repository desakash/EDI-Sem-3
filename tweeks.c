#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"

void essentialTweeks()
{
    int choice;
    while (1)
    {
        printf("\n");
        printf("1. Create Restore Point\n2. Disable Wifi Sense\n3. Disable Activity History\n4. Delete Temporary Files\n5. Run Disk Cleanup\n6. Disable Location Tracking\n7. Disable Storage Sense\n8. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("powershell Write-Host 'Creating Restore Point in case something bad happens'");
            system("powershell Enable-ComputerRestore -Drive '$env:SystemDrive'");
            system("powershell Checkpoint-Computer -Description 'Restore Point' -RestorePointType 'MODIFY_SETTINGS'");
            break;
        case 2:
            system("powershell -ExecutionPolicy Bypass -File '.\\scripts\\tweeks\\disableWifiSense.ps1'");
            break;
        case 3:
            system("powershell Write-Host 'Disabling Activity History'");
            setRegistry("EnableActivityFeed", 0);
            setRegistry("PublishUserActivities", 0);
            setRegistry("UploadUserActivities", 0);
            system("powershell Write-Host 'Disabled Activity History'");
            break;
        case 4:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\deleteTempFiles.ps1");
            break;
        case 5:
            system("powershell Write-Host 'Running Disk Cleanup on Drive C:...'");
            system("powershell cmd /c cleanmgr.exe /d C: /VERYLOWDISK");
            break;
        case 6:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\disableLocationTracking.ps1");
            break;
        case 7:
            system("powershell Write-Host 'Disabling Storage Sense'");
            char *path = getFromcsv("StoragePolicy");
            char main[1000] = "powershell Remove-Item -Path '";
            strcat(main, path);
            strcat(main, "' -Recurse -ErrorAction SilentlyContinue");
            system(main);
            break;
        case 8:
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
        printf("\n");
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
            askRestart();
            break;
        case 4:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\removeCortana.ps1");
            askRestart();
            break;
        case 5:
            system("powershell Write-Host 'Disabling Real Time Monitoring...'");
            system("powershell Set-MpPreference -DisableRealtimeMonitoring $True");
            askRestart();
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
            askRestart();
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
        printf("\n");
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