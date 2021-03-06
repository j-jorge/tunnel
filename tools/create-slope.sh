#!/bin/sh

print_anchors_positions()
{
    while read PX PY IX IY OX OY
    do
        if [ -z "$IX" ]
        then
            echo "in" 0 0 "[ $PX $PY ]" "out" 0 0
        else
            echo "in" $(( $IX - $PX )) $(( $IY - $PY )) \
                "[ $PX $PY ]" \
                "out" $(( $OX - $PX )) $(( $OY - $PY ))
        fi
    done
}

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
1024 256
2048 768
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

generate_points_sin()
{
    cat <<EOF
0 0 0 0 178 0
512 142 366 62 806 294
1024 512
1536 1024
2048 1394 1754 1242 2204 1474
2560 1536 2382 1536 2560 1536
EOF
} # generate_points_sin()

get_size_sin()
{
    cat <<EOF
2560 1792
EOF
} # get_size_sin()

if [ $# -ge 1 ]
then
    generate_points_$1 | print_anchors_positions
fi

if [ $# -ne 2 ]
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
