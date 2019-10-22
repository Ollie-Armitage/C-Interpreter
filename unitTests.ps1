Get-Content "testFiles/straight-line/literal.txt" | ./mycc.exe > "log.txt"
$a = Get-Content "log.txt" -Tail 1;

if($a -eq "30"){
    echo "Literal Test Passed."
}
else{
    echo "Literal Test Failed. ($a)"
}

Get-Content "testFiles/straight-line/literalArithmetic.txt" | ./mycc.exe > "log.txt"
$a = Get-Content "log.txt" -Tail 1;

if($a -eq "50"){
    echo "Literal Arithmetic Test Passed."
}
else{
    echo "Literal Arithmetic Test Failed. ($a)"
}

Get-Content "testFiles/straight-line/literalComparisons.txt" | ./mycc.exe > "log.txt"
$a = Get-Content "log.txt" -Tail 1;

if($a -eq "true"){
    echo "Literal Comparisons Test Passed."
}
else{
    echo "Literal Comparisons Test Failed. ($a)"
}

Get-Content "testFiles/straight-line/variable.txt" | ./mycc.exe > "log.txt"
$a = Get-Content "log.txt" -Tail 1;

if($a -eq "10"){
    echo "Variable Test Passed."
}
else{
    echo "Variable Test Failed. ($a)"
}

Get-Content "testFiles/straight-line/variableArithmetic.txt" | ./mycc.exe > "log.txt"
$a = Get-Content "log.txt" -Tail 1;

if($a -eq "300"){
    echo "Variable Arithmetic Test Passed."
}
else{
    echo "Variable Arithmetic Test Failed. ($a)"
}

Get-Content "testFiles/straight-line/variableComparisons.txt" | ./mycc.exe > "log.txt"
$a = Get-Content "log.txt" -Tail 1;

if($a -eq "False"){
    echo "Variable Comparisons Test Passed."
}
else{
    echo "Variable Comparisons Test Failed. ($a)"
}