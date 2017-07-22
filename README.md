# similitude

![](https://i.stack.imgur.com/KFbN7.png)

## Description

`similitude` compares edit distances using [Levenshtein's
Distance](https://en.wikipedia.org/wiki/Levenshtein_distance).

### Algorithmic complexity

Given a string of length *m* and a string of length *n*, `similitude` runs in
O(*m*,*n*) time and O(min(*m*,*n*)) space.

## Installation

```sh
make
```

## Usage

`similitude` will compare lines in two files and print the edit distances to
`stdout`.

## Example

```sh
$ ./bin/similitude test/foo test/bar
19958 S BAKERS FERRY RD, 2387 PIMLICO DR, 20
19958 S BAKERS FERRY RD, 1706 22ND AVE, 20
19958 S BAKERS FERRY RD, 512 SE BASELINE ST, 16
etc.
```

## Python extension

### Requirements

Python version 3.6 or greater (due to *f-strings*).

### Installation

```sh
pip install -r requirements.txt
```

### Usage

`similitude.py` will compare lines in `arg[1]` and`arg[2]` and load the
edit distances into a [pandas](https://pandas.pydata.org) dataframe.

### Example

```sh
$ python3 similitude.py test/foo test/bar
Pivot table:
                                                         distance
source             target
0104 SW LANE ST     1 CONDOLEA DR                              12
                    1 JEFFERSON PKWY  APT 266                  20
                    100 SW 195TH AVE SPC 13                    14
...                                                           ...
9906 SE REEDWAY ST  9510 S WILDCAT RD                          11
                    9517 SE 75TH AVE                           12
                    9532 SW WHITFORD LN                        14

[2000000 rows x 1 columns]
```
