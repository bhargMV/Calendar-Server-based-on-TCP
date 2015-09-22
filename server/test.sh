#!/bin/bash
for i in `seq 1 100000`;
do
	echo "`echo "mourya add 12345 1 1 1"| nc localhost 8778 `"
	sleep 2
done
