#! /bin/sh
#
# vec.sh
# Copyright (C) 2019 k <k@hlst>
#
# Distributed under terms of the MIT license.
#
posW=50
posH=50
negW=500
negH=500
numStages=30

rm *.txt *.vec -rf

numPos=`./tools/build/resizeImg -p ./posdata -w $posW  -h $posH  -s -o pos.txt -O posdata.txt`
numNeg=`./tools/build/resizeImg -p ./negdata -w $negW -h $negH -s -o neg.txt -O negdata.txt`

opencv_createsamples -vec pos.vec -info pos.txt -num $numPos -w $posW -h $posW
opencv_createsamples -vec neg.vec -info neg.txt -num $numNeg -w $negH -h $negH

# -featureType LBP\
cmd="opencv_traincascade \
	-data xml \
	-vec pos.vec \
	-bg negdata.txt \
	-numPos $(expr $numPos) \
	-numNeg $(expr $numNeg) \
	-numStages $numStages \
	-w $posW \
	-h $posH \
	-numThreads 24 \
	-precalcValBufSize 2048 \
	-mode ALL"
echo $cmd
$cmd

