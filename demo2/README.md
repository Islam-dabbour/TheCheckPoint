## `demo2/README.md`

```markdown
# Demo 2: Automatic Checkpointing

Demo 2 demonstrates automatic checkpoint saving using a POSIX background thread.

## What It Includes

- `game.c`: Source code for the game
- `game`: Compiled game executable
- `checkpoint.bin`: Binary checkpoint file

## How It Works

The game starts a background save thread. The thread periodically writes the current game state to `checkpoint.bin`.

The main game continues to accept user input while the background thread performs checkpoint saves.

The game state includes:

- Level
- Score
- Health
- Player position
- Checkpoint time

## Compile

```bash
cd /home/islam/TheCheckPoint/demo2
gcc `game.c` -o game -pthread
```

The `-pthread` option enables POSIX thread support.

## Run

```bash
./game
```

Follow the instructions displayed by the game.

## Checkpoint File

The checkpoint is stored in:

```text
checkpoint.bin
```

## Notes

- The game does not require command-line arguments.
- Checkpoints are saved automatically while the game is running.
- Run the program from the `demo2` directory.
- The checkpoint file is binary and should not be edited manually.
```
