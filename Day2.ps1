# If you order Rock/Paper/Scissors in a loop you'll find a pattern emerge
# These two arrays make use of that pattern, so we can loop through an array depending on Rock/Paper/Scissors
<#
Here's a little versus table, you can see the number's pattern.
  RPSRPSRPS
P 036036036
S 603603603
R 360360360

Knowing this, you can loop through win/draw/loss scores in an array and just change
your starting position based on what Rock/Paper/Scissors is chosen
#>
$WinArray = @(6,3,0,6,3)
$PlayArray = @("X","Z","Y","X","Z","Y")

# PlayValues/Play object determines starting position for Question Part 1
$PlayValues = @{
    X = 1
    Y = 0
    Z = 2
}
$Play = New-Object -TypeName psobject -Property $PlayValues

# WinValues/Win object determines starting position for Question Part 2
$WinValues = @{
    X = 0
    Y = 2
    Z = 1
}
$Win = New-Object -TypeName psobject -Property $WinValues

# Get Puzzle Content
$Advent = Get-Content .\Day2.txt

<# The below function "DeterminePlay" is for Question Part 2
It takes the opponents choice A/B/C - and whether we Win/Draw/Loss
    It determines where to start in the second PlayArray..
    It get the index value from the Win object (what we add to determine what we play to Win/Draw/Lose)
    Then returns the "Play" (Rock/Paper/Scissors - X/Y/Z)

I do this to recycle the original calculation function to answer Part 1.
Instead if re-writing how to calculate the new puzzle code, we just convert the new puzzle code into the original puzzle code.
New Puzzle Code is X/Y/Z = Lose/Draw/Win
Old Puzzle Code is X/Y/Z = Rock/Paper/Scissors
#>
Function DeterminePlay {
    param(
        $Opponent,
        $Outcome
    )
    switch ($Opponent) {
        "B" { $ArrayStart = 0 }
        "A" { $ArrayStart = 1 }
        "C" { $ArrayStart = 2 }
    }
    $index = $Win.$Outcome
    switch ($Outcome) {
        "X" { return $PlayArray[$index + $ArrayStart] }
        "Y" { return $PlayArray[$index + $ArrayStart] }
        "Z" { return $PlayArray[$index + $ArrayStart] }
    }
}

<#
The below function here is our main one for both parts. - There is a quick parameter to determine if we're using old or new puzzle code called $Part2
#>
Function Calculate {
    param(
        $Part2
    )
    # Set total to 0
    $Total = 0
    # Run through the puzzle code, putting the variables into $line
    foreach ($line in $Advent) {
        # Separate $line so we can get both columns into $line[0] and $line[1]
        $line = $line.split(" ")
        # The index variable is what we use to determine the score, similar to the previous function.
        # We decide what's being played, based on that we decide where we start in the "score" ($WinArray) array.
        $index = $Play.($line[1])
        # If this is Part2, then translate the new puzzle code into old puzzle code and create the new index value
        if ($Part2 -eq 1) {
            $Shape = (DeterminePlay -Opponent $line[0] -Outcome $line[1])
            $index = $Play.$Shape
        }else{
            $Shape = $line[1]
        }
        # Use the Shape (our play in the code) to get our play score
        switch ($Shape) {
            "X" { $Total += 1 }
            "Y" { $Total += 2 }
            "Z" { $Total += 3 }
        }
        # Determine our win result based on the opponents play and add it to our Total score
        switch ($line[0]) {
            "A" { $Total += $WinArray[$index] }
            "B" { $Total += $WinArray[$index + 1] }
            "C" { $Total += $WinArray[$index + 2] }
        }
    }
    return $Total
}

# Below just runs through the core function twice, determining how the puzzle code is interpreted
Write-Host "Question 1 answer is: "
Calculate -Part2 0
Write-Host "Question 2 answer is: "
Calculate -Part2 1
