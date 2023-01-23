#include <stdio.h>
#include <stdlib.h>

void essentialTweeks()
{
    int choice;
    while (1)
    {
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
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\disableWifiSense.ps1");
            break;
        case 3:
            system("powershell Write-Host 'Disabling Activity History'");
            system("powershell Set-ItemProperty -Path 'HKLM:\\SOFTWARE\\Policies\\Microsoft\\Windows\\System' -Name 'EnableActivityFeed' -Type DWord -Value 0");
            system("powershell  Set-ItemProperty -Path 'HKLM:\\SOFTWARE\\Policies\\Microsoft\\Windows\\System' -Name 'PublishUserActivities' -Type DWord -Value 0");
            system("powershell Set-ItemProperty -Path 'HKLM:\\SOFTWARE\\Policies\\Microsoft\\Windows\\System' -Name 'UploadUserActivities' -Type DWord -Value 0");
            break;
        case 4:
            system("powershell Write-Host 'Delete Temp Files'");
            system("powershell Get-ChildItem -Path 'C:\\Windows\\Temp' *.* -Recurse | Remove-Item -Force -Recurse -ErrorAction SilentlyContinue");
            system("powershell Get-ChildItem -Path $env:TEMP *.* -Recurse | Remove-Item -Force -Recurse -ErrorAction SilentlyContinue");
            system("powershell Write-Host '======================================='");
            system("powershell Write-Host '--- Cleaned following folders:'");
            system("powershell Write-Host '--- C:\\Windows\\Temp'");
            system("powershell Write-Host '--- '$env:TEMP");
            system("powershell Write-Host '======================================='");
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
            system("powershell Remove-Item -Path 'HKCU:\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\StorageSense\\Parameters\\StoragePolicy' -Recurse -ErrorAction SilentlyContinue");
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
        printf("1. Show File Extension\n2. Set Display For Performance\n3. Set Time to UTC\n4. Remove Cortana\n5. Disable Notification\n6. Disable TPM Check\n7. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("powershell  Write-Host 'Showing known file extensions...'");
            system("powershell Set-ItemProperty -Path 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced' -Name 'HideFileExt' -Type DWord -Value 0");
            break;
        case 2:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\displayPerformance.ps1");
            break;
        case 3:
            system("powershell Write-Host 'Setting BIOS time to UTC...'");
            system("powershell Set-ItemProperty -Path 'HKLM:\\SYSTEM\\CurrentControlSet\\Control\\TimeZoneInformation' -Name 'RealTimeIsUniversal' -Type DWord -Value 1");
            break;
        case 4:
            system("powershell   Write-Host 'Removing Cortana...'");
            system("powershell Get-AppxPackage -allusers Microsoft.549981C3F5F10 | Remove-AppxPackage");
            break;
        case 5:
            system("powershell Write-Host 'Disabling Notifications and Action Center...'");
            system("powershell New-Item -Path 'HKCU:\\Software\\Policies\\Microsoft\\Windows' -Name 'Explorer' -force");
            system("powershell  New-ItemProperty -Path 'HKCU:\\Software\\Policies\\Microsoft\\Windows\\Explorer' -Name 'DisableNotificationCenter' -PropertyType 'DWord' -Value 1");
            system("powershell  New-ItemProperty -Path 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\PushNotifications' -Name 'ToastEnabled' -PropertyType 'DWord' -Value 0 -force");
            break;
        case 6:
            system("powershell -ExecutionPolicy Bypass -File .\\scripts\\tweeks\\disableTPM.ps1");
            break;
        case 7:
            return;
        default:
            printf("Invalid choice");
            break;
        }
    }
}