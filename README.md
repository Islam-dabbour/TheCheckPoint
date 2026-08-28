

## Root `README.md`

```markdown
# TheCheckPoint

TheCheckPoint is a collection of C programming demonstrations that progressively implement game checkpoint and save functionality.

The project demonstrates:

- Manual checkpoint saving and loading
- Automatic periodic checkpointing with POSIX threads
- Urgent checkpoint saving using named pipes
- Multiple game processes managed by a checkpoint manager
- Communication between processes using FIFOs

## Project Structure

```text
TheCheckPoint/
├── demo1/
├── demo2/
├── demo3/
└── demo4/
```

Each demo is independent and should be compiled and run from its own directory.

## Requirements

- Linux or WSL
- GCC
- POSIX threads support
- `xterm` for Demo 4
- A graphical display if using `xterm`

Install the required tools on Ubuntu or WSL:

```bash
sudo apt update
sudo apt install gcc xterm
```

## Demos

### Demo 1

Demonstrates manual checkpoint saving and loading using a binary file.

See [demo1/README.md](demo1/README.md).

### Demo 2

Demonstrates automatic periodic checkpointing using a background POSIX thread.

See [demo2/README.md](demo2/README.md).

### Demo 3

Demonstrates urgent checkpoint saving after a simulated power failure. The programs communicate through named pipes.

See [demo3/README.md](demo3/README.md).

### Demo 4

Demonstrates multiple independent games managed by one checkpoint manager. Each game has its own checkpoint file and named pipes.

See [demo4/README.md](demo4/README.md).

## Important Notes

Run commands from the appropriate demo directory because the programs use relative file paths.

Checkpoint files are binary files generated while the programs run. They should not be edited manually.

Named pipes are also generated during execution. They may remain in the directory after a program exits and can be removed with:

```bash
rm -f *_pipe *_response power_pipe
```

To stop all project processes in WSL:

```bash
pkill -9 -f 'game[1-3]'
pkill -9 -f checkPointManager
pkill -9 -f xterm
```

Alternatively, from PowerShell:

```powershell
wsl --shutdown
```
```
