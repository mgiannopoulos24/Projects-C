killall progDelay
./build/jobCommander issueJob ./build/progDelay 1000
./build/jobCommander issueJob ./build/progDelay 1000
./build/jobCommander issueJob ./build/progDelay 1000
./build/jobCommander issueJob ./build/progDelay 1000
./build/jobCommander issueJob ./build/progDelay 1000
./build/jobCommander issueJob ./build/progDelay 1000
./build/jobCommander setConcurrency 4
./build/jobCommander poll running
./build/jobCommander poll queued
./build/jobCommander stop job_4
./build/jobCommander stop job_5
./build/jobCommander poll running
./build/jobCommander poll queued
./build/jobCommander exit
