$N = (10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000)

foreach ($i in $N)
{
    python -c "for _ in range($i): print(__import__('random').randint(-2**31, 2**31-1))" > "rand-$i.txt"

    hyperfine --warmup 1 --min-runs 2 `
        ".\xsort --bubble rand-$i.txt" `
        ".\xsort --cocktail rand-$i.txt" `
        ".\xsort --insertion rand-$i.txt" `
        ".\xsort --merge rand-$i.txt" `
        ".\xsort --quick rand-$i.txt" `
        ".\xsort --selection rand-$i.txt" `
        ".\xsort --shell rand-$i.txt" `
        --export-json "bench-$i.json"

    Remove-Item "rand-$i.txt"
}

jq --slurp --raw-output '[.[] | .results[] | {algorithm: (.command | split(\" \") | .[1] | ltrimstr(\"--\")), n: (.command | split(\" \") | .[2] | split(\".\") | .[0] | split(\"-\") | .[1] | tonumber), time: .median}] | group_by(.n) | ([\"n\"] + ([.[] | .[] | .algorithm] | unique)), (.[] | [.[0] | .n] + [.[] | .time]) | join(\",\")' (Get-Item bench-*.json) > data.csv

gnuplot -e "
    set terminal svg background rgb 'white';
    set datafile separator comma;
    set title 'Sorting algorithm runtime comparison';
    set xlabel '# of elements (N)';
    set ylabel 'Runtime (seconds)';
    set key left top;
    set style data line;
    plot for [i=2:*] 'data.csv' using i:xtic(1) title columnheader linewidth 3
    " > out.svg

Remove-Item "bench-*.json", "data.csv"
