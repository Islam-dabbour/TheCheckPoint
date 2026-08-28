
## `demo3/README.md`

```markdown
# Demo 3: Urgent Checkpointing

Demo 3 demonstrates periodic checkpointing and urgent checkpointing triggered by a simulated power failure.

The programs communicate using POSIX named pipes, also called FIFOs.

## What It Includes

- `game.c`: Game process
- `powerMonitor.c`: Simulates a power failure
- `checkPointManager.c`: Coordinates the power monitor and game
- `game`: Compiled game executable
- `powerMonitor`: Compiled power monitor executable
- `checkPointManager`: Compiled manager executable
- `power_pipe`: Communication pipe from the power monitor
- `game_pipe`: Communication pipe from the manager to the game
- `game_response`: Communication pipe from the game to the manager
- `checkpoint.bin`: Binary checkpoint file

## How It Works

The system contains three processes:

1. The game process runs the game and periodically saves its state.
2. The power monitor waits for a simulated power failure.
3. The checkpoint manager forwards the power-failure notification to the game.

When a power failure is triggered:

1. `powerMonitor` writes a status value to `power_pipe`.
2. `checkPointManager` reads the status.
3. The manager sends the status to the game through `game_pipe`.
4. The game saves its checkpoint immediately.
5. The game sends a response through `game_response`.
6. The manager reports whether the checkpoint was saved.

## Compile

Open a terminal and run:

```bash
cd /home/islam/TheCheckPoint/demo3
gcc `game.c` -o game -pthread
gcc powerMonitor.c -o powerMonitor
gcc `checkPointManager.c` -o checkPointManager
```

## Run

Start the game:

```bash
./game
```

In a second terminal, start the checkpoint manager:

```bash
cd /home/islam/TheCheckPoint/demo3
./checkPointManager
```

In a third terminal, start the power monitor:

```bash
cd /home/islam/TheCheckPoint/demo3
./powerMonitor
```

Enter:

```text
1
```

in the power monitor to simulate a power failure.

## Checkpoint File

The game saves its state to:

```text
checkpoint.bin
```

## Notes

- All programs must use the same `demo3` directory.
- The manager and game communicate through named pipes.
- The programs may block if one of the required processes is not running.
- The checkpoint file is a binary file.
```
