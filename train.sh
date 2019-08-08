#! /bin/sh
#
# vec.sh
# Copyright (C) 2019 k <k@hlst>
#
# Distributed under terms of the MIT license.
#

posW=200
posH=50
negW=400
negH=100
numStages=30
trainDir=train

if [ 0 == $# ]
    then
    echo "没有传入参数，退出"
    exit
fi

objectBox=$1

if ((1 < $# ))
    then
    trainDir=$2
fi

rm $trainDir -rf
mkdir $trainDir
mkdir ./$trainDir/posdata
mkdir ./$trainDir/negdata
mkdir ./$trainDir/xml
numPos=`./tools/build/resizeImg -p $objectBox/posdata -P ./$trainDir/posdata -w $posW -h $posH -s -o ./$trainDir/pos.txt -O ./$trainDir/posdata.txt`
numNeg=`./tools/build/resizeImg -p $objectBox/negdata -P ./$trainDir/negdata -w $negW -h $negH -s -o ./$trainDir/neg.txt -O ./$trainDir/negdata.txt`

opencv_createsamples -vec ./$trainDir/pos.vec -info ./$trainDir/pos.txt -num $numPos -w $posW -h $posH
opencv_createsamples -vec ./$trainDir/neg.vec -info ./$trainDir/neg.txt -num $numNeg -w $negW -h $negH

# -featureType LBP\
cmd="opencv_traincascade \
	-data ./$trainDir/xml \
	-vec ./$trainDir/pos.vec \
	-bg ./$trainDir/negdata.txt \
	-numPos $(expr $numPos) \
	-numNeg $(expr $numNeg) \
	-numStages $numStages \
	-w $posW \
	-h $posH \
	-numThreads 24 \
	-precalcValBufSize 2048 \
	-mode ALL"
echo "===========================>"
echo "||"
echo "||  $cmd "
echo "||"
echo "===========================>"
$cmd

