$Advent = Get-Content ".\22\Day10.txt"
$Cycles = 1
$Register = 1
$SolutionArray = @()
$StringOutput = ""
$Row = 0
Function CheckCycles($Cycles)
{
    if (($Cycles -eq ($Global:Register + $Global:Row)) -or ($Cycles -eq (($Global:Register + 1) + $Global:Row)) -or ($Cycles -eq (($Global:Register + 2) + $Global:Row)) ) {
        $Global:StringOutput += "#"
    }else{
        $Global:StringOutput += "."
    }
    switch ($Cycles)
    {
        20 { $Global:SolutionArray += ($Cycles * $Global:Register) }
        40 { $Global:Row = 40 }
        60 { $Global:SolutionArray += ($Cycles * $Global:Register) }
        80 { $Global:Row = 80 }
        100 { $Global:SolutionArray += ($Cycles * $Global:Register) }
        120 { $Global:Row = 120 }
        140 { $Global:SolutionArray += ($Cycles * $Global:Register) }
        160 { $Global:Row = 160 }
        180 { $Global:SolutionArray += ($Cycles * $Global:Register) }
        200 { $Global:Row = 200 }
        220 { $Global:SolutionArray += ($Cycles * $Global:Register) }
    }
}
foreach($line in $Advent) {
    $line = $line.split(" ")
    if ($line[0] -eq "addx") {
        CheckCycles($Cycles)
        $Cycles++
        CheckCycles($Cycles)
        $Register += [int]$line[1]
        $Cycles++
    }else{
        CheckCycles($Cycles)
        $Cycles++
    }
}

$Solution = 0
for ($i = 0; $i -lt $SolutionArray.Count; $i++) {
    $Solution += $SolutionArray[$i]
}
$Solution
$2Count = 0
while ($2Count -lt $Cycles) {
    if ((($2Count + 1) % 40) -ne 0 -or $2Count -eq 0) {
        Write-Host $StringOutput[$2Count] -NoNewline
    }else{
        Write-Host $StringOutput[$2Count]
    }
    $2Count++
}
