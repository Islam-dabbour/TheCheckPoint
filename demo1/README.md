## `demo1/README.md`

```markdown
# Demo 1: Manual Checkpointing

Demo 1 demonstrates basic manual checkpoint saving and loading in C.

## What It Includes

- `game.c`: Source code for the game
- `game`: Compiled game executable
- `checkpoint.bin`: Binary checkpoint file

## How It Works

When the game starts, it asks whether to start a new game or load an existing checkpoint.

The game stores the following state:

- Level
- Score
- Health
- Player position
- Checkpoint time

The player can use the game menu to update the score and health. When the game exits, it can save the current state to `checkpoint.bin`.

## Compile

```bash
cd /home/islam/TheCheckPoint/demo1
gcc `game.c` -o game
```

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

This is a binary file containing the serialized game state.

## Notes

- The game does not require command-line arguments.
- Run the program from the `demo1` directory.
- The checkpoint file is created or replaced when the game saves.
```

