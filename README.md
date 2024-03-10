This is an implementation of the game 2048 in c++, as well as an agent to play the game using alpha-beta pruning.  

Some tweaks need to be made to the implementation of the minimax algorithm to allow for floating point scores in order to give finer control over the paramaters set for the minimax algorithm.  

Currently I am using three heuristics: 
1. The number of zeros on the board
2. The total value of the top row
3. The sum of all values on the board weighted by distance from the bottom corner evaluated in a snaking pattern.

I plan to modify heuristic #1 to also account for the number of tiles which can be collapsed in either a row or a column in order to free up more open tiles.

From there I will run some simulations with various parameters to gather empirical data on the best parameters for the function.



Aside from modifications to the alpha-beta pruning search, I also plan to explore monte carlo search trees, and deep-q networks.

I might also look into implementing a system to render the current state of the board to the screen so that it looks like the game 2048, rather than my current solution of just printing the game board to the console when required.
