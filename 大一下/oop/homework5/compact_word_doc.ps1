param(
    [Parameter(Mandatory = $true)][string]$InputDocx,
    [Parameter(Mandatory = $true)][string]$OutputDocx
)

$ErrorActionPreference = "Stop"

$wdLineSpaceExactly = 4
$wdStatisticPages = 2
$word = New-Object -ComObject Word.Application
$word.Visible = $false
$word.DisplayAlerts = 0

try {
    $doc = $word.Documents.Open($InputDocx, $false, $false)
    try {
        foreach ($section in $doc.Sections) {
            $section.PageSetup.TopMargin = 0
            $section.PageSetup.BottomMargin = 0
        }

        foreach ($paragraph in $doc.Paragraphs) {
            $text = $paragraph.Range.Text
            $clean = ($text -replace [string][char]13, "" -replace [string][char]7, "").Trim()
            $paragraph.Format.LineSpacingRule = $wdLineSpaceExactly
            $paragraph.Format.SpaceBefore = 0
            $paragraph.Format.SpaceAfter = 0
            if ($clean.Length -eq 0) {
                $paragraph.Format.LineSpacing = 1
                $paragraph.Range.Font.Size = 1
            }
            else {
                $paragraph.Format.LineSpacing = 10
            }
        }

        foreach ($shape in $doc.Shapes) {
            try {
                if ($shape.TextFrame.HasText -ne 0) {
                    $shape.TextFrame.MarginTop = 0
                    $shape.TextFrame.MarginBottom = 0
                    $shape.TextFrame.MarginLeft = 2
                    $shape.TextFrame.MarginRight = 2
                    $shape.TextFrame.TextRange.ParagraphFormat.LineSpacingRule = $wdLineSpaceExactly
                    $shape.TextFrame.TextRange.ParagraphFormat.LineSpacing = 10
                    $shape.TextFrame.TextRange.ParagraphFormat.SpaceBefore = 0
                    $shape.TextFrame.TextRange.ParagraphFormat.SpaceAfter = 0
                }
            }
            catch {
            }
        }

        foreach ($shape in $doc.InlineShapes) {
            try {
                $shape.Range.ParagraphFormat.LineSpacingRule = $wdLineSpaceExactly
                $shape.Range.ParagraphFormat.LineSpacing = 10
                $shape.Range.ParagraphFormat.SpaceBefore = 0
                $shape.Range.ParagraphFormat.SpaceAfter = 0
            }
            catch {
            }
        }

        $doc.Repaginate()
        $pages = $doc.ComputeStatistics($wdStatisticPages)
        $doc.SaveAs2($OutputDocx, 16)
        Write-Output "pages=$pages"
        Write-Output "docx=$OutputDocx"
    }
    finally {
        $doc.Close($false)
    }
}
finally {
    $word.Quit()
}
