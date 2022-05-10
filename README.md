# SnakeMaze
A simple maze/dungeon escape game that runs in UNIX terminal.
It was created as a tutorial to introduce the concepts of using pointers, arrays and linked lists and the basics of file reading.
This was created to provide a practicle example of using a linked list to create an undo feature due to the lack of resources available demonstrating this use.

## How to Setup
1. Download / Copy all files into your desired folder (I call mine "SnakeMaze" for simplicity)
2. In a UNIX teriminal navigate to this folder using your "cd" command, for example cd /c/Users/"Username"/Documents/"FolderName"
   - If on a computer running windows I recommend using a UNIX-like environement emulator (such as cygwin) to do this as C will not compile natively on Windows Systems
4. Compile the code using the "make" command, this will compile the game files and create a runnable program called maze.exe
   - You will need to have installed gcc in order to do this
5. To run the game in terminal type the command "./maze" along with your prefered map file (eg. "./maze map1.txt")
6. The game map will now pop up in your terminal window ready for you to play

## How to Play
- The player is indicated by the symbol '^' (it's orientation will change as it moves). It can be controlled using the w,a,s,d keys
- The snake is indicated by '~' and will atempt to move towards the player whenever the player moves, ending the game if it intercepts you
- Barriers are indicated by 'O' and cannot be crossed by the player or the snake
- Your goal is the exit, indicated by 'x'. To win you must naviagte to it whilst avoiding the snake
- If you've made a move that leaves you in a difficult position you can undo that move by pressing the u key. This can be done as many times as needed

## Creating Your Own Map Files
The layout of a map file can be demonstred here by the contents of map1.txt:

15 10 14

1 7 3

6 3 0

2 7 3

3 7 3

4 2 3 

4 3 3

4 4 3

4 5 3

1 1 1

1 8 2

5 4 3

5 7 3

6 2 3

7 2 3

7 10 3

- The first line indicates the specs of the map (number of entities, number of rows, number of columns) in that order
- The lines below it indicate entity information
  - The first number is the row it's located in (remember to count from zero and be mindful that the first and last rows contain the border)
  - The second number is the column it's located in (again be mindfull that the first and last columns contain the border)
  - The third number is it's type: '0' indicates the entity is a player, '1' indicates the entity is a snake, '2' indicates the entity is an exit and '3' indicates the entity is a boundary.
  - The order the entities are entered is not important, as long as they are of the right format the game can read it

## Read and Modify
Feel free to read through the code and modify it to your hearts content as this program was created as an example for learning.
A major area of interest, particularly to new CS students is the impimentation of the linked list which can be found in the game.h library. Here this construction is used to make an undo feature which is a topic that may frequently come up in areas of game design (or in pesky assignments) if you aren't able to make use of pre-made libraries. 

A feature some more advanced students may want to make is a more advanced snake AI for example as the current one is extremely simple and frequently finds it's self getting stuck, which I just claim is a feature meaning the player has outsmarted the snake, when in reality I just didn't have the time.

Have fun!
