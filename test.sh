#!/bin/bash
for i in {1..50}
do
	echo -n $i
	./philo 50 800 200 200 7 |grep "$i is eating" | wc -l
done
