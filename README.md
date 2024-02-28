<!-- ahokcool HEADER START-->
---
<a id="top"></a>
<div align="center">
  <a href="https://github.com/ahokcool/ahokcool/blob/main/README.md">
    <img src="images/alexgit.png" alt="Logo" width="150">
  </a><br>
  An overview of all my projects can be found here: <a href="https://github.com/ahokcool/ahokcool/blob/main/README.md" target="_blank">ahokcool</a><br><br>
  <a href="https://www.42lisboa.com">
    <img src="images/logo42.svg" alt="Logo" width="100">
  </a><br>
  This project was created as part of my studies at: <a href="https://www.42lisboa.com" target="_blank">42 Lisboa</a><br>
</div>

---
<!-- ahokcool HEADER END-->
<!-- PROJECT HEADER START -->
<br />
<div align="center">
  <a href="./">
    <img src="images/logo.gif" alt="Logo" width="600">
  </a>
  <h1 align="center">philosophers</h1>
<p align="center">
    Write a program that simulates the life of a group of philosophers to learn the basics of threading a process an mutexes.
</p>
</div>
<br>
<!-- PROJECT HEADER END -->

## :bulb: Lessons learned
- multithreading in C
- race condition
- C mutex lock
- deadlocks

## Installation
```
$ git clone https://github.com/ahokcool/philosophers.git  # Clone
$ cd philosophers                                         # Change directory
$ make                                                    # Compile
$ ./philo 800 200 200 7                                   # Run
```

## More Information
This project is a version of the dinning philosopher problem <br>
[->Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
<br>

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/An_illustration_of_the_dining_philosophers_problem.png/800px-An_illustration_of_the_dining_philosophers_problem.png" width="300" />

| Common Problems  | My Solution |
| ------------- | ------------- |
| independent philos                | -> using threads  |
| race conditions                   | -> using pthread_mutex  |
| deadlocks                         | [-> resource hierarchy solution](https://medium.com/science-journal/the-dining-philosophers-problem-fded861c37ed)  |
| the starvation                    | -> wait for a lap time |

### The starvation solution
Every philo can see how many other philos are sitting at the table. Always half of the philos (result rounded down) can eat at the same time (exception: there is only one philo). Since in this variant all philos always eat the same amount of time, it can be calculated how long it takes until all have started to eat once. If each philo now waits until at least this time has passed before he eats again, nobody starves anymore. HOORAY! <br><br>
Formula<br>
``` table->min_wait_time = ((table->num_philos - (int)(table->num_philos / 2) - 1) * table->dur_eat) + (table->dur_eat * 0.5) ``` <br><br>
Note:<br>
I noticed that this wastes ```0.5*dur_eat``` ms per food round. So a philo could eat, but he does not.
So, since I did not come up with a solution, I simply adjusted the formula and waste now only ```5ms```. (which is still not ideal)<br>
New formula<br>
``` table->min_wait_time = ((table->num_philos - (int)(table->num_philos / 2) - 1) * table->dur_eat) + 5; ```

<!-- ahokcool FOOTER-->
---
<p align="center">
  <a href="#top">🔝 back to top 🔝</a>
</p>
