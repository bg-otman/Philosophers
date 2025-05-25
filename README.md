# Philosophers - 42 Project

> A simulation of the classic Dining Philosophers problem using multithreading and multiprocessing in C.

## 🧠 Project Overview

This project is part of the 42 school curriculum. It is a concurrency problem designed to familiarize students with thread management, mutexes, semaphores, and process synchronization in C.

The challenge is to prevent deadlocks and data races while simulating philosophers sitting around a table, thinking, eating, and sleeping.

## 📁 Contents

This repository contains:
- ✅ **Mandatory part**: A multithreaded version using `pthread`.
- ⭐ **Bonus part**: A multiprocess version using `semaphores`.

---

## ⚙️ Mandatory Part

### Description

- Implemented using **one thread per philosopher**.
- Uses **mutexes** to represent forks.
- Ensures:
  - No philosopher dies unexpectedly.
  - No two philosophers use the same fork simultaneously.
  - Philosophers eat, sleep, and think according to timing parameters.

### Compilation

```bash
make
```

### Execution

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

### Arguments

- `number_of_philosophers`: Number of philosophers (and forks).
- `time_to_die`: Time (ms) before a philosopher dies without eating.
- `time_to_eat`: Time (ms) a philosopher takes to eat.
- `time_to_sleep`: Time (ms) a philosopher takes to sleep.
- `number_of_times_each_philosopher_must_eat` (optional): If provided, the simulation ends when all philosophers have eaten at least this many times.

---

## 🧪 Bonus Part

### Features

- Implemented using **one process per philosopher**.
- Uses **semaphores** for fork access, printing, and meal tracking.
- Includes a **supervisor process** to monitor death and end conditions.

### Compilation

```bash
make bonus
```

### Execution

```bash
./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

---

## 🔧 Implementation Notes

- Written in **C99**, using standard POSIX functions.
- Emphasis on:
  - Preventing **deadlocks**.
  - **Precise time tracking** with `gettimeofday`.
  - Clean resource management and memory deallocation.
- In the bonus part, **semaphores** are unlinked and properly cleaned to prevent leaks.

---

## 📷 Sample Output

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
...
```

---

## 📚 What I Learned

- Fine-grained synchronization using **mutexes** and **semaphores**.
- Managing concurrency in both **threads** and **processes**.
- Implementing **monitoring threads/processes**.
- Handling edge cases like **1 philosopher**, **timing precision**, and **simultaneous death conditions**.

---

## 📄 License

This project is part of the [1337/42] school curriculum.

---
