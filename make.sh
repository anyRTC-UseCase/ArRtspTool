#!/bin/sh
#
if [ "$1" = "common" ]; then
	echo "Platform: common"
	rm -f Makefile && cp Makefile.linux Makefile
elif [ "$1" = "r-pi" ]; then
	echo "Platform: Raspberry Pi"
	rm -f Makefile && cp Makefile.pi Makefile
elif [ "$1" = "nv-tx" ]; then
	echo "Platform: Nvdia Jetson tx"
	rm -f Makefile && cp Makefile.tx Makefile
	
else
printf "Please input platform: (common, r-pi, nv-tx) \r\n"
exit;
fi

rm -rf lib_run && mkdir lib_run
make && make install
