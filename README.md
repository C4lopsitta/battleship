# Battleship
**I ACCIDENTALY BROKE THE REPO** So this will not work. Will revert asap
**This game will most likeley run ONLY on Linux because of termios.h**

A repository for all the files in my school assignment to make a simple battleship game with a matrix, i added *quite a lot* of extra things to the original assignment such as:
- (planned) local multiplayer
- (considering) network and serial multiplayer
- player vs computer
- WASD input instead of some lame X,Y
- a *fancy* UI (for my standards at least)
- shitty unreadable code

If you add any (serious) issues i *might* fix them, also consider that i'm actively developing this project and it's not yet complete.

I also know that this isn't how you're supposed to use header files and that you should use them only for function prototypes and use separate .c files for the actual implementation but i *do not give a fuck* about that.

# Compiling the program
Requirements:
- gcc
- make
- git (to clone the repository)

1. Clone the repository with the following command
    ```bash
    $ git clone https://github.com/c4lopsitta/battleship
    ```
2. Enter the folder and make the executable
    ```bash
    $ cd battleship
    $ make
    ```
3. Run the executable from the `bin/` folder
    ```bash
    $ bin/battleship
    ```
