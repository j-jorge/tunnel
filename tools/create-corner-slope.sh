#!/bin/sh

if [ $# -eq 0 ]
then
    echo usage $0 image_to_bend.png
    exit
fi

# The image must be seamless on its right but bend-image applies the texture
# starting from the left. In order to obtain the expected result, we do
# everything in mirror and we flip the result horizontally.

TMP_SOURCE=$(mktemp)

convert "$1" -flop $TMP_SOURCE

bend-image 256 256 $TMP_SOURCE <<EOF
0 0 0 0 175 0
256 64 256 32 256 64
EOF

mogrify -flop output.png

rm $TMP_SOURCE
