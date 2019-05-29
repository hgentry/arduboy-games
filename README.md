# arduboy-games
This is a collection of the Arduboy games I've developed.


## Games
### TicTacToe
[TicTacToe](TicTacToe/INFO.md) - A simple Tic Tac Toe clone.
- Controls: D-pad to navigate the play field, A/B to place a mark
- A game for two players - pass the Arduboy between turns! 
- Keeps track of win/loss/tie records for extended play sessions

## Tech Demos
### RotatingCubeDemo
[RotatingCubeDemo](RotatingCubeDemo/INFO.md) - Rotate a cube!
- Controls: D-pad for rotation, A/B to bring up debug
- Rotate a cube around the X and Y axes
- Made before I was reminded that rotation is not commutative

### Quaternion Demo
[QuaternionDemo](QuaternionDemo/INFO.md) - Rotate a cube, better!
- Controls: D-pad for rotation, A/B to bring up debug
- Rotate a cube around the X and Y axes, but with quaternions
- I made this to find out if the Arduboy could even handle this kind of thing
- Surprisingly, the debug messages cause much more slowdown than the 3D
