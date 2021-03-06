# sort

A study of sorting algorithms using C - over 15 algorithms applied exclusively
to `int32_t`.

## Motivation

- obtain an understanding of sorting algorithms beyond Wikipedia's initial paragraph
- take a C refresher by going through (most of) the
  [Modern C](https://modernc.gforge.inria.fr/) book
- mess around with [Ninja](https://ninja-build.org/) for simple build tasks

## Usage

The `xsort` program exposes the available algorithms:

```text
xsort 0.1.0, a study of sorting algorithms
Usage:
  xsort --bubble [FILE]
  xsort --cocktail [FILE]
  xsort --comb [FILE]
  xsort --cycle [FILE]
  xsort --flash [FILE]
  xsort --gnome [FILE]
  xsort --heap [FILE]
  xsort --insertion [FILE]
  xsort --intro [FILE]
  xsort --merge [FILE]
  xsort --odd-even [FILE]
  xsort --quick [FILE]
  xsort --selection [FILE]
  xsort --shell [FILE]
  xsort --stooge [FILE]
  xsort --strand [FILE]
  xsort --weak-heap [FILE]
  xsort -h | --help
Description:
  Write sorted integers to stdout.
  With no FILE, read from stdin.
```

## Benchmark

A rather simple and unscientific benchmark comparison is done with
the `sortperf` program;
it's a straight rip-off of CPython's `sortperf.py`,
which has been used to back up discussions to changes to the
standard library's sorting algorithm.

Visualisation limited to _efficient_ algorithms.

![Sorting algorithms runtime comparison](assets/out.svg)

```text
Key:
  *sort: random data
  \sort: descending data
  /sort: ascending data
  3sort: ascending, then 3 random exchanges
  +sort: ascending, then 10 random at the end
  %sort: ascending, then randomly replace 1% of the elements w/ random values
  ~sort: many duplicates
  =sort: all equal
  !sort: worst case scenario (for a specific quicksort implementation)
```

## Useful references

- [timsort discussion (Python's mailing list)](https://mail.python.org/pipermail/python-dev/2002-July/026837.html)
- [sortperf.py (source)](https://github.com/python/cpython/blob/master/Lib/test/sortperf.py)
- [memory handling / growth factor discussion (facebook/folly docs)](https://github.com/facebook/folly/blob/master/folly/docs/FBVector.md#memory-handling)
- [How to C in 2016 (blog post)](https://matt.sh/howto-c)
