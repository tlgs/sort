# sort

A study of sorting algorithms using C.

## Motivation

- obtain an understanding of sorting algorithms beyond Wikipedia's initial paragraph
- take a C refresher by going through (most of) the
  [Modern C](https://modernc.gforge.inria.fr/) book
- mess around with [Ninja](https://ninja-build.org/) for simple build tasks

## Benchmark

A rather simple and unscientific benchmark comparison is done with
the `sortperf.c` program.
It is a straight rip-off of CPython's
[sortperf.py](https://github.com/python/cpython/blob/master/Lib/test/sortperf.py),
which has been used to back up discussions to changes to the standard's
library sorting algorithm.

## Usage

The focus is on the algorithms and not on _general functionality_;
there is only an interface for `int`.

For testing convenience, the program `xsort` exposes the different available algorithms:

```console
$ .\xsort --help
xsort 0.1.0, a study of sorting algorithms
Sort lines of integers

Usage:
  xsort --bubble [FILE]
  xsort --cocktail [FILE]
  xsort --comb [FILE]
  xsort --insertion [FILE]
  xsort --merge [FILE]
  xsort --quick [FILE]
  xsort --selection [FILE]
  xsort --shell [FILE]

Description:
  Write sorted integers to stdout.
  With no FILE, read from stdin.
```

## Useful references

- timsort discussion
  ([Python's mailing list](https://mail.python.org/pipermail/python-dev/2002-July/026837.html))
- sortperf.py ([source](https://github.com/python/cpython/blob/master/Lib/test/sortperf.py))
