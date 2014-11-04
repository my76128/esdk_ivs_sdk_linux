#!/bin/csh

set IVS_WORK_DIR = `pwd`
set IVS_Netsource_DIR = $IVS_WORK_DIR/IVS_Netsource
set IVS_SDK_DIR = $IVS_WORK_DIR/IVS_SDK

set version = debug
set osver = suse11

while($# != 0)
if ($1 == ver) then
set version = $2
else if ($1 == os) then
set osver = $2
endif
shift
end

cd $IVS_SDK_DIR/rtsp_client
make clean -f Makefile.64
make -f Makefile.64
make copy -f Makefile.64

echo $version
echo $osver
if (($version != debug && $version != release) || ($osver != suse10 && $osver != suse11)) then
echo "parameter error! please input 'debug' or 'release' or 'suse10' or 'suse11'"
exit
endif

cd $IVS_Netsource_DIR
make clean -f Makefile_NetSource ver=$version os=$osver
make -f Makefile_NetSource ver=$version os=$osver
make copy -f Makefile_NetSource ver=$version os=$osver

cd $IVS_SDK_DIR
make clean ver=$version os=$osver;make ver=$version os=$osver;make install ver=$version os=$osver

