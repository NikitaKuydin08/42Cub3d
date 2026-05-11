#!/bin/bash

OUTPUT="results.txt"

> "$OUTPUT"

for map in maps/invalid/bad/*.cub
do
	./cub3D "$map" >> "$OUTPUT" 2>&1

	status=$?

	if [ $status -eq 139 ]
	then
		echo "SEGFAULT: $map" >> "$OUTPUT"
	fi
done
