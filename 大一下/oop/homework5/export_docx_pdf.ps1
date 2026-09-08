param(
    [Parameter(Mandatory = $true)][string]$InputDocx,
    [Parameter(Mandatory = $true)][string]$OutputPdf
)

$ErrorActionPreference = "Stop"
$word = New-Object -ComObject Word.Application
$word.Visible = $false
$word.DisplayAlerts = 0
try {
    $doc = $word.Documents.Open($InputDocx, $false, $true)
    try {
        $doc.Repaginate()
        $pages = $doc.ComputeStatistics(2)
        $doc.ExportAsFixedFormat($OutputPdf, 17)
        Write-Output "pages=$pages"
        Write-Output "pdf=$OutputPdf"
    }
    finally {
        $doc.Close($false)
    }
}
finally {
    $word.Quit()
}
