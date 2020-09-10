CurPath=$(pwd)
Bin=$2
Conf=$3
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib_run
retval=0

#---------------------------------------------------------------------------
# START
#---------------------------------------------------------------------------
Start()
{
	if [ $( pidof -s ${Bin} ) ]; then
		echo -n "${Bin} process [${prog}] already running"
		echo_failure
		echo
		return -1;
	fi
		
	if [ ! -x ./${Bin} ]; then
		echo -n "${Bin} binary [${prog}] not found."
		echo_failure
		echo
		return -1
	fi
		
	echo -n "Starting Dync Server(${Bin}): "
	${CurPath}/${Bin} ${CurPath}/${Conf} & 2> /dev/null
	retval=$?
	if [ ${retval} == 0 ]; then
		echo_success
		echo
	else
		echo_failure
		echo
		break
	fi
	sleep 1
	
	#cd -
	return 0
}

#---------------------------------------------------------------------------
# STOP
#---------------------------------------------------------------------------
Stop()
{
	echo -n "Stopping Dync Server(${Bin}): "
	killall ${Bin}
	echo
	return 0
}

#---------------------------------------------------------------------------
# MAIN
#---------------------------------------------------------------------------
case "$1" in
	start)
		Start
		;;
	stop)
		Stop
		;;
	restart)
		Stop
#		sleep 5
		Start
		;;
	*)
		echo "Usage: $0 {start|stop|restart}"
esac

exit 0
