# rushhour_solver

AI for rush hour. Solves rushhour puzzles using A* algorithm. Implemented in Python.

## Instructions

To run the python solver:

```bash
# python 3.6+
python src/solve.py
```

To run the rust solver:

```bash
# TODO
```
## Folder Structure

* jams: Test Cases
* python: A* solver implemented using Python (less than 200 lines)

## Results

Solver Results. Most solves are less than a second, but some can take a minute or two. Could be implemented in C++ if faster solve is required.

```
finished solve for jam 1 (elapsed = 0:00:00.920000, search_count = 11587
finished solve for jam 2 (elapsed = 0:00:08.125838, search_count = 32850
finished solve for jam 3 (elapsed = 0:00:00.413685, search_count = 7856
finished solve for jam 4 (elapsed = 0:00:00.127007, search_count = 3427
finished solve for jam 5 (elapsed = 0:00:03.745302, search_count = 24220
finished solve for jam 6 (elapsed = 0:00:01.927614, search_count = 16927
finished solve for jam 7 (elapsed = 0:00:19.109896, search_count = 61026
finished solve for jam 8 (elapsed = 0:00:00.597996, search_count = 6470
finished solve for jam 9 (elapsed = 0:00:00.425014, search_count = 5928
finished solve for jam 10 (elapsed = 0:00:02.139001, search_count = 15891
finished solve for jam 11 (elapsed = 0:00:00.388999, search_count = 6859
finished solve for jam 12 (elapsed = 0:00:01.037000, search_count = 11686
finished solve for jam 13 (elapsed = 0:00:38.607385, search_count = 72340
finished solve for jam 14 (elapsed = 0:01:59.787784, search_count = 112095
finished solve for jam 15 (elapsed = 0:00:00.186012, search_count = 3188
finished solve for jam 16 (elapsed = 0:00:03.512013, search_count = 22853
finished solve for jam 17 (elapsed = 0:00:02.599997, search_count = 19809
finished solve for jam 18 (elapsed = 0:00:01.514003, search_count = 13916
finished solve for jam 19 (elapsed = 0:00:00.156012, search_count = 3589
finished solve for jam 20 (elapsed = 0:00:01.688984, search_count = 12623
finished solve for jam 21 (elapsed = 0:00:00.047999, search_count = 1697
finished solve for jam 22 (elapsed = 0:00:07.391000, search_count = 32204
finished solve for jam 23 (elapsed = 0:00:03.114997, search_count = 19901
finished solve for jam 24 (elapsed = 0:00:11.387999, search_count = 46321
finished solve for jam 25 (elapsed = 0:00:47.222471, search_count = 81562
finished solve for jam 26 (elapsed = 0:00:11.662998, search_count = 40089
finished solve for jam 27 (elapsed = 0:00:03.489997, search_count = 21351
finished solve for jam 28 (elapsed = 0:00:02.378084, search_count = 16767
finished solve for jam 29 (elapsed = 0:00:09.390998, search_count = 38396
finished solve for jam 30 (elapsed = 0:00:00.732001, search_count = 8610
finished solve for jam 31 (elapsed = 0:00:07.832997, search_count = 33193
finished solve for jam 32 (elapsed = 0:00:00.181015, search_count = 3292
finished solve for jam 33 (elapsed = 0:00:08.625361, search_count = 36586
finished solve for jam 34 (elapsed = 0:00:09.428000, search_count = 37431
finished solve for jam 35 (elapsed = 0:00:07.986791, search_count = 34141
finished solve for jam 36 (elapsed = 0:00:03.755999, search_count = 22661
finished solve for jam 37 (elapsed = 0:00:02.174012, search_count = 15270
finished solve for jam 38 (elapsed = 0:00:05.813989, search_count = 28034
finished solve for jam 39 (elapsed = 0:00:05.022875, search_count = 24792
finished solve for jam 40 (elapsed = 0:00:04.781983, search_count = 24467
```

## References

* Rush Hour Web Assembly Game (written by me):
    * Site Link: https://nathanesau.github.io/rushhour_wasm/rushhour.html 
    * GitHub Link #1: https://github.com/nathanesau/rushhour_wasm
    * GitHub Link #2: https://github.com/nathanesau/rushhour

* Inspirations for solve algorithm:
    * Java Rush Hour Solve Algorithm: https://github.com/saschazar21/rushhour
    * A* Search Algorithm: https://en.wikipedia.org/wiki/A*_search_algorithm
    * Sudoku Solver: https://github.com/nathanesau/sudoku_solver
