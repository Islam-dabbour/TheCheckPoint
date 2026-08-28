
## `demo4/README.md`

```markdown
# Demo 4: Multiple Game Checkpoints

Demo 4 extends the previous demonstrations to support three independent game processes.

Each game has its own executable, checkpoint file, and named pipes.

## What It Includes

- `game.c`: Source code shared by the game versions
- `game1`: First game executable
- `game2`: Second game executable
- `game3`: Third game executable
- `powerMonitor.c`: Simulates a power failure
- `checkPointManager.c`: Starts and manages the games
- `powerMonitor`: Compiled power monitor
- `checkPointManager`: Compiled manager
- `checkpoint_1.bin`: Checkpoint for Game 1
- `checkpoint_2.bin`: Checkpoint for Game 2
- `checkpoint_3.bin`: Checkpoint for Game 3
- Per-game named pipes for save requests and responses

## How It Works

The checkpoint manager starts three game processes:

```text
./game1 1
./game2 2
./game3 3
```

Each game receives a unique game ID.

The game ID determines the checkpoint filename:

```text
Game 1 -> checkpoint_1.bin
Game 2 -> checkpoint_2.bin
Game 3 -> checkpoint_3.bin
```

Each game also uses separate named pipes:

```text
game1_pipe
game1_response

game2_pipe
game2_response

game3_pipe
game3_response
```

When a power failure is triggered:

1. `powerMonitor` writes to `power_pipe`.
2. `checkPointManager` receives the power-failure status.
3. The manager sends a save request to each running game.
4. Each game saves its own checkpoint.
5. Each game sends a response to the manager.
6. The manager reports which games saved successfully.

## Compile

```bash
cd /home/islam/TheCheckPoint/demo4

gcc `game.c` -o game1 -pthread
gcc `game.c` -o game2 -pthread
gcc `game.c` -o game3 -pthread

gcc powerMonitor.c -o powerMonitor
gcc `checkPointManager.c` -o checkPointManager
```

## Run

Start the power monitor in one terminal:

```bash
cd /home/islam/TheCheckPoint/demo4
./powerMonitor
```

Start the checkpoint manager in another terminal:

```bash
cd /home/islam/TheCheckPoint/demo4
./checkPointManager
```

The manager launches the three games in separate `xterm` windows.

Enter:

```text
1
```

in the power monitor to simulate a power failure.

## Run Games Individually

The games require a game ID:

```bash
./game1 1
./game2 2
./game3 3
```

## Terminal Requirements

The manager uses `xterm` to open separate game windows.

Install it with:

```bash
sudo apt update
sudo apt install xterm
```

If `xterm` reports a missing font, install:

```bash
sudo apt install xfonts-base fonts-dejavu
```

A graphical display is required for separate windows. WSLg is required when running graphical Linux applications through WSL.

## Checkpoint Files

The game checkpoints are stored separately:

```text
checkpoint_1.bin
checkpoint_2.bin
checkpoint_3.bin
```

## Notes

- Run the manager from the `demo4` directory.
- The manager expects `game1`, `game2`, and `game3` to exist.
- A FIFO existing on disk does not necessarily mean the corresponding game is running.
- The manager uses nonblocking FIFO operations to detect games that have already exited.
- The manager waits for a limited time for game responses.
- Checkpoint files are binary files and should not be edited manually.
- To close a game normally, enter `-1` inside that game.
```
