<#
A/X = Rock
B/Y = Paper
C/Z = Scissors

Scores:

Shape selected (Column 2)
Rock = 1
Paper = 2
Scissors = 3

Win = 6
Draw = 3
Loss = 0
#>

$Properties = @{
    C = 6
    A = 3
    B = 0
}
$Rock = New-Object -TypeName psobject -Property $Properties

$Properties = @{
    A = 6
    B = 3
    C = 0
}
$Paper = New-Object -TypeName psobject -Property $Properties

$Properties = @{
    B = 6
    C = 3
    A = 0
}
$Scissors = New-Object -TypeName psobject -Property $Properties

$Content = Get-Content C:\users\alexf\Documents\AdventofCode22\Day2.txt
$TotalScore = 0


Function Calculate {
    param(
        $Column1,
        $Column2
    )
    $CurrentScore = 0
    switch ($Column2) {
        X {
            $CurrentScore += 1
            $CurrentScore += $Rock.$Column1
        }
        Y {
            $CurrentScore += 2
            $CurrentScore += $Paper.$Column1
        }
        Z {
            $CurrentScore += 3
            $CurrentScore += $Scissors.$Column1
        }
    }
    return $CurrentScore
}

foreach ($line in $Content) {
    $line = $line.split(" ")
    $TotalScore += Calculate -Column1 $line[0] -Column2 $line[1]
}
Write-Host "Question 1 answer is $TotalScore"

# With the previous function, we knew what we were going to play in the game
# Now we need to determine what play is going to be made, then run the original function again
Function DeterminePlay {
    param(
        $Column1,
        $Column2
    )
    #Column1 = Opponent Play
    #Column2 = How we respond
    #All I'm doing here is converting X,Y,Z from game outcome to what we play
    switch ($Column1) {
        A { #Opponent played Rock
            switch ($Column2) {
                X {$Play = "Z"} #Loss, so play Scissors = Z
                Y {$Play = "X"}
                Z {$Play = "Y"} #Win, so play Paper = Y
            }
        }
        B { #Opponent played Paper
                $Play = $Column2
        }
        C { #Opponent played Scissors
            switch ($Column2) {
                X {$Play = "Y"}
                Y {$Play = "Z"}
                Z {$Play = "X"}
            }
        }
    }
    return $Play
}

$NewScore = 0
foreach ($line in $Content) {
    $line = $line.Split(" ")
    $NewScore += Calculate -Column1 $line[0] -Column2 (DeterminePlay -Column1 $line[0] -Column2 $line[1])
}
Write-Host "Question 2 answer is $NewScore"
