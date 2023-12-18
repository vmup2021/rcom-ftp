## Connecting the new cables

We connected `P1.1` to the first entrance on the router `ETH1`.
We also connected `ETH2` from the router to the switch on port `ETHER10`.

## Adding the router to `bridge11`

Now we have to go to the GTKterm interface and configure the switch to have `ETHER10` in `bridge11`

For that we run the following commands:

```
/interface bridge port remove [find interface=ether10]
/interface bridge port add bridge=bridge11 interface=ether10
```

## Configuring the router using the console

To access the router we must switch our cable from the switch console to the router console which is in a port called `Router MTIK`.

After this change, we have a new connection like this: 
`(gnu13 (S0)) -> (RS232/CISCO) -> router MTIK`

We then ran the following commands to configure the router:
```
/ip address add address=172.16.2.49/24 interface=ether1
/ip address add address=172.16.11.254/24 interface=ether2
```

## Adding routes and configuring the computers

On computer `gnu12` we run the following command to add the router as the default gateways in `gnu12` and `gnu14`:

gnu12:
```
route add -net default gw 172.16.11.254
```

gnu14:
```
route add -net default gw 172.16.10.254
```

Then we need to add routes in the router and in `gnu12` for 172.16.10.0/24 so that they know to use `gnu14` to communicate with that subnet.

To allow direct communication with the other subnet from gnu12, we added a route for gnu14 from gnu12, so that it doesn't have to go throug Rc first:

gnu12:
```
route add -net 172.16.10.0/24 gw 
```

FOTOS TIRADAS NESTE PONTO ANETS DE COMECAR O SLIDE 15
FOTOS TIRADAS AS ROUTES

O COISO UTILIZADO NO ROUTER FOI O 172.16.1.49/24 PARA LIGAR O Rc a internet