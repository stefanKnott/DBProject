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
	
#	run ip addr >> match on eth0/enp0s3 >> match on inet <<IP ADDR>>
#	run ./sysMetric <<IP ADDR>>
