#! /bin/ash
#

while [ TRUE ]
do
	BTNS=`devmem 0x41240000`
	SWTCHS=`devmem 0x41200000`
	echo "buttons = " $BTNS ", switches = " $SWTCHS
	if [ "$BTNS" = "0x00000000" ]
	then
		devmem 0x41220000 8 $SWTCHS
	else


		if [ "$BTNS" = "0x00000001" ] || [ "$BTNS" = "0x00000002" ] || [ "$BTNS" = "0x00000004" ] || [ "$BTNS" = "0x00000008" ] || [ "$BTNS" = "0x00000010" ]
		then

			NUM=$(printf "%d" $SWTCHS)
			NUM2=$((-1*NUM - 1))
			NUM3=$(printf "0x%08X" $NUM2)
#			echo $NUM3
			devmem 0x41220000 8 $NUM3
		else
			devmem 0x41220000 8 0xFF
		fi
	fi
done
