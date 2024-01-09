
# Local path to the files
$localPath = "C:\Users\Administrateur\Documents\Learn_Batch_Script\pts"
$xmlFile = Join-Path -Path $localPath -ChildPath "application.xml"
$backupFolder = Join-Path -Path $localPath -ChildPath "Backup_ApplicationXML"

try {
    # Create backup folder if not exist
    if (-not (Test-Path -Path $backupFolder -PathType Container)) {
        New-Item -Path $backupFolder -ItemType Directory
    }

    # Read XML content
    $xmlContent = Get-Content -Path $xmlFile

    # Search for target line in XML
    $targetLine = "<Data key=`"TrialSerialNumber`">"
    $lineIndex = $xmlContent | Select-String -Pattern $targetLine | Select-Object -ExpandProperty LineNumber

    if ($lineIndex) {
        $cleanedLine = $xmlContent[$lineIndex - 1] -replace '.*<Data key="TrialSerialNumber">', '' -replace '</Data>.*', ''
        Write-Host "Current trial serial number: [31m$cleanedLine[0m"

        $new_serial = [System.Numerics.BigInteger]::Parse($cleanedLine) + 1
        Write-Host "Updated trial serial number: [32m$new_serial[0m"

        # Backup original XML content
        $xmlBackup = $xmlContent.Clone()

        # Update XML content with new serial
        $xmlContent[$lineIndex - 1] = $xmlContent[$lineIndex - 1] -replace "(?<=<Data key=`"TrialSerialNumber`">)[^<]+(?=</Data>)", $new_serial

        # Save modified XML content
        $xmlContent | Set-Content -Path $xmlFile -Force

        # Save original XML content to a backup file
        $backupFileName = Join-Path -Path $backupFolder -ChildPath ("application_" + (Get-Date -Format "yyyyMMddHHmm") + ".xml")
        $xmlBackup | Set-Content -Path $backupFileName
        Write-Host "[36mBackup file created: $backupFileName[0m"
    } else {
        Write-Host "[31mTarget line not found in XML.[0m"
    }
} catch {
    Write-Host "[31mAn error occurred: $_[0m"
}
