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

