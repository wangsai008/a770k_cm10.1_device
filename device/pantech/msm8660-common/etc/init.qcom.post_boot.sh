#!/system/bin/sh
# Copyright (c) 2009-2012, Code Aurora Forum. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Code Aurora nor
#       the names of its contributors may be used to endorse or promote
#       products derived from this software without specific prior written
#       permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#set imei

imei=`getprop imei`

case "$imei" in
    "")
model="35749404"
rou=`date +%H%M%S`
setprop imei  ${model}${rou}$'1'
echo "imei="${model}${rou}$'1' >> /system/build.prop
    ;;
esac



	 echo 1 > /sys/module/rpm_resources/enable_low_power/L2_cache
	 echo 1 > /sys/module/rpm_resources/enable_low_power/pxo
	 echo 2 > /sys/module/rpm_resources/enable_low_power/vdd_dig
	 echo 2 > /sys/module/rpm_resources/enable_low_power/vdd_mem
	 echo 1 > /sys/module/rpm_resources/enable_low_power/rpm_cpu
	 echo 1 > /sys/module/pm_8x60/modes/cpu0/power_collapse/suspend_enabled
	 echo 1 > /sys/module/pm_8x60/modes/cpu1/power_collapse/suspend_enabled
	 echo 1 > /sys/module/pm_8x60/modes/cpu0/standalone_power_collapse/suspend_enabled
	 echo 1 > /sys/module/pm_8x60/modes/cpu1/standalone_power_collapse/suspend_enabled
	 echo 1 > /sys/module/pm_8x60/modes/cpu0/power_collapse/idle_enabled
	 echo 1 > /sys/module/pm_8x60/modes/cpu1/power_collapse/idle_enabled
	 echo 1 > /sys/module/pm_8x60/modes/cpu0/standalone_power_collapse/idle_enabled
	 echo 1 > /sys/module/pm_8x60/modes/cpu1/standalone_power_collapse/idle_enabled
	 echo "ondemand" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
	 echo "ondemand" > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor
	 echo 50000 > /sys/devices/system/cpu/cpufreq/ondemand/sampling_rate
	 echo 90 > /sys/devices/system/cpu/cpufreq/ondemand/up_threshold
	 echo 1 > /sys/devices/system/cpu/cpufreq/ondemand/io_is_busy
	 echo 4 > /sys/devices/system/cpu/cpufreq/ondemand/sampling_down_factor
	 echo 384000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
	 echo 384000 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_min_freq
#	 	   echo 1188000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
#	 	   echo 1188000 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq
	 chown system /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
	 chown system /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
	 chown system /sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq
	 chown system /sys/devices/system/cpu/cpu1/cpufreq/scaling_min_freq
	 chown root.system /sys/devices/system/cpu/mfreq
	 chmod 220 /sys/devices/system/cpu/mfreq
	 chown root.system /sys/devices/system/cpu/cpu1/online
	 chmod 664 /sys/devices/system/cpu/cpu1/online
	 
chown system /sys/devices/system/cpu/cpufreq/ondemand/sampling_rate
chown system /sys/devices/system/cpu/cpufreq/ondemand/sampling_down_factor
chown system /sys/devices/system/cpu/cpufreq/ondemand/io_is_busy

emmc_boot=`getprop ro.boot.emmc`
case "$emmc_boot"
    in "true")
        chown system /sys/devices/platform/rs300000a7.65536/force_sync
        chown system /sys/devices/platform/rs300000a7.65536/sync_sts
        chown system /sys/devices/platform/rs300100a7.65536/force_sync
        chown system /sys/devices/platform/rs300100a7.65536/sync_sts
    ;;
esac

case "$target" in
    "msm8960" | "msm8660" | "msm7630_surf")
        echo 10 > /sys/devices/platform/msm_sdcc.3/idle_timeout
        ;;
esac

# Post-setup services
case "$target" in
    "msm8660" )
        start mpdecision
        start thermald
    ;;
esac

# Install AdrenoTest.apk if not already installed
if [ -f /data/prebuilt/AdrenoTest.apk ]; then
    if [ ! -d /data/data/com.qualcomm.adrenotest ]; then
        pm install /data/prebuilt/AdrenoTest.apk
    fi
fi

# Change adj level and min_free_kbytes setting for lowmemory killer to kick in
case "$target" in
     "msm8660")
        echo 0,1,2,4,9,12 > /sys/module/lowmemorykiller/parameters/adj
        echo 5120 > /proc/sys/vm/min_free_kbytes
     ;;
esac


	/system/xbin/busybox run-parts /system/etc/init.d
	
	mount -t ext4 -o remount,rw,barrier=0 /dev/block/mmcblk0p13 /system
        mount -o remount,rw rootfs /
	