
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
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
        
        char url[] = " '192.168.100.20:8086/db/sysMetrics/series?u=root&p=root'";
        char cmd[] = "curl -X POST -d";
        char data[150];
        
        sprintf(data, "'[{\"name\":\"%s\",\"columns\":[\"Total\", \"Free\", \"Used\", \"Configured Proc\", \"Online Proc\"], \"points\":[[%lu, %lu, %lu, %lu, %lu]]}]'", "sysInfo", totalsize, totalfree, totalused, procconf, proconln);
    
        char curlCMD[300];
        sprintf(curlCMD, "%s %s %s", cmd, data, url);
        printf("CURL CMD: %s\n", curlCMD);
    
        system(curlCMD);
    }

    return 0;
}
