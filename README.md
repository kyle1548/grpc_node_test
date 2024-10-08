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
