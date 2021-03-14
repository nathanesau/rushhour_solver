# rushhour_solver

Solve RushHour puzzles using Dijkstra's Algorithm.

See the [docs](docs/README.md) for a detailed a explanation of the algorithm.

## Results

C++

```
solved jam01 in 0.045076 seconds (node count = 11586)
solved jam02 in 0.201284 seconds (node count = 33886)
solved jam03 in 0.023817 seconds (node count = 7799)
solved jam04 in 0.011589 seconds (node count = 3490)
solved jam05 in 0.146569 seconds (node count = 24066)
solved jam06 in 0.089744 seconds (node count = 16917)
solved jam07 in 0.280209 seconds (node count = 56221)
solved jam08 in 0.044166 seconds (node count = 6469)
solved jam09 in 0.036175 seconds (node count = 5933)
solved jam10 in 0.098053 seconds (node count = 16196)
solved jam11 in 0.026874 seconds (node count = 6858)
solved jam12 in 0.046308 seconds (node count = 11685)
solved jam13 in 0.521913 seconds (node count = 72544)
solved jam14 in 0.867875 seconds (node count = 116280)
solved jam15 in 0.021446 seconds (node count = 3187)
solved jam16 in 0.124391 seconds (node count = 23103)
solved jam17 in 0.115059 seconds (node count = 19640)
solved jam18 in 0.05918 seconds (node count = 13895)
solved jam19 in 0.016408 seconds (node count = 3588)
solved jam20 in 0.070274 seconds (node count = 12483)
solved jam21 in 0.005602 seconds (node count = 1696)
solved jam22 in 0.208542 seconds (node count = 32414)
solved jam23 in 0.117906 seconds (node count = 19884)
solved jam24 in 0.235652 seconds (node count = 46320)
solved jam25 in 0.560147 seconds (node count = 81942)
solved jam26 in 0.251328 seconds (node count = 40854)
solved jam27 in 0.110104 seconds (node count = 21339)
solved jam28 in 0.092958 seconds (node count = 15557)
solved jam29 in 0.23098 seconds (node count = 38405)
solved jam30 in 0.041215 seconds (node count = 8609)
solved jam31 in 0.178864 seconds (node count = 33028)
solved jam32 in 0.016812 seconds (node count = 3271)
solved jam33 in 0.231987 seconds (node count = 36608)
solved jam34 in 0.219605  seconds (node count = 37390)
solved jam35 in 0.180512 seconds (node count = 34067)
solved jam36 in 0.141356 seconds (node count = 22759)
solved jam37 in 0.093657 seconds (node count = 15269)
solved jam38 in 0.15607 seconds (node count = 28513)
solved jam39 in 0.15541 3seconds (node count = 24881)
solved jam40 in 0.157726 seconds (node count = 24466)
```

Python:

```
solved jam1 in 0.078999 seconds (node_count = 11632)
solved jam2 in 0.374999 seconds (node_count = 32378)
solved jam3 in 0.04 seconds (node_count = 7833)
solved jam4 in 0.021001 seconds (node_count = 3426)
solved jam5 in 0.212002 seconds (node_count = 22863)
solved jam6 in 0.138997 seconds (node_count = 16979)
solved jam7 in 0.547 seconds (node_count = 56795)
solved jam8 in 0.068 seconds (node_count = 6469)
solved jam9 in 0.051002 seconds (node_count = 5912)
solved jam10 in 0.142 seconds (node_count = 15435)
solved jam11 in 0.042 seconds (node_count = 6894)
solved jam12 in 0.078 seconds (node_count = 11685)
solved jam13 in 0.115004 seconds (node_count = 76561)
solved jam14 in 0.268997 seconds (node_count = 121157)
solved jam15 in 0.031999 seconds (node_count = 3187)
solved jam16 in 0.195001 seconds (node_count = 23289)
solved jam17 in 0.161999 seconds (node_count = 19708)
solved jam18 in 0.095003 seconds (node_count = 13917)
solved jam19 in 0.022997 seconds (node_count = 3584)
solved jam20 in 0.134002 seconds (node_count = 13520)
solved jam21 in 0.009999 seconds (node_count = 1696)
solved jam22 in 0.341 seconds (node_count = 32734)
solved jam23 in 0.157 seconds (node_count = 18561)
solved jam24 in 0.371999 seconds (node_count = 45837)
solved jam25 in 0.947002 seconds (node_count = 81627)
solved jam26 in 0.384998 seconds (node_count = 40103)
solved jam27 in 0.178 seconds (node_count = 21361)
solved jam28 in 0.143001 seconds (node_count = 15454)
solved jam29 in 0.346999 seconds (node_count = 38411)
solved jam30 in 0.065 seconds (node_count = 8632)
solved jam31 in 0.288 seconds (node_count = 32985)
solved jam32 in 0.029002 seconds (node_count = 3291)
solved jam33 in 0.338 seconds (node_count = 37589)
solved jam34 in 0.318 seconds (node_count = 37420)
solved jam35 in 0.288 seconds (node_count = 34143)
solved jam36 in 0.19 seconds (node_count = 22199)
solved jam37 in 0.138 seconds (node_count = 15269)
solved jam38 in 0.261002 seconds (node_count = 29290)
solved jam39 in 0.225003 seconds (node_count = 24791)
solved jam40 in 0.225997 seconds (node_count = 24466)
```

## Instructions

Run the Python tests:

```bash
pytest -s src/python
```

Run the C++ tests:

```bash
# build with cmake
"F:\rushhour_solver\src\cpp\build\Release\test.exe"
```

## References

* Rush Hour Web Assembly Game (written by me):
    * Site Link: https://nathanesau.github.io/rushhour_wasm/rushhour.html 
    * GitHub Link: https://github.com/nathanesau/rushhour
