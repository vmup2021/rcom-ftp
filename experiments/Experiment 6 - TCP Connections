## Conclusion
In this experiment we compiled our FTP application in tux3 and capture the packets during downloading some files. We notice 
that our FTP application open two TCP connections, being the first one used for the control information, where we send our
commands to the FTP server, and the second connection being responsible for the DTP(data transfer protocol). In the logs above 
we could see the "Three-Way Handshake" being performed, which is the phases for stablishing a connection in TCP. We could see that
the ARQ TCP mechanims depends on the ACK and sliding window mechanisms, that uses the TCP fields SQN(the sequence number to keep 
the order of the packets in a stream), ACK(check if a packet was or not received), WIN(the number of the sliding window). And the 
TCP congestion control mechanism work with the fields CWND and SSTHRESH, to indicate the number of packets the network support and
the threshold that if passed reduces the CWND
