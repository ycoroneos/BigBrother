BigBrother
==========

He's watching you, in the kitchen

The server will be running on the raspi located in the kitchen.
Clients can connect and retrieve raw images upon request.

Information is first compressed by an OpenCV function into a buffer of
ushorts (unsigned int). This is then sent over a socket to the client.

**the correct endinanness must be observed**
