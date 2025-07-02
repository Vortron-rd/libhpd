# lib Hardware performance data

A library for quickly and easily accessing data about hardware performance on linux-based systems.
This is mainly a learning project for now and only includes a minimal set of functions.
## Function Checklist (Incomplete)

[x] int cpust(char * stat, int core); Gives Total clock ticks that the core has spent on a specific type of task.
[x] float cpustm(int core, int stat, int time); Get Measurements over time about a stat's share in clock ticks spent.
[x] float cpuhz();  Gives the amount of Hertz the cpu is running at.
