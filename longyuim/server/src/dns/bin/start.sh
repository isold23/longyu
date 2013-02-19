#!/bin/sh

rm -rf ${PWD}/dns/bin/*log
nohup ${PWD}/dns/bin/dns -f ../conf/dns.conf > /dev/null &
