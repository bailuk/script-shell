#!/bin/sh

sdk_dir="${HOME}/asteroidos-sdk"
sdk_env="environment-setup-armv7vehf-neon-oe-linux-gnueabi"
sdk_bin="sysroots/armv7vehf-neon-oe-linux-gnueabi/usr/bin"
shell_dir="/home/ceres/script-shell" 
log_file="/home/ceres/debug-script-shell.log"
dev="192.168.2.15"
dev_root="root@${dev}"
dev_user="ceres@${dev}"

export CMAKE_PROGRAM_PATH="${sdk_dir}/${sdk_bin}"
. "${sdk_dir}/${sdk_env}"

# rm -rf build
cmake -B build -DCMAKE_INSTALL_PREFIX:PATH=/usr || exit 1

cp ci/script-shell-debug build/script-shell

cmake --build build --target package  || exit 1

scp build/*.ipk ${dev_root}:.
ssh ${dev_root} "opkg remove script-shell"
ssh ${dev_root} "opkg install script-shell*.ipk"

ssh ${dev_user} "touch ${log_file}"
ssh ${dev_user} "tail -f ${log_file}"
