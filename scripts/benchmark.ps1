$commands = @(
    '.\xsort --bubble',
    '.\xsort --cocktail',
    '.\xsort --insertion',
    '.\xsort --merge',
    '.\xsort --quick',
    '.\xsort --selection',
    '.\xsort --shell'
)

$N = 1..10 | ForEach-Object {$_ * 1000}

foreach ($i in $N) {
    Get-Random -Minimum ([int32]::MinValue) -Maximum ([int32]::MaxValue) -Count $i > "rand-$i.txt"
    hyperfine --warmup 1 `
              --min-runs 2 `
              --export-json "bench-$i.json" `
              $commands.ForEach({"$_ rand-$i.txt"})
    Remove-Item "rand-$i.txt"
}

jq --slurp --raw-output -f ($PSScriptRoot + '\filter.jq') (Get-Item bench-*.json) > 'data.csv'
Remove-Item "bench-*.json"

gnuplot -e "
    set terminal svg background rgb 'white';
    set encoding default;
    set datafile separator comma;
    set title 'Sorting algorithm runtime comparison';
    set xlabel '# of elements (N)';
    set ylabel 'Runtime (seconds)';
    set key left top;
    set style data line;
    plot for [i=2:*] 'data.csv' using 1:i title columnheader linewidth 3
    " > out.svg
Remove-Item 'data.csv'
