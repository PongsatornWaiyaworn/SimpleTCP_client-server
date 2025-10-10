## Compile Server & Client

Open your terminal and run the following commands:

```bash
# Compile the server
g++ server.cpp -o server -lws2_32

# Compile the client
g++ client.cpp -o client -lws2_32
```

## Running the Program
```bash
./server
```
```bash
#./client [hostname or IP address] [input value]
# ex.
./client localhost 5 
```
