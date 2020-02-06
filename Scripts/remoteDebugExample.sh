#!/bin/bash
# the script supports copying files used in remote debugging for SLM,DSP 
# and SoundEncoding
# usage ./remoteDebug ip_addr binary_executeable
set -e

ip_addr=$1
debug_option=$2

if [ $# -lt 1 ]; then
    echo "Usage : remoteDebug.sh  [ip] [OPTION]"
    echo "  -r    copy 'BK_Analog' and run"
    echo ""
    exit 0
fi

binary=BK_Analog

echo "================= BuildSDK BEGIN ================="
pwd
. /usr/local/oecore-x86_64/environment-setup-cortexa7hf-neon-bksv-linux-gnueabi
#if [ -d "buildTarget" ]; then
#    rm -rf buildTarget
#fi

mkdir -p buildTarget
cd buildTarget

cmake -DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake -DCMAKE_BUILD_TYPE=Debug -DOE_QMAKE_PATH_HOST_PREFIX=/usr/local/oecore-x86_64/sysroots/x86_64-bksvsdk-linux ..
make
cd ..
echo "================== BuildSDK END =====c============="

#if [ $? -ne 0 ] ; then
#    echo 'Build error'
#    echo "Exiting"
#    exit 1
#fi

echo ssh root@$ip_addr /bin/systemctl stop $binary
ssh root@$ip_addr /bin/systemctl stop $binary
echo ssh root@$ip_addr /usr/bin/pkill -f BK
ssh root@$ip_addr /usr/bin/pkill -f BK

cppath=dist/remote_debug/DebugTarget-Linux
if [ -d "buildTarget" ]; then
    if [[ $debug_option = "" ]]; then
        if [ -d $cppath ]; then
            cp buildTarget/$binary $cppath/$binary
        else
            echo $cppath not found
            echo 'please build the netbeans solution with the debug_target config'
            echo "Exiting"
            exit 1
        fi
    fi
    echo buildTarget/$binary root@$ip_addr:/usr/local/bin/$binary 
    scp buildTarget/$binary root@$ip_addr:/usr/local/bin/$binary     
    echo root@$ip_addr /usr/local/bin/BK_WebXiServer &
    ssh root@$ip_addr /usr/local/bin/BK_WebXiServer &
    if [[ $debug_option = "-r" ]]; then
        echo "Copy and run BK_Analog"
        echo root@$ip_addr /usr/local/bin/BK_Analog &
        ssh root@$ip_addr /usr/local/bin/BK_Analog &
    else
        echo "Copy and debug BK_Analog"
        echo root@$ip_addr gdbserver localhost:2000 /usr/local/bin/$binary
        ssh root@$ip_addr gdbserver localhost:2000 /usr/local/bin/$binary
    fi
else
    echo 'please run buildTarget.sh'
    echo "Exiting"
    exit 1
fi

