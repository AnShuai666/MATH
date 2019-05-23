#!/usr/bin/env bash

INSTALL_DIR="/usr/local"

rm -drf $INSTALL_DIR/include/MATH
rm -drf $INSTALL_DIR/lib/MATH
rm -drf $INSTALL_DIR/bin/MATH
rm -drf $INSTALL_DIR/share/MATH

#需要加条件 移除成功才显示
echo "移除文件夹:$INSTALL_DIR/include/MATH"
echo "移除文件夹:$INSTALL_DIR/lib/MATH"
echo "移除文件夹:$INSTALL_DIR/bin/MATH"
echo "移除文件夹:$INSTALL_DIR/share/MATH"