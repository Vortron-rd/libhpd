#ifndef LIB_TDATA
	#define LIB_TDATA
	#define STAT_USER 1
	#define STAT_NICE 2
	#define STAT_SYSTEM 3
	#define STAT_IDLE 4
	#define STAT_IOWAIT 5
	#define STAT_IRQ 6
	#define STAT_SOFTIRQ 7
	#define STAT_STEAL 8
	#define STAT_GUEST 9
	#define STAT_GUEST_NICE 10
	 int cpust(int stat, int core); //Total clock ticks that the core has spent on a specific type of task. (set core=-1 for all cores)
	 float cpustm(int core, int stat, int time); //Get Measurements over time about a stat.
	 float *cpustats(int core, int time); //Gets measurements over time for all stats under a given core and returns them in an array.
	 float cpuhz(); // Hertz the cpu is running at.
#endif
