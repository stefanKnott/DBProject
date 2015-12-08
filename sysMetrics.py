import subprocess
import time
import datetime
import re

def frMemCmd():
    p1 = subprocess.Popen(["free", "-m"], stdout=subprocess.PIPE)
    p2 = subprocess.Popen(["grep", "+*.buffers"], stdin=p1.stdout, stdout=subprocess.PIPE)
    p3 = subprocess.Popen(["awk", "{print $4}"], stdin=p2.stdout, stdout=subprocess.PIPE)

    freeResp = p3.communicate()[0]
    freeResp = freeResp.replace("\n","")

    matchObj = re.match('shared(.*)', freeResp)
    if matchObj:
        return matchObj.group(1)

def cpuUtCmd():
    p1 = subprocess.Popen(["grep", "cpu", "/proc/stat"], stdout=subprocess.PIPE)
    p2 = subprocess.Popen(["awk", "{print ($2+$4)*100/($2+$4+$5)}"], stdin = p1.stdout, stdout=subprocess.PIPE)
        #get first reading
    cpuResp = re.match('(.*)\n', p2.communicate()[0])
    return cpuResp.group()

def ioStatCmd():
        #"iostat -x | awk '{print $1,$4,$5}'"
    p1 = subprocess.Popen(["iostat", "-x"], stdout=subprocess.PIPE)
    p2 = subprocess.Popen(["awk", "{print $1,$4,$5}"], stdin=p1.stdout, stdout=subprocess.PIPE)

    ioResp = re.match("Device:\s+(\w+)", p2.communicate()[0])#\s+r/s\s+w/s.(\w+-*\d*)\s+(\d+.\d+)\s+(\d+.\d+)", p2.communicate()[0])
    print ioResp
        #return ioResp.group()

def writeCpu(perc):
    subprocess.call(["curl", "-i", "-XPOST", "http://localhost:8086/write?db=sysMetrics", "--data-binary", "cpuUse,host=denprdinf0017,region=denver cpuUse=" + perc])

def writeMem(mb):
    subprocess.call(["curl", "-i", "-XPOST", "http://localhost:8086/write?db=sysMetrics", "--data-binary", "freeMem,host=denprdinf0017,region=denver freeMem=" + mb])

if __name__ == '__main__':
    dbUrl = "'http://localhost:8086/write?db=sysMetrics'"
    
    subprocess.call(["curl", "-G", "http://localhost:8086/query", "--data-urlencode", "q=create database sysMetrics"])
    subprocess.call(["curl", "-G", "http://localhost:8086/query", "--data-urlencode", "q=create retention policy two_days on sysMetrics duration 2d Replication 1 Default"])
    
    while True:
        memInfo = frMemCmd()
        cpuInfo =  cpuUtCmd()
        writeMem(memInfo)
        writeCpu(cpuInfo)
		sleep(2)
