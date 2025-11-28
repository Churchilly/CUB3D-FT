#!/bin/bash

valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --verbose \
    --log-file=valgrind-report.log \
    --show-reachable=yes \
    --track-fds=yes \
    --error-limit=no \
    ./cub3d
