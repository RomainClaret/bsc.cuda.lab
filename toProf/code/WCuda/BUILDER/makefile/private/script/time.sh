#!/bin/bash
#


# ---------------------------------------
#                input
#----------------------------------------

# $@ : all para


title=$1
timeStart=$2

# ---------------------------------------
#               private
#----------------------------------------


timeStop=$(date +%s)

echo "$title $(($timeStop - $timeStart)) (s)"

# ---------------------------------------
#               end
#----------------------------------------
