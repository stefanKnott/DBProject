#!/bin/bash
#THIS IS FOR REDHAT & CENTOS

#install InfluxDB
wget http://influxdb.s3.amazonaws.com/influxdb-0.9.4.2-1.x86_64.rpm
sudo yum localinstall influxdb-0.9.4.2-1.x86_64.rpm


#Install Grafana
sudo yum install https://grafanarel.s3.amazonaws.com/builds/grafana-2.1.3-1.x86_64.rpm

#Run both
sudo /etc/init.d/influxdb start
sudo service grafana-server start

#Create sysMetrics DB
/opt/influxdb/influx
CREATE DATABASE sysMetrics
exit

#now compile sysMetrics
make sysMetrics

#get local IP addr for data input and front end visualization
#get CentOS version with cat regex on /etc/*release*
#when running ip addr:
#	Centos 6: IP address is listed eth0
#	Centos 7: IP address is listed enp0s3
	
#	Write program to run 'ip addr | grep <<ethLabel>> | awk '{print $2}' | tail -1 '
#	pipe this into a program which does more formal regex matching to determine legitimate ip address


#Get cpu usage -- this sums use from user and system, will be useful for data population program
#top -d 0.5 -b -n2 | grep "Cpu(s)"|tail -n 1 | awk '{print $2 + $4}'

#Get amount of "free" memory on machine in MB
#free -m | grep '+.*buffers' | awk '{print $4}'


