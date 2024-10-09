#!/bin/bash

# Stopping all jobs
jobCommander poll running | awk '{print $1}' | xargs -I {} jobCommander stop {}
jobCommander poll queued | awk '{print $1}' | xargs -I {} jobCommander stop {}
