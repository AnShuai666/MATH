#!/bin/bash

if [ "$#" -eq 0 ]
then
    echo "利用默认安装路径:/usr/local"
    INSTALL_DIR="/usr/local"
elif [ "#$" -eq 1 ]
then
    echo "利用用户自定义安装文件夹:$1"
    INSTALL_DIR=$1
else
    echo "ERROR"
fi

#rm -drf build
rm -drf $INSTALL_DIR/include/MATH
rm -drf $INSTALL_DIR/lib/MATH
rm -drf $INSTALL_DIR/bin/MATH
rm -drf $INSTALL_DIR/share/MATH



#mkdir build
#chmod -R 777 build/ build/*
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
make
make install