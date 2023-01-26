Write-Host "Checking if Winget is Installed..."
if (Test-Path ~\AppData\Local\Microsoft\WindowsApps\winget.exe) {
    Write-Host "Winget Already Installed"
}
else {
    if (((Get-ComputerInfo).WindowsVersion) -lt "1809") {
        Write-Host "Winget is not supported on this version of Windows (Pre-1809)"
    }
    else {
        Write-Host "Winget not found, installing it now."
        Start-Process "ms-appinstaller:?source=https://aka.ms/getwinget"
        $nid = (Get-Process AppInstaller).Id
        Wait-Process -Id $nid
        Write-Host "Winget Installed"
    }
}