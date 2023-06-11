# Multiplayer-Among-Us-Game
## The game should has the following features:
1. The game board is represented as a two-dimensional grid of squares. Each square can either be
empty or contain an item that the player can collect.
2. Players can move around the board by pressing arrow keys on their keyboard.
3. When a player moves onto a square that contains an item, they collect the item and gain points.
There can be multiple players on the board at the same time.
4. The game should be able to handle multiple players moving and collecting items concurrently.

## Board size is calculated using the following steps
1. Generating any random number between 10 - 99
2. Multiply the generated number by last digit of your roll number.
3. Now divide your roll number with the generated number.
4. Once division is done, Take the mod of respective number with 25. If your number is
less than 10, add 15 to it.

