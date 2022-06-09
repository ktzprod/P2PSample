# How to build

```
cmake -B build .
cmake --build build
```

# Run

When running the program you will be able to run some command to interact with it.

```
./build/peer-sample -user [NAME] -ip [HOST] -port [PORT]
```

# Commands

Connect
```
>> connect [HOST] [PORT]
```

Send
```
>> send [WHO] [MESSAGE]
```

Exit
```
>> exit
```

# Tests

Tests are run with doctest.

```
./build/tests/peer-sample-tests
```

# Example

Terminal 1

```
./build/peer-sample -user "Kuertz" -ip localhost -port 8080
>> connect localhost 8082
[NEW] connection detected: User 1
>> [RECV] message from: User 1 msg: coucou
```

Terminal 2

```
./build/peer-sample -user "User 1" -ip localhost -port 8082
>>
connection from: 127.0.0.1
[NEW] connection detected: Kuertz
>> send Kuertz coucou
>>
```
