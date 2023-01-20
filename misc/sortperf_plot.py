"""Plot the results of the `sortpref` binary.

Expects a `sortperf` executable in the current directory.
Writes image to `misc/out.svg`.

`pip install seaborn` should be enough to install this script's dependencies.

Notes:
  > By default, printf buffers its output, but the output is flushed on newline
  > or if a read occurs when the output is directed to a terminal.
  > When the output is directed to a file or a pipe,
  > the actual output only occurs when the buffer is full.
"""
from io import StringIO
from subprocess import Popen, PIPE, STDOUT

import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns


def main():
    buf = StringIO()
    with Popen("./sortperf", stdout=PIPE, stderr=STDOUT, bufsize=1, text=True) as proc:
        for line in proc.stdout:
            print(line, end="")
            buf.write(line)
    datasets = buf.getvalue().split("\n\n")

    df = pd.DataFrame()
    for dataset in datasets[:-1]:
        algo, *table = dataset.split("\n")
        tmp = pd.read_fwf(StringIO("\n".join(table)))
        tmp["algorithm"] = algo
        df = pd.concat([df, tmp])

    df = df.melt(
        id_vars=["algorithm", "i"],
        value_vars=[x for x in df.columns if x.endswith("sort")],
        var_name="arrangement",
        value_name="time",
    )

    with plt.xkcd():
        # fiddle with some of the xkcd defaults
        # see https://matplotlib.org/3.1.1/_modules/matplotlib/pyplot.html#xkcd
        mpl.rcParams.update(
            {
                "path.effects": [
                    mpl.patheffects.withStroke(linewidth=2.5, foreground="w")
                ],
                "lines.linewidth": 2.25,
            }
        )

        g = sns.relplot(
            data=df,
            x="i",
            y="time",
            hue="algorithm",
            col="arrangement",
            kind="line",
            height=2.5,
            aspect=1.5,
            col_wrap=3,
        )
        g.set_axis_labels("Array size (2^N)", "Time (s)")
        g.set_titles("{col_name}")

    g.savefig("misc/out.svg")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
