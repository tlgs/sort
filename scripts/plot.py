import sys
from io import StringIO

import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

if __name__ == "__main__":
    datasets = sys.stdin.read().split("\n\n")

    df = pd.DataFrame()
    for dataset in datasets[:-1]:
        algo, *table = dataset.split("\n")
        tmp = pd.read_fwf(StringIO("\n".join(table)))
        tmp["algorithm"] = algo
        df = df.append(tmp)

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

    output = StringIO()
    g.savefig(output, format="svg")
    print(output.getvalue())
