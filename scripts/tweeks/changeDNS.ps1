# read command line arg
$name = $args[0]
$Interfaces = [System.Management.ManagementClass]::new("Win32_NetworkAdapterConfiguration").GetInstances()
If ( $name -eq 'Google' ) { 
    Write-Host "Setting DNS to $name for all connections..."
    $DC = "8.8.8.8"
    $Internet = "8.8.4.4"
    $dns = "$DC", "$Internet"
    $Interfaces.SetDNSServerSearchOrder($dns) | Out-Null
}
If ( $name -eq 'Cloud' ) { 
    Write-Host "Setting DNS to $name Flare for all connections..."
    $DC = "1.1.1.1"
    $Internet = "1.0.0.1"
    $dns = "$DC", "$Internet"
    $Interfaces.SetDNSServerSearchOrder($dns) | Out-Null
}
If ( $name -eq 'Open' ) { 
    Write-Host "Setting DNS to $name DNS for all connections..."
    $DC = "208.67.222.222"
    $Internet = "208.67.220.220"
    $dns = "$DC", "$Internet"
    $Interfaces.SetDNSServerSearchOrder($dns) | Out-Null
}