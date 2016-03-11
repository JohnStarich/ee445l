# Lab 4: The Internet of Things

## Objectives

* Implement a system that connects to the internet via an IEEE 802.11 – Wifi module, CC3100
* Use DNS to convert name to IP address
* Configure a smart object that can retrieve data from a weather server using TCP
* Design a smart object that can store data onto an internet server using TCP

## Measurement Data

### Packet loss
0% packet loss

### Weather
Average = 283ms
Minimum = 162ms
Maximum = 369ms

### MOOC
Average = 322ms
Minimum = 154ms
Maximum = 415ms

### Custom site
Average = 220ms
Minimum = 119ms
Maximum = 362ms

## Analysis and Discussion

1.  The client sends a request to the server with a random port number requesting a socket. The server creates the socket and sends a reply to the client. The client then sends the data to the server socket and the data is saved in the proper location.
2.  The DNS server allows users to request an IP address of a server knowing only the URL for the website they are trying to visit.
3.  The main difference between UDP and TCP is that TCP is connection based and the packet is guaranteed to get to its destination in order while UDP is sent with any guarantee it will arrive. UDP is often used to sacrifice reliability for speed over using TCP.
