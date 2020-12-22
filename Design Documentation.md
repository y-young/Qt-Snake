Design Documentation
===

## Structure
### MainWindow
Displays game main menu and redirects user to other windows.

### SettingsDialog
Lets the user set game preferences and redirects user to gameboard.

### Gameboard
Holds game map, scoreboard and control panel, controls the saving, loading and state of game.

### Map
In charge of map items renderings, including foods, walls and snakes.

### Scoreboard
Displays the score, lives and undefeatable time of a single player.

### Snake
Denotes a single player, handles user commands, food effects and notifies other components of the game.

### AISnake
Inherits `Snake`, implements a simple algorithm that enables AI player to move towards the nearest food while avoiding hitting walls and the body of itself.

### Walls
Generates, stores and renders the obstacles on the map, check whether a snake hit the walls.

### Foods
Generates, stores and renders the foods on the map, check whether a snake ate a food.

### Constants
Defines game configurations, enumerables and types.

## Features
### 5 Modes
- Single Player
- Double Players
- Triple Players
- Only AI
- AI and Player

### 2 Types of Walls
- No Walls: Snake is teleported to the other side when crossing the borders
- Surrounding Walls: Walls on 4 sides, player will die when hitting the walls

### 9 Kinds of Foods
#### Fruits
- Grape: 5 points
- Pear: 10 points
- Apple: 15 points
- Peach: 20 points

#### Speed Change
- Rocket: speed up
- Snail: slow down

#### Survival Aid
- Shield: extends undefeatable time by 5 secods (extra)
- Heart: award 1 extra life

#### Special Effect
- Green Apple: reset snake length and speed (extra)

## How to Play
### Move
- Player 0: Up, Left, Down, Right
- Player 1: W, A, S, D
- Player 2: I, J, K, L

### Control
You may use game control panel on the right side or keyboard shortcuts specified below.

- Pause: 'P' key
- Resume: 'R' key
- Quit: Escape key

### Map Editing
Choose the map item to edit and the type of food from control panel, left-click to add item, right-click to remove.

## Implementations
This implemenation utilizes Qt's 'Signals and Slots' feature to decouple the components, making it organized, extensible, and easy to maintain.

### Rendering
A `QTimer` in `Map` periodically invokes `Map::paintEvent`, which calls independent rendering functions of `Snake`, `Walls` and `Foods`.

`Scoreboard` uses a timer of an 1-second interval to update `undefeatable time`.

For performance concerns, only necessary items are painted, blanks are left as they are, there's nothing like global arrays to hold the entire map.

### Snake Movement
A `QVector<QPoint>` named `body` stores the positions of snake body, the snake head is the last item of it.

When snake moves, an item is popped from the front of `body`, the new position of snake head is calculated and pushed to the back of `body` vector.

### Snake Control
Implements an _User Input Queue_ to store user inputs, each time the timer inside a `Snake` object timeouts, an user command is popped out and processed.

This technique eliminates the chance that the snake may turn around under quick operations.

After a snake moves, it emits a `snakeMoved` signal with snake ID and the new position of snake head for the judgement of walls and foods.

### Judgement of Walls
`snakeMoved` signal is connected to the `checkHit` slot of `Walls`, which checks if the snake hits the wall. If so, a `hitWall` signal is emitted along with the snake ID, the signal is sent to ths `die` slot of `Snake`.

> The connection of signals and slots between `Snake` and `Walls` is established by `Map`.

### Judgement of Foods
Similar to the judgement of walls, `Foods` will emit  a `foodEaten` signal to the `eatFood` of `Snake`, along with the type of food, `Snake` then applies the food effect to itself.

> The connection of signals and slots between `Snake` and `Foods` is established by `Map`.
> 
### Acceleration & Deceleration
As previously stated, each `Snake` has its own timer, this timer measures its speed in _rendering interval_. When it accelerates, this interval is decreased, when it decelerates, this interval is increased.

### Resurgence after Death
When a snake with more than 1 life dies, it'll be assigned a 3-second undefeatable time to escape from danger, its length and speed will be reset.

### Map Editing
When the `Edit Map` button is clicked, `Gameboard` notifies `Map` to enter editing mode and start to monitor _mouse press event_, it then calls the `add` or `remove` method of `Walls` or `Foods`.

### AI Snake
The algorithm of AI Snake is quite simple, it continuously searches for the nearest food by comparing manhattan distance.

Then it checks all 3 possible directions for the next move and choose the one that moves towards the target food, while avoiding hitting walls or itself.

### Undefeatable Time
Uses `QDeadlineTimer` as countdown

### Save & Load Game
Utilizes `QDataStream` to write and read binary file, since `QPoint`, `QVector` and other types support serialization natively, we just need to implement operator overloads for our own types.



