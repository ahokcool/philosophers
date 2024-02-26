## Philosophers
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