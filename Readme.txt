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
	1)	Socket Programming : 
	⁃	Brian “Beej Jorgensen” Hall - Beej’s Guide to Network Programming  Using Internet Sockets (2005)
	⁃	Stream Server - https://www.youtube.com/watch?v=cNdlrbZSkyQ&t=388s
	⁃	Stream Client - https://www.youtube.com/watch?v=fmn-pRvNaho
	⁃	UDP Server and Client - https://www.youtube.com/watch?v=uIanSvWou1M

  Functions that use referenced or reused code:
    1> client.cpp and monitor.cpp
      1] createStreamClientSocket
      2] sendRecieve

    2> serverM.cpp 
      1] createBindListenStrmSrvrWlcmngSocket
      2] childFork
      3] createUDPSocket
      4] createUDPServerAddrHint
      5] createUDPClientAddrHint
      6] sendRequestToDatagramServer
    
    3> serverA.cpp, serverB.cpp serverC.cpp
      1] createBindDatagramSocket

  2) Sorted list in CPP :
  - https://thispointer.com/c-how-to-sort-a-list-of-objects-with-custom-comparator-or-lambda-function/

  Functions or structures that use referenced or reused code:
    1> serverM.cpp, serverA.cpp, serverB.cpp and serverC.cpp
      1] struct Transaction
      2] sendRecieve

	3)	Make File Tutorial
	⁃	https://www.youtube.com/watch?v=_r7i5X0rXJk

==============================================================================================
==============================================================================================

Assumptions:
	1)	As mentioned in Makefile, the option ‘-std=c++11’ has to be used while compiling the files.
  2)  The monitor can only accept one argument and it has to be TXLIST. This validation is done on monitor, no call made to server if input is not TXLIST
  3)  The client can only accept one or three arguments. This validation is done on client, no call made to server is if argument number is not 1 or 3
	4)	Attempt to transfer an amount less than or equal to zero is not allowed and will be caught in validations. eg: ./client Chinmay Martin -20
	5)	All names of sender and receivers are case sensitive. Eg: ./client Martin is not the same as ./client martin
	6)	Main Server Message : The following message is being used consistently:
  “The main server received transactions from Server <i> using UDP over port <PORT_NUMBER>.”
  
  The following message is not being used:
  “The main server received feedback from Server <i> using UDP over port <PORT_NUMBER>.”                            
  
  As per https://courses.uscden.net/d2l/le/22707/discussions/threads/47370/View, we are allowed to use either
  7) Main Server Message : The following message is being used ater the Main Server generates TXLIST:
  "The main server generated the transaction list file."
  8) Error Messages : Error messages are liberally being used for all files in case of RunTime failures.
