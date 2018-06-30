# Mancala Agent

A Human vs Computer Manacala game - Built as demonstration of an adversarial AI applied to the zero-sum game of Mancala. Uses a minimax algorithm with alpha/beta pruning to competently compete against the user.

![alt text][board]

## Usage

Complile with `g++ mancala.cpp` (or equivelant).
Run with `./mancala [ MAX_SEARCH_DEPTH ]` (`mancala [ MAX_SEARCH_DEPTH ]` on windows)

## MAX_SEARCH_DEPTH

The minimax algorithm parses it's decision space as a tree. MAX_SEARCH_DEPTH defines the maximum depth to which the algorithm may traverse before it must choose its move. A higher max depth will give a "smarter" agent, but at a geometrically increasing cost to performance.

[board]: https://github.com/dustinfast/mancala/raw/master/preview.png "Board Preview"
