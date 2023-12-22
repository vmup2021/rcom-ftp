## Accessing the switch to configure the bridges

To access the switch we connected the computer **gnu13** to the (RS232->CISCO) port and then connected the (CISCO->RS232) port to the console port in the switch.
Knowing this, we have to switch our monitor over to the **gnu13** computer and open up GTKterm.
The GTKTerm configuration we changed was just the BaudRate which was set to 115200.
We press enter once and are in the system console for the switch.

## Creating the bridges

To create our first bridge `bridge10` we ran the following command:
```
/interface bridge add name=bridge10
```

Our second bridge `bridge11` we ran the following command:
```
/interface bridge add name=bridge10
```

Now we have 3 bridges: `bridge` (which is the default bridge in the switch and it contains all the ports by default), `bridge10` and `bridge11` which are our bridges.
## Adding ports to the bridges

To add our computer's ports to our newly created bridges we must first remove them from the default bridge using the following command (where we edit the YY variable to be our port):

```
/interface bridge port remove [find interface=etherYY]
```

We do this for ports `ether2`, `ether3` and `ether24`

Now we add them to our bridges:

- bridge10
	- gnu13
	- gnu14
- bridge11
	- gnu12

```
/interface bridge port add bridge=bridge10 interface=ether3
/interface bridge port add bridge=bridge10 interface=ether24
/interface bridge port add bridge=bridge11 interface=ether2
```

With this computers `gnu13` and `gnu14` should be in the same bridge and `gnu12` should be in its own bridge.

## Captures

We start a capture using WireShark in all three computers and ping broadcast from `gnu13` with the following command:

```
ping -b 172.16.10.255
```

We also observed that we cannot ping computer 3 from computer 2 or computer 4 from 2 and vice-versa.

// todo pacotes e perguntas

## Conclusion
Basically removed the computer ports that we would use from the default bridge and added them to our newly created ones "bridge10" and "bridge11", 
for that we used the commands that can be seen above. With that we now have two broadcast domains, which we can conclude by that fact that by now 
our network is composed by basically two bridges, or from the logs above, that is possible to view two broadcasts domains in the arp requests.
