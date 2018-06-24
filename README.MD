# Mancala

A Human vs Computer Manacala game - A demonstration of an adversarial AI applied to the zero-sum game of Mancala. Uses a minimax algorithm with alpha/beta pruning to competently compete against the user.

## Usage

Complile with `g++ mancala.cpp` (or equivelant).
Run with `./mancala [ MAX_SEARCH_DEPTH ]` (or `mancala [ MAX_SEARCH_DEPTH ]`, on windows).

## MAX_SEARCH_DEPTH

The minimax algorithm parses it's decision space as a tree. MAX_SEARCH_DEPTH defines the maximum depth the algorithm may explore to before being forced to decide on a move. A higher max depth will give make the computer player "smarter", but at a geometrically increasing cost to performance.