# square_puzzle
C code for solving classic 9x9 square tile puzzles

(I.e. puzzzles like this: http://www.robspuzzlepage.com/images/vess-billion-bubbles-pcs1.jpg)

# How to

Configure the code at the top between "CONFIG" and "CONFIG END"
 - Define each tile `'A'` -> `'I'` according to their layout
 - `a` -> `d` is for objects
 - `A` and `B` are for each end
 - For instance, `cB` means "the back side of the third object
 - Optionally, define colors using standard ANSI codes

Compile, run!  You'll see 4 solutions for each 1 unique solution, since each is valid in 4 rotations.
