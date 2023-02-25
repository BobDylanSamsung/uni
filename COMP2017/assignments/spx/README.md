1. Describe how your exchange works.

The exchange starts by parsing the products which are held in an orderbook struct as an array and each product struct has two linked lists of order structs for buys and sells. Then it will then make the FIFOs, fork and start the traders as child processes. The orders are also held as structs, containing information such as the trader and the time they were placed. The exchange scans for two signals, SIGUSR1 and SIGCHLD. When received, it will create a new node in a linked list containing the signal number and the PID of the sender. When the exchange parses a node in the queue, it will match the PID to a trader. If the signal is SIGUSR1 then it will read input from that trader's pipe and act accordingly. Otherwise, it disconnects the trader. The exchange continues until there are no connected traders.

2. Describe your design decisions for the trader and how it's fault-tolerant.

In addition to the exchange pipes, the trader will open an additional self pipe that only it has access to. When a message and SIGUSR1 are received from the exchange, the trader will write it to the self pipe preceded by its length as an int. In the main loop, once the self pipe is not empty, it will read the length and then read that many bytes as the message. This ensures messages from the exchange are not lost as if messages are received in quick succession, the trader won’t parse both at once. Additionally, only the trader has access to the messages once they have been read, reducing race conditions. Further, After a buy order is sent, the trader will signal every 0.1 seconds until the order has been read by the exchange, ensuring its orders are not lost.

3. Describe your tests and how to run them.

The cmocka unittests directly test the output of functions. Test cases will pass functions input similar to what it would receive by a trader and test the returned variables. This is done by specifying the expected output and checking it against what is returned. 

Each end to end testcase is contained within its own subdirectory. Inside is the source code for the tests, the products file, the expected output file and a simple bash script to run the test. They test the overall output of the exchange and match it to what is expected.

Using the make command, the makefile will compile each test in its directory as well as the exchange and trader. Running runtests.sh will run all of the end-to-end tests. Specifying “unittest” as a command-line argument will run the unit tests. Otherwise specifying one or more end-to-end tests will run each of them.
