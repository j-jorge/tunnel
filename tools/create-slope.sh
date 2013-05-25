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

generate_points_gentle()
{
    cat <<EOF
0 0 0 0 176 0
512 72 354 32 806 146
1024 256 1024 256 1024 256
2048 768 2048 768 2048 768
2560 954 2265 878 2716 994
3072 1024 2894 1024 3072 1024
EOF
} # generate_points_gentle()

get_size_gentle()
{
    cat <<EOF
3072 1280
EOF
} # get_size_gentle()

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
