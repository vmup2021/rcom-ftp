## Adding `gnu14` eth1 to `bridge11`

We start by going in the rack and adding a new cable from `gnu14` on port E1 to the switch on port ETHER23.

To add `gnu14` to the bridge11 we have to go in the GTKterm console for the switch and run the following commands:

```
/interface bridge port remove [find interface=ether23]
/interface bridge port add bridge=bridge11 interface=ether23
```

After this, we switch our monitor over to `gnu14` and run the following `ifconfig` command:

```
ifconfig eth0 172.16.11.253/24
```

## Transform `gnu14` into a router

In order for `gnu14` to work as a router we must first run a few commands:

```
sysctl net.ipv4.ip_forward=1
sysctl net.ipv4.icmp_echo_ignore_broadcasts=0
```

Then we have to inform our computers on the different bridges about the new route using the route command:

- `gnu13`
```
route add -net 172.16.11.0/24 gw 172.16.10.254
```
- `gnu12`
```
route add -net 172.16.10.0/24 gw 172.16.11.253
```

todo: captures

## Conclusion 
In this experience we used the commands ifconfig, route, sysclt. The first command was used to give to our added router an IP address in our network. The 
route command was used to add routes to the other devices in our network, telling them where to forward certain packets. And the last command was used
to configure our router so that it could properly work. The routes in each tux basically describe what to do with a packet that needs to be delivered 
to a specific network, for that each entry has the destination field, the netmask field, the gateway, flags, and metric field that helps decide where
to forward the packet. In the logs of this experience we could notice how the pings are performed into different networks seeing the IP addresses associated
with the ICMP packets and the ARP requests that are used to discover the MAC of the hosts when the ping is executed.
