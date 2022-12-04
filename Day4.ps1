$Advent = Get-Content .\Day4.txt
$Overlaps = 0;
$NoOverlaps = 0;
foreach ($line in $Advent) {
    $line = $line.replace(",","-").split("-")
    if ([int]$line[0] -le [int]$line[2] -and [int]$line[1] -ge [int]$line[3]) {
        $Overlaps++
    }elseif ([int]$line[0] -ge [int]$line[2] -and [int]$line[1] -le [int]$line[3]) {
        $Overlaps++
    }elseif ([int]$line[0] -gt [int]$line[3] -or [int]$line[1] -lt [int]$line[2]) {
        $NoOverlaps++
    }
}
"Question 1 answer is: $Overlaps"
"Question 2 answer is: "+[string]($Advent.Count - $NoOverlaps)
