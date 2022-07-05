Pooja Desai
4307030112

==============================================================================================

Parts 1, 2 and 3 are completed. Optional part is NOT implemented.

==============================================================================================
Files:
client.cpp - Stream Client, supports one or three input parameters
monitor.cpp - Stream Client, supports one one input parameters
serverM.cpp - Stream Server as well as Datagram Client, fixed ports
serverA.cpp - Datagram Server, fixed port
serverB.cpp - Datagram Server, fixed port
serverC.cpp - Datagram Server, fixed port
Makefile - 'make all' will execute all files, 'make clean' will clean executables

==============================================================================================
==============================================================================================

Format of messages exchanged:
client - serverM --> Stream Client - Stream Server
client can ask server either for balance in the wallet or to transfer coins from their wallet to another
check balance in wallet : One input argument eg: ./client Chinmay
transfer coins : three input arguments, from:to:amt : eg: ./client Chinmay Martin 30


monitor - serverM --> Stream Client - Stream Server
monitor can ask server for the list of transactions that have taken place from the beginning till now.
list : eg: ./monitor TXLIST

serverM - serverA --> Datagram Client - Datagram Server
serverM - serverB --> Datagram Client - Datagram Server
serverM - serverC --> Datagram Client - Datagram Server
The serverM acts as a controller and delegates the actual work to persist transactions to backend servers : serverA, serverB and serverC
serverM will internally communiate with serverA, serverB and serverC when serving the requests from the client and the monitor AND these exchanges will be invisible to the client and monitor.
All the transactions that have taken place by far will be stored by serverA, serverB and serverC without redundancy. Meaning that is a transaction is saved by serverA, it will not be saved by serverB and serverC. 
All transactions are persisted in encrypted format (except serial number). The transaction messages exchanged are also encrypted.


==============================================================================================
==============================================================================================

References or reused code:
	1)	Code for Socket Programming has been taken from : 
	⁃	Brian “Beej Jorgensen” Hall - Beej’s Guide to Network Programming  Using Internet Sockets (2005)
	⁃	Stream Server - https://www.youtube.com/watch?v=cNdlrbZSkyQ&t=388s
	⁃	Stream Client - https://www.youtube.com/watch?v=fmn-pRvNaho
	⁃	UDP Server and Client - https://www.youtube.com/watch?v=uIanSvWou1M

	2)	Make File Tutorial
	⁃	https://www.youtube.com/watch?v=_r7i5X0rXJk

==============================================================================================
==============================================================================================

Assumptions:
	1)	As mentioned in Makefile, the option ‘-std=c++11’ has to be used while compiling the files.
	2)	Attempt to transfer an amount less than or equal to zero is not allowed and will be caught in validations. eg: ./client Chinmay Martin -20
	3)	All names of sender and receivers are case sensitive. Eg: ./client Martin is not the same as ./client martin
	4)	Main Server Message : The following message is being used consistently:
  “The main server received transactions from Server <i> using UDP over port <PORT_NUMBER>.”
  
  The following message is not being used:
  “The main server received feedback from Server <i> using UDP over port <PORT_NUMBER>.”                            
  
  As per https://courses.uscden.net/d2l/le/22707/discussions/threads/47370/View, we are allowed to use either
