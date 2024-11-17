#!/bin/bash

# Stopping all jobs
./build/jobCommander poll running | awk '{print $1}' | xargs -I {} ./build/jobCommander stop {}
./build/jobCommander poll queued | awk '{print $1}' | xargs -I {} ./build/jobCommander stop {}
