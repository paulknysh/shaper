# shaper: A C++ code for 3D reconstruction from parallel 2D sections

## An example

The voxel model containing ~100 layers reconstructed from 25 sections. Visualisation is performed in Mathematica.

![example](https://imgur.com/a/AdwVArB)

## How do I run the procedure?

In `main()` function of `shaper.cpp` user needs to specify values of `n` (number of given sections) and `m` (number of desired subsections between each pair of sections).

![(sub)sections](https://imgur.com/a/bc0MGEJ)

Consecutive 2D sections must be reprsented as PNG images named as "1.png", "2.png", ... etc. All images must be placed in the same directory as the `shaper.cpp`.

The output of the procedure is the set of intermediate images saved in the same directory and named as "1_1.png", "1_2.png", ... etc.

**Important:**
* PNG images should contain "clean" RGB colors

## Author

Paul Knysh (paul.knysh@gmail.com)

Feel free to email me if you have any questions or comments.
