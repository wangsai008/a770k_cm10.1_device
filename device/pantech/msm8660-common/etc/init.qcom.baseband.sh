#!/system/bin/sh

# No path is set up at this point so we have to do it here.
PATH=/sbin:/system/sbin:/system/bin:/system/xbin
export PATH

target=`getprop ro.product.device`

#by syhost
case "$target" in
    "IM-A820L" | "ef65l" | "A820L" )
        if [ "`getprop gsm.version.baseband`" == "" ]; then
		if [ "`cat /data/baseband`" == "" ]; then
			mdm=`strings -n 12 /system/etc/firmware/misc_mdm/image/amss.mbn | grep M9600B | head -1`
			msm=`strings -n 12 /firmware/image/modem.b05 | grep M8660A- | head -1`
            	setprop gsm.version.baseband ${msm}$'\n'${mdm}
			echo $'\n'$msm$'\n'$mdm$'\n' > /data/baseband
        	else
			msm=`cat /data/baseband | strings | grep -- "M8660A-" | head -1`
			mdm=`cat /data/baseband | strings | grep -- "M9600B" | head -1`
			setprop gsm.version.baseband ${msm}$'\n'${mdm}
		fi
        fi
    ;;
esac
