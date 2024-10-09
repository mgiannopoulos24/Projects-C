killall progDelay
./jobCommander issueJob ./progDelay 1000
./jobCommander issueJob ./progDelay 1000
./jobCommander issueJob ./progDelay 1000
./jobCommander issueJob ./progDelay 1000
./jobCommander issueJob ./progDelay 1000
./jobCommander issueJob ./progDelay 1000
./jobCommander setConcurrency 4
./jobCommander poll running
./jobCommander poll queued
./jobCommander stop job_4
./jobCommander stop job_5
./jobCommander poll running
./jobCommander poll queued
./jobCommander exit
