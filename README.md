# Project Description
This project was submitted as part of a graded assignment for a "Data Structures and Algorithms" module.

It aims to replicate the classical board game “Reversi”, or otherwise known as “Othello”, as a console application, making use of various data structures and algorithms to program the game logic. Reversi and Othello are very similar games in terms of the game mechanics, but since there are slight variations in the rules, we will be following the international Reversi rules.

## Rules
Reversi is played on a 8x8 board, with 2 players, using black and white pieces to represent the players. The objective of the game is to have more pieces than the other player at the end of the game, and the game ends when every tile (or cell) of the grid has been filled, or when none of the players have any legal moves to make. 

The core of the game revolves around capturing enemy pieces, and this occurs when a new placed piece traps pieces of the other colour in between this piece and another piece of the same colour. Pieces can be captured vertically, horizontally or diagonally, and several pieces can be captured with the placement of a single piece.

Reversi starts the game off with no pieces on the board, which is unlike Othello which starts with 4 alternating pieces placed in the middle. The first two moves of each plate have to be within the 4 middle tiles, and be non-capturing moves. The side playing black will start first, placing a black piece within the 4 middle tiles then followed by white. Every move after the first 4, has to capture at least 1 enemy piece for it to be considered a valid or legal move. In the event a player has no valid moves to make, the player simply skips their turn until they have a valid move.

Our implementation of the game accepts an input from the user each turn, taking in 2 values (row, column) to determine the position of the board to place the new piece, and then the console would display the state of the board. It also has 2 modes of gameplay, singleplayer where the user plays against an AI or multiplayer, where it takes in an input for both white and black. On top of this, there is also an implementation of a history system, where past matches can be viewed or deleted.

# Instructions
## Setup
1.	Download the zipped folder from the network folder or clone the repository from https://github.com/kahkoii/Reversi-Game
2.	Navigate to the Reversi.sln solution file and open with Visual Studio
3.	Click the green triangle at the top with “Local Windows Debugger” to launch the program

## Gameplay
●	On the main menu, input 1, 2, 3 or 4 to play multiplayer, play singleplayer, view match history and exit the program respectively

●	If the user is playing multiplayer or singleplayer, they can select a tile on the board to place their piece by typing in 2 numbers separated by a space, representing the x and y coordinates on the board respectively

●	If the user chooses singleplayer specifically, they also have the option to display the moves that the AI considers before making its decision, do note that enabling this may cause the console to print repeatedly

●	If the user chooses to view history, they can choose an action, 1 to view a match history, 2 to delete a record, or -1 to return to the main menu. If they choose to view or delete, they will be prompted to enter a number to select a specific record to carry out the action on. 

# Components Overview & Project Contributions


# Features
## Board Class (Contribution by Kah Ho)
The board is a graph containing 8 x 8 Nodes, which are all connected to all surrounding Nodes. The attributes of this class include an 8 x 8 array of Node pointers with each item pointing to a unique Node, and an integer containing the total number of pieces on the board.

Within the Board class, a less complex 8 x 8 array of integers referred to as “Grids” are used to contain the state of the board, storing the status of each tile on the board as an integer instead of a Node object. The usage of Grids allows us to represent the state of the board and pass data about the state of the board quickly without containing the extra pointer data, which comes in useful in functions such as “Foresight” which is used to check how many pieces would be flipped if a certain piece was placed down, and “SetBoard” which allows us to change the state of the board immediately, given a grid as a parameter.

### Graph Data Structure
[image]

The Board class makes use of a Graph data structure to represent the real-life equivalent of a Reversi board. A graph where all surrounding Nodes are connected to one another is specifically used so we can implement a recursive function to flip the pieces on the board when a new piece is “placed”. Due to the nature of Reversi, any changes to any individual piece can affect the pieces around it, so the Nodes being connected in such a manner would allow any Node to pass data or call functions of the Nodes around it (further explained in the Node Class).

### Update Algorithm
In this class, the “SetBoard” function was implemented to update the state of the board to a different state given a Grid of integers, essentially providing an update functionality for the Graph. The Graph is updated by having a nested for-loop go through every Node on the Graph and updating the value of the Node from its old value to a corresponding value on the Grid. In the “Foresight” algorithm, the coordinates of a tile and a colour is passed in as parameters, and an integer representing the number of pieces that were captured is returned, which allows us to determine if specific moves are considered legal moves. This is achieved by first saving the current state of the board in a temporary Grid, then placing a piece down and checking how many pieces have changed as a result, before using this “SetBoard” function to update the Graph to match its state before the “hypothetical” change. 

## Node Class (Contribution by Kah Ho)
[image]

The Node represents tiles on the Reversi board, and it contains the colour of the piece that is supposed to be on it, with 0, 1 and -1 representing white, black, and empty respectively, where empty means there are currently no pieces placed on the tile. Unlike the Graph which has direct access to all Nodes, each Node object only has access to the 8 Nodes surrounding it, and for Nodes on the borders of the board, up to 3 of the pointers will be NULL, depending on which side of the board the Node is in.

The 8 directions ranging clockwise from N for North to NW for North-West, are pointers which point to a Node in the corresponding direction. Each Node having 8 pointers allows it to make recursive function calls to Nodes in a specific direction.

