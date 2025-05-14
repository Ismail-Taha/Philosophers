# Philosophers Project - Mandatory Part Explanation

The Philosophers project is a classic concurrency problem that involves managing shared resources (forks) among multiple threads (philosophers) while avoiding deadlocks and ensuring proper synchronization. Below is a detailed explanation of the concepts and implementation used in the mandatory part of the project.

---

## 1. Problem Overview

The problem simulates a group of philosophers sitting around a table. Each philosopher alternates between three states:
- **Thinking**
- **Eating**
- **Sleeping**

To eat, a philosopher needs to pick up two forks (one on their left and one on their right). The challenge is to ensure that:
1. No two philosophers use the same fork simultaneously.
2. Deadlocks are avoided (e.g., all philosophers waiting indefinitely for forks).
3. The program terminates when all philosophers have eaten a specified number of times or when a philosopher dies due to starvation.

---

## 2. Key Concepts Used

### 2.1 Threads
Each philosopher is represented as a thread. Threads allow concurrent execution, enabling philosophers to perform their routines (thinking, eating, sleeping) independently.

### 2.2 Mutexes
Mutexes (mutual exclusions) are used to protect shared resources (forks) from being accessed by multiple threads simultaneously. Each fork is represented by a mutex.

### 2.3 Synchronization
Synchronization ensures that threads operate in a coordinated manner. For example:
- A philosopher must wait for both forks to be available before eating.
- The simulation must stop when a philosopher dies or all have eaten enough.

### 2.4 Shared Data Structures
The program uses shared data structures to store information about the philosophers, forks, and simulation state. Access to these structures is synchronized using mutexes.

---

## 3. Implementation Details

### 3.1 Philosopher Routine
Each philosopher thread executes the following routine:
1. **Thinking**: The philosopher thinks for a while.
2. **Eating**: The philosopher:
   - Locks the mutexes for the two forks.
   - Eats for a specified duration.
   - Unlocks the mutexes for the forks.
3. **Sleeping**: The philosopher sleeps for a specified duration.

### 3.2 Grim Reaper Thread
A separate thread (the "grim reaper") monitors the philosophers to:
- Detect if a philosopher has died (i.e., hasn't eaten within the `time_to_die` limit).
- Check if all philosophers have eaten the required number of times.

If either condition is met, the simulation stops.

### 3.3 Fork Assignment
Each philosopher is assigned two forks:
- The fork on their left.
- The fork on their right.

To avoid deadlocks, the order in which forks are picked up is alternated for even- and odd-numbered philosophers.

### 3.4 Simulation Stop
The simulation stops when:
- A philosopher dies.
- All philosophers have eaten the required number of times.

A shared flag (`sim_stop`) is used to signal the end of the simulation. Access to this flag is synchronized using a mutex.

---

## 4. Code Structure

### 4.1 Key Files
- **`philo/sources/main.c`**: Entry point of the program. Initializes the simulation and starts the philosopher threads.
- **`philo/sources/init.c`**: Handles initialization of data structures, mutexes, and threads.
- **`philo/sources/philosopher.c`**: Contains the philosopher routine.
- **`philo/sources/grim_reaper.c`**: Implements the grim reaper thread.
- **`philo/sources/output.c`**: Handles printing of philosopher statuses.
- **`philo/includes/philo.h`**: Header file containing structure definitions and function prototypes.

### 4.2 Key Structures
- **`t_table`**: Represents the simulation table. Contains information about the philosophers, forks, and simulation state.
- **`t_philo`**: Represents a philosopher. Contains information about the philosopher's state, assigned forks, and last meal time.

---

## 5. Avoiding Deadlocks

Deadlocks are avoided by:
1. Alternating the order in which forks are picked up for even- and odd-numbered philosophers.
2. Using a "lone philosopher" routine for cases where there is only one philosopher.

---

## 6. Debugging and Output

The program includes options for debugging and formatted output:
- **Debug Mode**: Provides detailed logs for debugging.
- **Formatted Output**: Displays philosopher statuses in a user-friendly format.

---

## 7. Challenges and Solutions

### 7.1 Starvation
Starvation occurs when a philosopher cannot eat due to resource contention. This is mitigated by ensuring that philosophers take turns accessing forks
