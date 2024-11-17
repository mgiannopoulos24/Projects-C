./scripts/multijob.sh ./tests/commands_3.txt
./build/jobCommander setConcurrency 4
./scripts/multijob.sh ./tests/commands_4.txt
./scripts/allJobsStop.sh
./build/jobCommander  poll running
./build/jobCommander  poll queued
ps -aux | grep ./build/progDelay
