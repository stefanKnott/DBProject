#!/bin/bash
#THIS IS FOR UBUNTU & DEBIAN

#install InfluxDB
wget http://influxdb.s3.amazonaws.com/influxdb_0.9.4.2_amd64.deb
sudo dpkg -i influxdb_0.9.4.2_amd64.deb

#Install Grafana
sudo apt-get install -y apt-transport-https
wget https://grafanarel.s3.amazonaws.com/builds/grafana_2.1.3_amd64.deb
sudo apt-get install -y adduser libfontconfig
sudo dpkg -i grafana_2.1.3_amd64.deb
#	Add the folowing line to your /etc/apt/sources.list file:
#	deb https://packagecloud.io/grafana/stable/debian/ wheezy main

curl https://packagecloud.io/gpg.key | sudo apt-key add -
sudo apt-get update
sudo apt-get install grafana

#Run both
sudo /etc/init.d/influxdb start
sudo service grafana-server start
