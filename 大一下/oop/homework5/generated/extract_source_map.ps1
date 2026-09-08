$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

$src = Join-Path (Get-Location) "generated/source.doc"
$png = Join-Path (Get-Location) "generated/source_map.png"

$word = New-Object -ComObject Word.Application
$word.Visible = $false
$word.DisplayAlerts = 0
$word.AutomationSecurity = 3

try {
  $doc = $word.Documents.OpenNoRepairDialog($src, $false, $true, $false, "", "", $false, "", "", 0, 65001, $false, $false, 0, $true)
  $inlineShape = $doc.InlineShapes.Item(1)
  $inlineShape.Range.Select()
  $word.Selection.CopyAsPicture()
  Start-Sleep -Milliseconds 1000
  $image = [System.Windows.Forms.Clipboard]::GetImage()
  if ($null -eq $image) {
    throw "Clipboard image is null"
  }
  $image.Save($png, [System.Drawing.Imaging.ImageFormat]::Png)
  $doc.Close($false)
}
finally {
  $word.Quit()
}

Get-Item -LiteralPath $png | Select-Object FullName,Length
