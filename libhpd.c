#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
//Read integer values from files like /proc/stat by table & row
int readtable(int row, int column, FILE *table) {
	char buff = 0;
	char sbuff[200];
	int ret = 0;
	if(table == NULL) {return -1;}
	
	
	fseek(table, 0, SEEK_SET);
	
	//move offset to specified row
	for (int i = 0; i < row; i++) {
	   while(fgetc(table) != 10) { // for looping until a newline is reached
	   			if(i == row) {break;}
	   		}
	}
	//This just moves the fp's offset to the specified column
	for (int i = 0; i < column; i++) {
		while(fgetc(table) != 32) { // for looping until a space is reached
			if(i == column) {break;}
		} 
	}
	int i = 0;
	while(buff != 32) {
		buff = fgetc(table);
		sbuff[i] = buff;
		i++;
	}
	
	ret = atoi(sbuff);
		
	return ret;
}
//Sister Function to readtable() for getting data from /proc/cpuinfo by processor & lines below
char * readcpuinfo(int processor, int line) {
	FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
	fseek(cpuinfo, 0, SEEK_SET);
	char buff = 0;
	char *ret = malloc (sizeof(char) * 50);
	int lines = processor*26+line;
	//move offset to specified processor & line
	for (int i = 0; i < lines; i++) {
	   while(fgetc(cpuinfo) != 10) { // for looping until a newline is reached
	   			if(i == lines) {break;}
	   		}
	}
	//move offset to the data values
	while(fgetc(cpuinfo) != 58){}   // for looping until a colon or EOF is reached   
	fgetc(cpuinfo); // move offset by one char to account for the space that comes after the :			
		
	
	int i = 0;
	while(true) { // put all chars into string from SEEK_CUR until a newline is hit
		buff = fgetc(cpuinfo);
		if(buff == 10){break;}
		ret[i] = buff;
		i++;
	}
	fclose(cpuinfo);
	return ret;
}
//Function for getting stats about cpu clock cycles from /proc/stat. core=-1 reads from all cores
int cpust(int core, int stat) {
	//Workaround for line 1 of /proc/stat since it has 2 spaces
	if(core == -1) {
		stat++;
	}
	FILE *statfile = fopen("/proc/stat", "r");
	int ret = readtable((core+1),stat, statfile);
	return ret;
}

//Function for getting 
int clockcyclet(int core) {
	int ret = 0;
	for(int i =0; i < 10; i++) {
		ret = ret + cpust(core, i);
	}
	return ret;
}
float cpustm(int core, int stat, int time) {
	int total1 = clockcyclet(core);
	int stat1 = cpust(core, stat);
	sleep(time);
	int total2 = clockcyclet(core);
	int stat2 = cpust(core, stat);

	int totald = total2-total1;
	int statd = stat2-stat1;
	
	float ret = (float)statd/totald;
	
	return ret;
}
long int cpuhz(int core) {
	long int ret;
	ret = atoi(readcpuinfo(core,9))*1000000;
	return ret;
}
float *cpustats(int core, int time) {
	float *ret = malloc(sizeof(float)*10);
	int stats[sizeof(float)*10];
	int stats2[sizeof(float)*10];
	int total1 = clockcyclet(core);
	for(int i=1; i<10; i++) {
		stats[i] = cpust(core, i);
	}
	sleep(time);
	int total2 = clockcyclet(core);
	for(int i=1; i<10; i++) {
			stats2[i] = cpust(core, i);
		}
	int totald = total2-total1;
	for(int i=1; i<10; i++) {
		ret[i] = (float)(stats2[i]-stats[i])/totald;
	}
	return ret;
}
