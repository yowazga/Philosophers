# 🧠 Philosophers

> “I never thought philosophy would be so deadly…”

## 📌 Project Overview

The **Philosophers** project is part of the 42 core curriculum. It introduces you to the **basics of concurrency** by simulating the famous *Dining Philosophers Problem*. This classic exercise is all about managing shared resources (forks) between competing threads (philosophers) without causing deadlocks or starvation.

You'll learn how to use **POSIX threads (pthreads)**, **mutexes**, and optionally **semaphores** to coordinate actions like eating, sleeping, and thinking — all under strict timing constraints.

---

## 🎯 Objectives

- Understand and implement **thread synchronization** using `pthread_mutex`.
- Prevent **data races** and **deadlocks** in a concurrent environment.
- Simulate real-time behaviors using precise timestamps and sleeping mechanisms.
- Explore **process-based concurrency** and **semaphores** in the bonus.

---

## 🔧 How It Works

Each philosopher:
- Eats when they can grab **two forks** (mutexes).
- Sleeps after eating.
- Thinks after sleeping.
- **Dies** if they don’t eat within a given `time_to_die`.

Simulation stops:
- If any philosopher dies.
- Or if all philosophers have eaten a required number of times (optional).

---

## ⚙️ Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- **number_of_philosophers**: Total philosophers (and forks).

- **time_to_die**: Max time before a philosopher dies without eating.

- **time_to_eat**: Duration of eating.

- **time_to_sleep**: Duration of sleeping.

- **number_of_times_each_philosopher_must_eat** (optional): Ends simulation when all have eaten this many times.

## 🧪 Example
```bash
./philo 5 800 200 200
```
Simulates 5 philosophers with:

- 800ms before dying

- 200ms to eat

- 200ms to sleep

Expected log output:
```csharp
0 1 is thinking
5 1 has taken a fork
10 1 has taken a fork
15 1 is eating
...
```

## 💡 Implementation Details

✅ Mandatory (Threads + Mutexes)
- Each philosopher is a thread.

- Each fork is a mutex.

- Precise timing using gettimeofday() and usleep().

- Log output is protected to avoid message collision.

🌟 Bonus (Processes + Semaphores)
- Each philosopher is a process, managed by the parent.

- Forks are protected with a semaphore.

- Uses sem_open, sem_wait, sem_post, etc.

- Proper cleanup with sem_unlink.

## 🔥 Challenges Solved
- Preventing deadlocks with staggered fork acquisition.

- Detecting starvation in real-time with a monitor thread.

- Ensuring clean exit and no resource leakage.

- Managing simultaneous access to logs and forks.
