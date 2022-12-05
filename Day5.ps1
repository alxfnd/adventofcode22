$Stack = Get-Content .\22\Day5Stack.txt
$StacksProp = [ordered]@{
    1 = ""
    2 = ""
    3 = ""
    4 = ""
    5 = ""
    6 = ""
    7 = ""
    8 = ""
    9 = ""
}
$AllStacks = New-Object psobject -Property $StacksProp
$SecondStacks = New-Object psobject -Property $StacksProp
foreach ($line in $Stack) {
    for ($i = 0; $i -lt $line.length; $i++) {
        if ($line[$i] -match '[A-Z]') {
            $StackNumber = (($i + 3) / 4)
            $AllStacks.$StackNumber = [string](($AllStacks.$StackNumber)+$line[$i])
            $SecondStacks.$StackNumber = [string](($SecondStacks.$StackNumber)+$line[$i])
        }
    }
}

Function MoveCrate {
    param(
        $from,
        $to
    )
    $AllStacks.$to = [string](($AllStacks.$from)[0]+$AllStacks.$to)
    $AllStacks.$from = [string]($AllStacks.$from).Remove(0,1)
}

$Instructions = Get-Content .\22\Day5.txt
foreach ($line in $Instructions) {
    $line = $line.Split(" ")
    [int]$moves = $line[1]
    [int]$from = $line[3]
    [int]$to = $line[5]
    $Count = 0
    while ($Count -lt $moves) {
        MoveCrate -from $from -to $to
        $Count++
    }
}

Write-Host "Question 1 answer is: " -NoNewline
for ($i = 1; $i -lt 10; $i++) {
    Write-Host $AllStacks.$i[0] -NoNewline
}
Write-Host

Function MoveCrate9001 {
    param(
        $from,
        $to,
        $index
    )
    $SecondStacks.$to = [string](($SecondStacks.$from)[$index - 1]+$SecondStacks.$to)
    $SecondStacks.$from = [string]($SecondStacks.$from).Remove(($index - 1),1)
}

$Instructions = Get-Content .\22\Day5.txt
foreach ($line in $Instructions) {
    $line = $line.Split(" ")
    [int]$moves = $line[1]
    [int]$from = $line[3]
    [int]$to = $line[5]
    $Count = $moves
    while ($Count -gt 0) {
        MoveCrate9001 -from $from -to $to -index $Count
        $Count--
    }
}
Write-Host "Question 2 answer is: " -NoNewline
for ($i = 1; $i -lt 10; $i++) {
    Write-Host $SecondStacks.$i[0] -NoNewline
}
Write-Host
