param(
    [Parameter(Mandatory = $true)][string]$InputDocx,
    [Parameter(Mandatory = $true)][string]$OutputDocx
)

$ErrorActionPreference = "Stop"

$wdLineSpaceExactly = 4
$wdStatisticPages = 2

function Set-TextFrameCompact($shape, [double]$fontSize) {
    if ($shape.TextFrame.HasText -ne 0) {
        $shape.TextFrame.MarginTop = 0
        $shape.TextFrame.MarginBottom = 0
        $shape.TextFrame.MarginLeft = 1.5
        $shape.TextFrame.MarginRight = 1.5
        $shape.TextFrame.TextRange.ParagraphFormat.LineSpacingRule = $wdLineSpaceExactly
        $shape.TextFrame.TextRange.ParagraphFormat.LineSpacing = 10
        $shape.TextFrame.TextRange.ParagraphFormat.SpaceBefore = 0
        $shape.TextFrame.TextRange.ParagraphFormat.SpaceAfter = 0
        $shape.TextFrame.TextRange.Font.Size = $fontSize
    }
}

$word = New-Object -ComObject Word.Application
$word.Visible = $false
$word.DisplayAlerts = 0

try {
    $doc = $word.Documents.Open($InputDocx, $false, $false)
    try {
        # Keep the document's original paper size. Only remove vertical margins
        # that were already effectively zero in the source map.
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

        $emergencyShapes = @()

        foreach ($shape in $doc.Shapes) {
            $top = [double]$shape.Top
            $height = [double]$shape.Height
            $left = [double]$shape.Left

            try {
                if ($shape.TextFrame.HasText -ne 0) {
                    Set-TextFrameCompact $shape 7.2
                }
            }
            catch {
            }

            # Top diagnosis node.
            if (($top -ge 25) -and ($top -le 40) -and ($height -lt 40)) {
                $shape.Top = 28
            }

            # Clinical manifestations row.
            if (($top -ge 62) -and ($top -le 75) -and ($height -gt 150)) {
                $shape.Top = 48
                $shape.Height = 140
            }

            # Disease-name boxes between row 1 and row 2.
            if (($top -ge 260) -and ($top -le 273) -and ($height -lt 30) -and ($left -gt -10)) {
                $shape.Top = 196
                $shape.Height = 18
                try { Set-TextFrameCompact $shape 7.0 } catch {}
            }

            # Cause row.
            if (($top -ge 292) -and ($top -le 303) -and ($height -gt 80) -and ($height -lt 120)) {
                $shape.Top = 230
                $shape.Height = 76
            }

            # Prevention row.
            if (($top -ge 392) -and ($top -le 405) -and ($height -gt 120)) {
                $shape.Top = 326
                $shape.Height = 90
            }

            # Emergency handling row: it originally starts a second page and
            # appears as very high text boxes near the top of that page.
            if (($top -lt 55) -and ($height -gt 120) -and ($left -gt 0)) {
                $emergencyShapes += $shape
            }

            # Left-side row labels.
            if (($left -lt -40) -and ($height -lt 30)) {
                if (($top -ge 130) -and ($top -le 150)) { $shape.Top = 118 }
                elseif (($top -ge 265) -and ($top -le 275)) { $shape.Top = 196 }
                elseif (($top -ge 335) -and ($top -le 350)) { $shape.Top = 264 }
                elseif (($top -ge 445) -and ($top -le 458)) { $shape.Top = 360 }
                elseif (($top -ge 85) -and ($top -le 105)) { $shape.Top = 486 }
            }

            # Connector arrows/lines.
            if (($shape.Width -lt 3) -and ($height -lt 40)) {
                if (($top -ge 55) -and ($top -le 65)) { $shape.Top = 44 }
                elseif (($top -ge 252) -and ($top -le 270)) { $shape.Top = 188 }
                elseif (($top -ge 280) -and ($top -le 292)) { $shape.Top = 214 }
                elseif (($top -ge 390) -and ($top -le 405)) { $shape.Top = 306 }
            }
        }

        # Reflow emergency boxes along the bottom. The low-glucose box gets
        # extra width because it contains the longest emergency-treatment text.
        $emergencyShapes = $emergencyShapes | Sort-Object Left
        $layout = @(
            @{ Left = 10;  Width = 73;  Height = 132; Font = 6.6 },
            @{ Left = 88;  Width = 73;  Height = 132; Font = 6.6 },
            @{ Left = 166; Width = 155; Height = 148; Font = 6.3 },
            @{ Left = 326; Width = 78;  Height = 132; Font = 6.6 },
            @{ Left = 410; Width = 72;  Height = 132; Font = 6.6 },
            @{ Left = 488; Width = 72;  Height = 132; Font = 6.6 },
            @{ Left = 566; Width = 76;  Height = 132; Font = 6.6 },
            @{ Left = 648; Width = 76;  Height = 132; Font = 6.6 },
            @{ Left = 730; Width = 76;  Height = 148; Font = 6.3 }
        )

        for ($i = 0; $i -lt [Math]::Min($emergencyShapes.Count, $layout.Count); $i++) {
            $shape = $emergencyShapes[$i]
            $shape.Left = $layout[$i].Left
            $shape.Top = 430
            $shape.Width = $layout[$i].Width
            $shape.Height = $layout[$i].Height
            try { Set-TextFrameCompact $shape $layout[$i].Font } catch {}
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
