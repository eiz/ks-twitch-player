#!/bin/bash

if [ "$STEAMLINK_HOST" == "" ]; then
    echo "STEAMLINK_HOST must be set."
    exit 1
fi

scp -r build/* root@${STEAMLINK_HOST}:/mnt/disk

