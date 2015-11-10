#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[]){
    //Get metrics
    long numpages, pagesize, totalsize, totalfree, totalused, freepages, procconf, proconln;
    while (1){
        //get info
        
        freepages = sysconf( _SC_AVPHYS_PAGES);
        numpages = sysconf(_SC_PHYS_PAGES);
        pagesize = sysconf(_SC_PAGESIZE);
        procconf = sysconf(_SC_NPROCESSORS_CONF);
        proconln = sysconf(_SC_NPROCESSORS_ONLN);
        
        totalsize = numpages * pagesize;
        totalfree = pagesize * freepages;
        totalused = totalsize - totalfree;
        
        //curl into influxDB
	char cpuCMD[100] = "top -d 0.5 -b -n2 | grep 'Cpu(s)'|tail -n 1 | awk '{print $2 + $4}'";
	int cpuUsage = system(cpuCMD);
	char url[] = " 'http://localhost:8086/write?db=sysMetrics'";
	char cmd[] = "curl -i -XPOST";
	char data[150];
	sprintf(data, "--data-binary 'sysInfo,host=denprdinf0017,cpuUsage=%d freeMem=%lu'", cpuUsage, totalfree);

	char curlCMD[300];
	sprintf(curlCMD, "%s %s %s", cmd, data, url);
	printf("CURL CMD: %s\n", curlCMD);

	system(curlCMD);
    }

    return 0;
}
