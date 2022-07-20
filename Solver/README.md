﻿# Thistlethwaite Solver


C++ Code to solve a Rubik's cube using the Thistethwaite algorithm : (https://www.jaapsch.net/puzzles/thistle.htm)


## Execution

The first 12 values are the edge cubies, and the next eight are the corners. The faces are U(p), D(own), R(ight), L(eft), F(ront), and B(ack). First the cubie that's in the UF position is given, by the color (in UFRDBL notation) that's on top first, and then the other color next. And so on.

`UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR`  represents the solved cube. Performing  `U`, a 90° clockwise turn on the front face, would result in  `LF UR UB UL RF DR DB DL FU FD BR BL LFU URB UBL LDF RUF RFD DLB DBR`.


Here are some visualizations that may be helpful:
![](https://i.stack.imgur.com/bU5Nc.png)

That renders the input  `UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR`.

The way the input works is by using the template of the solved cube. If  `DF`  was in the place of  `UF`, then the orange-white edge would be in the place of the red-white edge.

##    Input examples
###   1)
If we were to swap, for example, the red-white edge and the red-blue edge, the visualization would look like this (with no changes to the hidden faces):

![](https://i.stack.imgur.com/pdndD.png)

That renders the input `UR UF UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR` (which, btw, is an impossible cube state). 
>**Note** that the order of the letters in cubies matter:


```
Above: UR UF UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR
Below: RU FU UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR
```
![](https://i.stack.imgur.com/mQF50.png)

### 2)
A cube scrambled with  `L2D2L2D2B2R2F2L2D2U2F2UF2U'R2UB2U'L2UB2U'LU'L2U'D'B2U'RBUBF'D'`  creates this visualization (only top, front, and right faces shown):

![](https://i.stack.imgur.com/X8S81.png)

```
Solved:    UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR
Scrambled: RU LF UB DR DL BL UL FU BD RF BR FD LDF LBD FUL RFD UFR RDB UBL RBU
```
As you can see in the comparison above and in the visualizations, the blue-red `RU` edge of the mixed cube is in the place of the red-white `UF` edge of the solved cube. The green-white `LF` edge is in the place of the red-blue `UR` edge, etc.

# Connection of Solver & Simulator


The solver program takes manual input from user and then creates a txt file with the output named "solve" in the same folder. "solve.txt" contains solution of the scrambled cube which is read by the simulator program. Because of this both the set of codes should be present in same folder. Simulator performs the solution moves according to "solve.txt" and we gradually come to see the cube being solved!


