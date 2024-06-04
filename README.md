# rubiks_cube

Super Fast Rubiks Cube Solver

# Project

This is a fun project to learn about compiling, linking and tools like cmake and make.

# Components

This project is implemented according to the Model-View-Controller design pattern.

## Representing and Manipulating States (Model)

For efficient calculations we will use a binary representation of the cube. As outlined in this stack overflow post (https://stackoverflow.com/questions/500221/how-would-you-represent-a-rubiks-cube-in-code), you represent each side as a 64 bit integer. Each of the 8 faces on a side is encoded as a single byte that denotes its color. The only action where all 8 colors necessarily stay the same, but the location changes is the rotation of the face. Hence it would be nice to represent the cube in a way where we can move the bytes inside the integer to represent rotation in a single instruction. This can be achieved if we order the bytes in the following way:

1 2 3
8 X 4
7 6 5

Now rotating 90-degrees Clockwise is a single 16-bit rolq instruction (the other rotations are all rorq/rolq) instructions. Note that the edges on the other faces have to be manually adjusted. We could either do this by copying the edges over in a circle or using bitwise operation. We should check which approach is faster.

There is two ways to model rotating a slice. The simplest one is just rotating the two faces that sandwich it instead which allows the center to always stay on the same face. Alternatively you have to remember which face the center is on seperately and then do some manual copying/bitwise operations.

The cube can be seen as this:

. . . | 1 2 3 | . . .
. . . | 8 W 4 | . . .
. . . | 7 6 5 | . . .
----------------------
1 2 3 | 1 2 3 | 1 2 3
8 R 4 | 8 B 4 | 8 O 4
7 6 5 | 7 6 5 | 7 6 5
----------------------
. . . | 1 2 3 | . . .
. . . | 8 Y 4 | . . .
. . . | 7 6 5 | . . .
----------------------
. . . | 1 2 3 | . . .
. . . | 8 G 4 | . . .
. . . | 7 6 5 | . . .

Face W is White and Up, Face Y is Yellow and Down
Face R is Red and Left, Face O is Orange and Right
Face B is Blue and Front, Face G is Green and Back

## Visualizing the Cube (View)

For the initial visualization I will print to the console.

## Solving the Cube (Controller)

For the initial solver, I will implement a trivial but slow approach:

1. Establish the white cross
2. Fill in the corners
3. Fill the second layer
4. Make the yellow cross
5. Solve the cube

# Credits

Inspired by https://github.com/benbotto/rubiks-cube-cracker.
