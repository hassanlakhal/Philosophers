#!/bin/bash
for i in {1..100}
do
	./philo 100 800 200 200 7 |grep "$i is eating" | wc -l
done
