#ifndef LIB_TDATA
	#define LIB_TDATA
	 int cpust(char * stat, int core); //Total clock ticks that the core has spent on a specific type of task. (set core=-1 for all cores)
	 float cpustm(int core, int stat, int time); //Get Measurements over time about a stat.
	 float cpuhz(); // Hertz the cpu is running at.
#endif
