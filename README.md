# grpc_node_test
This project is an example of using self-defined message defined in [grpc_core](https://github.com/kyle1548/grpc_core).

***The following all use "$HOME/corgi_ws/install" to replace {your installation path}.***
# compile
```
$ cd grpc_node_test
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_PREFIX_PATH=$HOME/corgi_ws/install
$ make -j16
```

# run
```
$ grpccore      // terminal 1
$ ./DataPubTest // terminal 2 (run in the build file)
$ ./DataSubTest // terminal 3 (run in the build file)
```
Here ***DataPubTest*** publish command and state of motor and power of the robot, where for now the values are assigned with constant initial values and increasing with constant increments after each publish.  
***DataSubTest*** subscribe all topics  ***DataPubTest*** published and print out the values it recieved.
