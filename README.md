Store system metric info (free RAM, cpu utilization, r/s and w/s) in InfluxDB, display this data to the front end via Grafana

To run:
	Go through setup.sh to make sure Influx and Grafana are installed
	Create dashboard in Grafana at localhost:3000 to read info from measurements cpuUse and freeMem in sysMetrics database
	run: python sysMetrics.py to begin inserting metric data into Influx, this data will then be visualized at the Grafana dashboard