### Recursion Algorithm
Whenever a new piece is placed on the board, the Node that the piece is placed on will call a recursive function “FlipRequest” on all 8 of its surrounding Nodes, and all of the Nodes which have called the function will continue to recursively call the function on the Nodes in the same direction, until either a same-coloured piece is found, the last piece in that direction is reached, or the edge of the board is reached. Then, depending on what value is passed back to the original Node through the recursive function, the colours of the Nodes will change. Using a recursive function is necessary because it allows the program to automatically “crawl” through the pieces on the board and make changes if a set of conditions are true, and break out of the function when some conditions are met, allowing us to apply the rules of Reversi to our game without hardcoding, which would provide the added benefit of being able to run on a board larger than 8 x 8.
 
1. Originally, there is an empty spot on the board (green)
[image]

2. A new piece is placed on the board, and the FlipRequest function is called in all 8 directions
[image]
 
3. The recursive function is kept being called until the same coloured piece is found, an empty tile is reached, or the end of the board is reached
[image]

4. In the case where the same-coloured piece is found, a boolean value true is returned to the Node which called the function, and every Node that is between this current Node and the Node where the new piece was placed, will also return true to the previous Node, whilst flipping its colour to the opposite colour, until the original Node is reached, exiting the recursive function
[image]

## AI Class (Contribution by Dong Kiat)
### Minimax Algorithm
[image]

The minimax algorithm is a recursive algorithm that is used for decision making and finding the optimal move for a player. It is widely used in many turn based games. There are two players in Minimax, which are the minimizer and maximizer. The goal of the maximizer is to get the highest score possible, while the goal of the minimizer is to get the lowest score possible.

[image]

Above is the pseudocode that was obtained and used as reference to build the minimax algorithm for the AI. It has a depth parameter to limit how many layers deep it goes. This is because in a game of Reversi, the number of possible moves with each layer becomes significantly larger, thus we have to limit it to prevent an unmeasurably large processing time. The greater the depth, the stronger the AI, thus the depth can be used to determine the difficulty level of the AI. For this AI, the default depth has been set to 3, which results in a somewhat easy to medium difficulty after playing against it a couple of times.

### Alpha Beta Pruning
[image]

Alpha Beta Pruning is a search algorithm that helps to optimize the minimax algorithm. It does so by reducing the number of nodes that are needed to be evaluated, thus reducing processing time and redundant searching. When applied to a minimax algorithm, it will still return the same move as minimax alone would, but it prunes away the branches that cannot possibly influence the final decision.

[image]

Above is the minimax pseudocode obtained that utilizes the Alpha Beta Pruning algorithm. As can be seen, two more parameters have been added, which are alpha and beta respectively. Initially, alpha is a highly negative number and beta is a huge positive number. Both players start with the worst possible score. Whenever the maximum score that the minimizing player is assured of becomes less than the minimum score that the maximizing player is assured of, the maximizing player need not consider further descendants of this node, as they will never be reached.
 
### Performance Comparison
To compare the performance difference with Alpha Beta Pruning, 8 games were played against the AI we have built. 4 games using the Minimax algorithm alone, and another 4 games with the Alpha Beta Pruning applied. The results can be seen below.

[image]

Above shows the accumulated number of states explored by the AI for each entire game. As can be seen, with just the Minimax algorithm alone, the number of states the AI had to explore is larger on average than the AI with Alpha Beta Pruning applied.

[image]

The table above shows the raw values from the graph. With the results obtained, it can be concluded that the Alpha Beta Algorithm optimized and improved the performance of the AI, and resulted in an average improvement of states explored by 2.54 times.

## Move History Class (Contribution by Kah Ho)
The Move History class is the object used to represent the set of moves made in a specific game. This class makes use of a doubly linked list data structure to allow the user to navigate back and forth between different points of history of a game, and this class contains the attributes “first”, “current” and “last” which are pointers to the respective Moves in the linked list, “currentMove” which is the numeric representation of the position of a move in the list, “totalMoves'' which is the total number of moves made in that match, and “winner” which represents the outcome of the match, with “w”, “b” and “t” to represent white, black and tie respectively. Also within this class is a struct called “Move”, which contains 2 pointers, 1 pointing to the next Move in the list and one pointing to the previous, and a Grid, which is a 8 x 8 integer array representing the state of the board (explained earlier in the Board class).
Doubly Linked List Data Structure

A doubly linked list is used to represent the set of moves made in a game because it allows the user to traverse back and forth within the linked list, to make comparisons between different states of the board and see what changes are made with each move. The sequential revealing of the board status is more accurate in portraying the moves made in a game, so using vectors or arrays which give access to the whole list at once would not be as appropriate.

[image]

### Insertion Algorithm
This doubly linked list data structure makes use of an insertion algorithm to add a new Move to the back of the doubly linked list. Whenever a new Move is inserted into the list, the algorithm first checks if the list is empty. If it is empty, it sets the first, current and last pointers to the new Move. Any subsequent moves that are added would change the last pointer to point to the new Move, while the first and current pointer remain unchanged. This insertion algorithm is called every time the player or the AI makes a move, and saves the current state of the board after every move.

## History Logs Class (Contribution by Dong Kiat)
The History Logs class acts as a storage that stores the Move History class for each game that was played during the session. 

### Stack
A basic stack is used to store all the games. Within each stack, it contains records that have the Move History class as an item and a pointer to the next node. It is able to insert records, delete records, display all records and get a record.
[image]
