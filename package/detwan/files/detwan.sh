#! /bin/sh

. /dni-gconfig
CONFIG=/bin/config
# DNI copyright (c) 2015
detwan="/usr/sbin/detwan"

conffile="/etc/detwan.conf"
 

configs()
{
	# TODO: generate config file.
	cat > $conffile <<-EOF
	### GENERATED BY detwan.sh AUTOMATICALLY, DON'T EDIT BY MANUAL ###
	
	detwan_pptp_hostname		${DGC_product_name}
	detwan_lan_ifname		${DGC_LAN_BR_IF}
	
	wan_factory_mac			`$CONFIG get wan_factory_mac`
	wan_hostname			`$CONFIG get wan_hostname`
	wan_dhcp_gateway		`$CONFIG get wan_dhcp_gateway`
	wan_dhcp_ipaddr			`$CONFIG get wan_dhcp_ipaddr`
	internet_ppp_type		`$CONFIG get internet_ppp_type`

	EOF
}

ip2mac()
{
	cat /proc/net/arp | awk -v ip=$1 '$1 == ip {printf $4}'
}

if2mac()
{
	ifconfig $1 | awk -F 'HWaddr ' '{print $2}' 
}

#set -x
configs

remote_addr=$1
wan_proto=`$CONFIG get wan_proto`
if [ "${DGC_product_name}" == "r7500v2" ] && [ "$wan_proto" == "pppoe" ]; then
	if_name="ethwan"
else
	if_name=${DGC_WAN_BR_IF}
fi
pc_mac=$(ip2mac $remote_addr)
wan_mac=$(if2mac $if_name)
parameter=""

[ "X$2" == "Xap_detect" ] && {
	echo "" > /tmp/result_ap_autodetection

	cable=`cat /tmp/port_status`
	if [ $cable != "1" ]; then
		parameter="-l"
		if_name=${DGC_LAN_BR_IF}
		wan_mac=$(if2mac $if_name)
		[ -z "$wan_mac" ] && {
			echo "1" > /tmp/result_ap_autodetection
			exit 
		}	
	else
		parameter="-k"
	fi
}

$detwan -p $remote_addr -i $if_name -d $wan_mac -n $pc_mac $parameter