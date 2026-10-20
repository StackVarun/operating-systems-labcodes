# Operating Systems Lab — 21CSC202J

C programs for **Operating Systems Lab (21CSC202J)**, organized by experiment for practical sessions, revision, and learning.

The programs in this repository are transcribed from the supplied Operating Systems Lab manual. **Only indentation was adjusted** for readability; one line wrapped by the PDF layout was rejoined. No algorithms, identifiers, comments, or program behavior have been intentionally changed. These are lab-manual examples, not revised or optimized implementations.

## Contents

- **Experiments 1, 1B and 1C** cover operating-system installation, basic Linux commands, filters and administrative commands. See [installation and Linux commands](docs/experiment-01-installation-linux-commands.txt).
- **Experiments 2–15** contain the following **20 C programs**:

| Experiment | Topic | Source file |
|---|---|---|
| Ex 2 | wait() | [`02_wait.c`](programs/02_wait.c) |
| Ex 3 | Multithreading | [`03_pthreads.c`](programs/03_pthreads.c) |
| Ex 4 | Semaphore and Monitor | [`04_semaphore_monitor.c`](programs/04_semaphore_monitor.c) |
| Ex 5 | Reader-Writer | [`05_reader_writer.c`](programs/05_reader_writer.c) |
| Ex 6 | Dining Philosophers | [`06_dining_philosophers.c`](programs/06_dining_philosophers.c) |
| Ex 7 | Bankers Algorithm | [`07_bankers.c`](programs/07_bankers.c) |
| Ex 8A | FCFS Scheduling | [`08a_fcfs.c`](programs/08a_fcfs.c) |
| Ex 8B | SJF Scheduling | [`08b_sjf.c`](programs/08b_sjf.c) |
| Ex 9A | Priority Scheduling | [`09a_priority.c`](programs/09a_priority.c) |
| Ex 9B | Round Robin Scheduling | [`09b_round_robin.c`](programs/09b_round_robin.c) |
| Ex 10 | FIFO Page Replacement | [`10_fifo.c`](programs/10_fifo.c) |
| Ex 11A | LRU Page Replacement | [`11a_lru.c`](programs/11a_lru.c) |
| Ex 11B | LFU Page Replacement | [`11b_lfu.c`](programs/11b_lfu.c) |
| Ex 12A | Best Fit | [`12a_best_fit.c`](programs/12a_best_fit.c) |
| Ex 12B | Worst Fit | [`12b_worst_fit.c`](programs/12b_worst_fit.c) |
| Ex 13 | Disk Scheduling | [`13_disk_scheduling.c`](programs/13_disk_scheduling.c) |
| Ex 14A | Sequential File Allocation | [`14a_sequential.c`](programs/14a_sequential.c) |
| Ex 14B | Indexed File Allocation | [`14b_indexed.c`](programs/14b_indexed.c) |
| Ex 15A | Single-Level Directory | [`15a_single_level.c`](programs/15a_single_level.c) |
| Ex 15B | Two-Level Directory | [`15b_two_level.c`](programs/15b_two_level.c) |

## Requirements

- **Linux/Ubuntu** environment recommended (the lab manual uses Linux/POSIX APIs).
- GCC compiler.
- POSIX threads support for threading and synchronization examples.

> Some semaphore examples, particularly programs using `sem_init()`, may not work directly on macOS. Linux or an appropriate Linux environment is recommended.

## Compile and run

### Standard C example (Experiment 2)

```bash
gcc programs/02_wait.c -o wait
./wait
```

### POSIX threads example (Experiment 3)

```bash
gcc programs/03_pthreads.c -o pthreads -pthread
./pthreads input.txt
```

For Experiment 3, prepare a plain-text `input.txt` containing integers (the program reads up to 1,000 integers). For other programs, substitute the corresponding source filename and provide input when prompted. For thread-based programs, compile with `-pthread`.

### Stopping the continuously running Dining Philosophers example

Experiment 4 intentionally runs indefinitely. Press **Ctrl+C** to stop it.

## Organization

```text
operating-systems-lab/
├── README.md
├── .gitignore
├── docs/
│   └── experiment-01-installation-linux-commands.txt
└── programs/
    ├── 02_wait.c
    ├── 03_pthreads.c
    ├── ...
    └── 15b_two_level.c
```

## Notes

- Experiment numbering, labels, and code are based on the provided lab manual.
- The code is kept close to the manual for reference and memorization; issues present in the original code may remain.
- Output involving process IDs, thread scheduling, or concurrency can vary between runs.

## Reference

**21CSC202J — Operating Systems Lab Manual**, SRM Institute of Science and Technology (course material provided for the extraction).

> For academic reference and learning. Credit for the supplied manual material belongs to its respective authors/institution.
