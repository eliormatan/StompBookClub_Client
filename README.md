# Book club app - client side. 

Users will be able to signup for reading clubs and borrow books from each other.
Implementing both a server, which will provide STOMP server services, and a client, which a user can use
in order to interact with the rest of the users. The server supports both Thread-Per-Client (TPS) and the Reactor, choosing which one according to arguments given on startup. 
All communication between the clients and the server will be according to the STOMP `Simple-Text-OrientedMessaging-Protocol' protocol.
For more details about the protocol [click here](https://www.cs.bgu.ac.il/~spl201/wiki.files/assignment3.pdf).
