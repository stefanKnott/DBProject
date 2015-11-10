#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[]){
    //Get metrics
 char freeCMD[] = "free -m | grep '+.*buffers' | awk '{print $4}'";
        char cpuCMD[100] = "grep 'cpu ' /proc/stat | awk '{print ($2+$4)*100/($2+$4+$5)}'";
        char url[] = " 'http://localhost:8086/write?db=sysMetrics'";
        char cmd[] = "curl -i -XPOST";
        int freeMem, cpuUseage;

        while (1){
        //get info
                FILE *in;
                extern FILE *popen();
                char buff[512];

                if(!(in = popen(freeCMD, "r"))){
                        exit(1);
                }

                while(fgets(buff, sizeof(buff), in)!=NULL){
                        freeMem = atoi(buff);
                }


                if(!(in = popen(cpuCMD, "r"))){
                        exit(1);
                }
                while(fgets(buff, sizeof(buff), in)!=NULL){
                        printf("CPU use: %s\n", buff);
                        cpuUseage = atoi(buff);
                }

                pclose(in);

                //CPU USEAGE
                //curl into influxDB
                char data[150];
                sprintf(data, "--data-binary 'cpuUse,host=denprdinf0017,region=denver cpuUsage=%d'", cpuUseage);
         
                char curlCMD[300];

		sprintf(curlCMD, "%s %s %s", cmd, data, url);
                system(curlCMD);

                char mdata[150];
                sprintf(mdata, "--data-binary 'freeMem,host=denprdinf0017,region=denver freeMem=%d'", freeMem);

                char memCMD[300];
                sprintf(memCMD, "%s %s %s", cmd, mdata, url);
                system(memCMD);

                sleep(1);
	}
    return 0;
}
