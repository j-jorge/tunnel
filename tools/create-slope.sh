#!/bin/sh

generate_points_bump()
{
    cat <<EOF
0 0 0 0 255 0
512 256 384 128 512 256
1024 768 1024 768 1264 1024
1536 1024 1418 1024 1536 1024
EOF
} # generate_points_bump()

get_size_bump()
{
    cat <<EOF
1536 1280
EOF
} # get_size_bump()

if [ $# -le 1 ]
then
    echo "usage $0 [ bump | gentle | sin | steep ] image_to_bend.png"
    exit
fi

get_size_$1 \
    | (
    read WIDTH HEIGHT
    TMP_POINTS=$(mktemp)
    generate_points_$1 >$TMP_POINTS

    echo "run  $WIDTH $HEIGHT $2 < $TMP_POINTS" | gdb --args bend-image

    rm $TMP_POINTS
)
