### Stepik C++ Multithreaded Programming
---

##### Exercise 2.1 (Derivative of polynomial)
- regex parsing
- std::map

##### Exercise 2.2 (Smart pointer)
- representation of smart pointer

##### Exercise 2.3 (Memory allocation)
- representation of memory allocator

##### Exercise 3.1 (Sockets)
- performance of local server
- performance of client
- sys/types.h
- sys/sockets.h
- netinet/in.h
- unistd.h

##### Exercise 3.2 (Chat)
- kqueue
- performance of chat server

##### Exercise 5.2.1 (Signals handlers)
- signal.h
- interrupt foreign signals

##### Exercise 5.2.2 (Zombie process)
- fork()
- waitpid() - waiting for chaild process exit code

##### Exercise 5.4.1 (Shell emulator)
- pipe();
- STDIN_FILENO, STDOUT_FILENO
- redirect std in/out

##### Exercise 5.4.2 (fifo stream)
- mkfifo()
- infinite read from one file and write to another

##### Exercise 5.4.3 (Processes pairing)
- socketpair()
- pair two separate processes

##### Exercise 6.2.1 (SysV Queue)
- ftok() / msgget() / msgrcv() / msgsnd() / msgctl()
- read from queue and write to file
- linked to real file in OS

##### Exercise 6.2.2 (POSIX Queue)
- mq_open() / mq_recieve() / mq_send() / mq_unlink() / mq_close()
-	read from queue and write to file
- not linked to file in OS

##### Exercise 6.3.1 (SysV Semaphore)
- ftok() / semget() / semctl()
- file access control

##### Exercise 6.3.1 (POSIX Semaphore)
- sem_open() / sem_wait() / sem_close() / sem_unlink()
- file access control

##### Exercise 6.4.1 (SysV Shared Memory)
- ftok() / shmget() / shmctl() / shmat() /shmdt()
- allocate shared memory segment

##### Exercise 6.4.2 (POSIX Shared Memory)
- shm_open() / ftruncate() / mmap() / munmap() / shm_unlink()
- allocate shared memory segment

##### Exercise 7.1 (POSIX Threads)
- pthread_t / pthread_create() / pthread_join() / pthread_detach()
- create thread, sent data to thread and recieve data back

##### Exercise 7.2 (Mutex and spinlock)
- pthread_mutex_t / pthread_spinlock_t / pthread_rwlock_t
- pthraed_mutex_lock() / pthread_spin_lock() / pthread_rwlock_wrlock()
- pthread_mutex_unlock() / pthread_spin_unlock() / pthread_rwlock_unlock()
- pthread_mutex_destroy() / pthread_spin_destroy() / pthread_rwlock_destroy()
- create different types of mutex

##### Exercise 7.3 (Conditional vars)
- pthread_cond_t / pthread_barrier_t / pthread_once_t
- pthread_cond_wait() / pthread_barrier_init() / pthread_barrier_wait()
- pthread_cond_destroy() / pthread_barrier_destroy()
- pthread_once()
- synchronise threads by make them wait

##### No Exercise 7.4 (C++11 Threads and mutexes)
- std::thread / .join() / .detach()
- std::mutex / .lock() / .trylock() / .unlock()
- std::unique_lock<std::mutex>
- std::condition_variable
- .wait() / .wait_for() /.wait_until() / .notify_one() /.notify_all()
- std::future<type> / std::async() / .get()
- C++11 thread tools

##### Exercise 8.3 (Multi-threading with OpenMP, Intel TBB and MPI)
- merge sort algorithm with OpenMP multi-threading

---
Link to curse: [C++ Multithreaded Programming](https://stepik.org/course/149/syllabus)
