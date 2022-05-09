[![alzaynou's 42 n-puzzle Score](https://badge42.vercel.app/api/v2/cl2mjk5oo009709i7yb0upwvb/project/2407577)](https://github.com/alizaynoune)
# n_puzzle
The goal of this project is to solve the N-puzzle ("taquin" in French) game using the IDA*
search algorithm or one of its variants.

# Install

```
git clone git@github.com:alizaynoune/n_puzzle_1337.git
cd n_puzzle_1337
make
python2 ./n-puzzle.py -s 4 > map
./n_puzzle map | python ./visul/visul.py
```

# Usege
* ./n_puzzle `file` `algorithme` `distance` | python ./visul/visul.py
## algorithme
* -astar `A*`
* -greedy `greedy shearch`
## distance
* -m `manhattan distance`
* -e `euclidean distance`
* -i `inverse distance`
* -mp `missed place distance`
## file
```
# This puzzle is solvable
4 # map size
 6  0  7 11
 9  1  3  4
13 10 14  5
 2 12 15  8
```

### keyboard usage
* n `next step`
* r `run app`
* p `pause app`
* q `quite`

# review
![](https://github.com/alizaynoune/n_puzzle_1337/blob/main/images/n_puzzle.gif?raw=true)

