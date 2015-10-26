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
