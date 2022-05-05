#!/bin/bash

for i in {1..20}
do
    dd if=/dev/random of=/tmp/testout bs=204800 count=1500 2>> onlydd-ddbigprint
    rm /tmp/testout
done

for i in {1..20}
do
    dd if=/dev/random of=/tmp/testout bs=2048 count=100000 2>> onlydd-ddsmallprint
    rm /tmp/testout
done

for i in {1..20}
do
    ./small 5 noprints >> small-ddnoprint
done

for i in {1..20}
do
    dd if=/dev/random of=/tmp/testout bs=204800 count=1500 2>> big-ddbigprint & ./small 5 bigprints >> small-ddbigprint &
    sleep 10
    rm /tmp/testout
done

for i in {1..20}
do
    dd if=/dev/random of=/tmp/testout bs=2048 count=100000 2>> big-ddsmallprint & ./small 5 smallprints >> small-ddsmallprint &
    sleep 10
    rm /tmp/testout
done

for i in {1..20}
do
    ./small 5 sstest >> small-small1 & ./small 5 sstest2 >> small-small2 &
    sleep 6
done