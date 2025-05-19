# Philosophers Project Documentation

## Project Overview

The goal of this project is to implement a solution to the classic _Dining Philosophers Problem_, avoiding deadlocks and ensuring proper synchronization using threads, mutexes, and other concurrency tools in C.

The Dining Philosophers problem involves a number of philosophers sitting at a table, each alternating between thinking and eating. Between each pair of philosophers is a fork, and a philosopher must pick up both the left and right forks (mutexes) to eat. The challenge is to design a system where philosophers can eat without resulting in deadlocks (where no progress can be made) or starvation (where a philosopher never gets to eat).

---

## Solution Method

### Key Features

- Each philosopher is represented by a separate thread.
- Forks are represented by mutexes.
- To prevent deadlocks:
  - Forks are always picked up in a specific order.
  - For three philosophers, a "turn" mechanism is used to serialize access to forks.
- A monitor (supervisory) thread checks if any philosopher has starved or if all have finished the required meals.

### Deadlock avoidance

- For an even number of philosophers, forks are picked up in alternating order depending on philosopher ID (even/odd).
- For three philosophers, a strict turn-taking order is enforced using a mutex-protected turn variable.

---

## Execution Flow

1. **Initialization**
   - Parse and check arguments.
   - Initialize program data, philosophers, mutexes, and threads.
   - For odd numbers, special grouping logic is used for philosophers.

2. **Philosopher Routine**
   - Each philosopher thread runs a loop:
     - Waits for its turn (if 3 philosophers).
     - Tries to pick up forks (mutexes).
     - Eats for a specified time.
     - Puts down forks.
     - Sleeps for a specified time.
     - Thinks.

3. **Monitor Routine**
   - Supervisory thread checks if any philosopher has starved (exceeded `t_die` since last meal) or if all have eaten enough times.

4. **Termination**
   - If a philosopher dies or all have eaten enough, all threads are notified to stop.
   - Resources are cleaned up and mutexes destroyed.

---

## Execution Flow Illustration

```
+-------------------+
|   Program Start   |
+-------------------+
          |
          v
+----------------------+
|  Parse Arguments     |
+----------------------+
          |
          v
+-------------------------+
| Initialize Data/Mutexes |
+-------------------------+
          |
          v
+-----------------------------------+
|  Create Philosopher & Monitor     |
|             Threads               |
+-----------------------------------+
          |
          v
+-----------------------------------+
|      Philosopher Routine          |
| (Eat, Sleep, Think, Repeat)       |
+-----------------------------------+
          |
          v
+----------------------+
|  Monitor Routine     |
|  (Check death/meal)  |
+----------------------+
          |
          v
+--------------------------+
|  End: Clean Up Resources |
+--------------------------+
```

---

## Structs and Their Roles

### `t_philo` (Philosopher Structure)
| Field            | Type              | Description                                           |
|------------------|-------------------|-------------------------------------------------------|
| `id`             | int               | Philosopher's index                                   |
| `meals`          | int               | Number of times this philosopher has eaten            |
| `last_meal_time` | long long         | Timestamp of last meal                                |
| `lfork`          | pthread_mutex_t*  | Pointer to left fork mutex                            |
| `rfork`          | pthread_mutex_t*  | Pointer to right fork mutex                           |
| `meal_mtx`       | pthread_mutex_t   | Mutex for protecting `meals` and `last_meal_time`     |
| `prog`           | t_prog*           | Pointer to main program structure                     |

### `t_prog` (Program Structure)
| Field            | Type               | Description                                         |
|------------------|--------------------|-----------------------------------------------------|
| `philo_count`    | int                | Number of philosophers                              |
| `t_die`          | int                | Time (ms) a philosopher survives without eating     |
| `t_eat`          | int                | Time (ms) spent eating                              |
| `t_sleep`        | int                | Time (ms) spent sleeping                            |
| `meals_required` | int                | Optional: meals needed to finish simulation         |
| `start`          | long long          | Simulation start time                               |
| `dead`           | int                | 1 if a philosopher has died                         |
| `dead_mtx`       | pthread_mutex_t    | Mutex for accessing `dead`                          |
| `print_mtx`      | pthread_mutex_t    | Mutex for printing states                           |
| `forks`          | pthread_mutex_t*   | Array of fork mutexes                               |
| `threads`        | pthread_t*         | Array of philosopher thread IDs                     |
| `monitor`        | pthread_t*         | Monitor thread ID                                   |
| `philos`         | t_philo*           | Array of philosopher structures                     |
| `turn_mtx`       | pthread_mutex_t    | Mutex for turn logic (3 philosophers)               |
| `turn`           | int                | Current turn (3 philosophers)                       |

---

## Key Functions

### Initialization

- **`check_args(int ac, char **av)`**  
  Validates command-line arguments for correctness.

- **`prog_args_init(t_prog *prog, int ac, char **av)`**  
  Initializes program parameters from arguments (number of philosophers, times, meals).

- **`mutexes_init(t_prog *prog)`**  
  Initializes all mutexes (forks, print, dead, turn).

- **`philos_init(t_prog *prog)`**  
  Initializes all philosopher structs and assigns forks.

### Philosopher Actions

- **`philo_thread(void *arg)`**  
  Main routine for philosopher threads. Loop: eat, sleep, think.

- **`philo_thread3(void *arg)`**  
  Special routine for three philosophers, uses turn-based eating.

- **`eat_action(t_philo *philo)` / `eat3_action(t_philo *philo)`**  
  Handles picking forks, eating, updating meal count and time.

- **`sleep_think(t_philo *philo)`**  
  Handles sleeping and thinking actions, with prints.

- **`take_forks3(t_philo *philo)`**  
  For three philosophers: properly locks forks according to turn.

### Monitoring

- **`djikstra_mon(void *arg)`**  
  Monitor thread that checks for dead philosophers and meal completion.

- **`check_meals_count(t_philo *philo)`**  
  Checks if a philosopher has eaten enough.

- **`check_if_all_ate(t_prog *prog)`**  
  Checks if all philosophers have eaten enough.

### Utility

- **`set_last_meal(t_philo *philo)`**  
  Updates last meal time and increments meal count.

- **`get_last_meal(t_philo *philo)`**  
  Returns last meal time.

- **`set_dead(t_philo *philo)`**  
  Sets `dead` flag in the program.

- **`get_dead(t_prog *prog)`**  
  Returns the dead flag.

- **`print_state(t_philo *philo, char *state)`**  
  Prints the philosopher's state (eating, thinking, sleeping, died).

### Cleanup

- **`prog_clean(t_prog *prog)`**  
  Joins all threads, destroys all mutexes, and frees memory.

---

## Notes on Implementation

- Mutexes are used rigorously for all shared data (forks, dead flag, meal counters, printing, turn).
- Special logic for three philosophers prevents starvation and deadlock via a "turn" mechanism.
- All major program states and actions are announced via thread-safe printing.
- The monitor thread ensures simulation ends on a philosopher's death or when all have eaten enough.

---

## How to Run

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
- Example: `./philo 5 800 200 200 7`
  - 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms, must eat 7 times

---

## Conclusion

This implementation provides a robust, deadlock-free solution to the Dining Philosophers problem using threads and mutexes, with careful attention to edge cases and starvation. The code is modular and extensible for further concurrency learning.
