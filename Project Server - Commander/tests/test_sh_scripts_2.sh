./multijob.sh commands_3.txt
./jobCommander setConcurrency 4
./multijob.sh commands_4.txt
./allJobsStop.sh
./jobCommander  poll running
./jobCommander  poll queued
ps -aux | grep ./progDelay
