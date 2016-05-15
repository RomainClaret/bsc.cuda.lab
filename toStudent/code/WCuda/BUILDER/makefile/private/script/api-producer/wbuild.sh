#!/bin/bash
#
# Version:	0.0.2
#

set -e

#-----------------------------------------------
#		include
#-----------------------------------------------

source ${ROOT_SCRIPT}/workspace.sh
source ${ROOT_SCRIPT}/project.sh
source ${ROOT_SCRIPT}/tools.sh

#-----------------------------------------------
#		Input
#-----------------------------------------------

CBICC_OPTIONS="$@"

#-----------------------------------------------
#		Main
#-----------------------------------------------

processWorkspace

#-----------------------------------------------
#		end
#-----------------------------------------------


