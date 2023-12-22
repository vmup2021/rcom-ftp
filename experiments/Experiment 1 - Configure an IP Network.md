## gnuXY configuration in the rack

We started by connecting the computers (gnuXY) to the switch in the following ports:
- **gnu12**
	- E0 -> SWITCH2
- **gnu13**
	- E0 -> SWITCH3
- **gnu14**
	- E0 -> SWITCH24

## ifconfig and route config in the computers

After this we run the `ifconfig` command and configure the interfaces for the eth0 interface for **gnu13** and **gnu14**.

- **gnu13**
```
ifconfig eth0 172.16.10.1/24
```

- **gnu14**
```
ifconfig eth0 172.16.10.254/24
```

With these commands we get IPs assigned to our computers and are able to ping each other.

// TODO do arp and pcapng

# Conclusion
In this experience we used the commands "ifconfig" and "arp". Where the first command is used to test the connectivity between 
hosts, and for that it generates the ICMP(Internet Control Message Protocol) packets. The second command stands for "Address
Resolution Protocol", which is a protocol used to map IP's to MAC's in a network. The packets we captured with Wireshark  
showed source and destination IP addresses associated with the ping packets, and the arp packets generated to discover
the MAC address of the destination, in case it wasn't in the arp table. We notice that the Ethernet frames have a field to indicate the type of payload in it(ARP, 
IP, ICMP) and a field that indicates it's length.  

