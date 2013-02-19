#!/bin/sh

rm -rf ${PWD}/dcs/bin/*log
nohup ${PWD}/dcs/bin/dcs -f ../conf/dcs.conf > /dev/null &
