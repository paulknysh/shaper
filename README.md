# shaper: A C++ tool for 3D reconstruction from parallel 2D sections

## Demos

* A voxel model that reconstructs the volume between lightning and star shapes (visualized in Mathematica):

<img src="http://i.imgur.com/arVf4Ct.png">

* A voxel model containing ~100 layers reconstructed from 25 sections (visualized in Mathematica):

<img src="http://i.imgur.com/cJqGgUL.png">

## How do I run the procedure?

In `main()` function of `shaper.cpp` user needs to specify values of `n` (number of input sections) and `m` (number of output subsections between each pair of consecutive sections). Here is the schematic:

<img src="http://i.imgur.com/65NgGKB.png">

Input sections must be PNG images named as "1.png", "2.png" etc and placed in the same directory with `shaper.cpp`. A code produces sets of subsections (also PNG images) between each pair of consecutive sections. The subsections are saved in the same directory and named as "1_1.png", "1_2.png" etc.

For example, if `n=3` and `m=2` the resultant sequence will be:
"1.png", "1_1.png", "1_2.png", "2.png", "2_1.png", "2_2.png", "3.png"

**Important:**
* Procedure can handle multi-phase reconstruction - each phase should be represented with its unique color throughout
* Procedure requires "clean" colors - without noise, color variation etc

## Credits

STB public domain libraries: https://github.com/nothings/stb

## Author

Paul Knysh
