# Chess-Engine

C++ Chess Engine, UCI and XBoard/WinBoard compliant

## Board representation
* Uses a 10x12 Board array  
<pre>
     -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
     -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
     -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
     -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
     -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
     -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
     -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
     -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
     -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
     
     -Negative numbers represent offboard squares
</pre>

## Move Representation
* Represents moves using a 32-bit integer
<pre>
  Internal representation of moves
  0000 0000 1 1111 1 1111 1111111 1111111 
            ^   ^  ^   ^      ^       ^
            1   2  3   4      5       6

    1. Castle
    2. Promoted piece
    3. EnPassant
    4. Captured piece
    5. To square
    6. From square
</pre>

## Search
* Iterative Deepening
* Alpha-beta pruning
* Quiescence search

## Move Ordering Improvements
* Transposition Table
* Polyglot opening book
* Most Valuable Victim / Least Valuable Aggressor
* Killer moves
* Null Move Pruning

## Evaluation
* Material value
* Piece Square tables
* Mobility
* Pawn structure

## Resources
* https://www.chessprogramming.org/Main_Page
* Credits to Bluefever Software, an educational youtube channel, for inspiration on the engine.
