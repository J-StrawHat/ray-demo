# Ray C++ Demo

## Dependencies

Install bazel 3.4 for building apps

```bash
$ wget https://mirrors.huaweicloud.com/bazel/3.4.0/bazel_3.4.0-linux-x86_64.deb
$ sudo dpkg -i bazel_3.4.0-linux-x86_64.deb
$ sudo apt-get install -f
```

Install the latest version of Ray with C++ support

```bash
$ pip install -U ray[cpp,default]
```

Then modify the `path` of ray C++ in file [`./WORKSPACE`](./WORKSPACE) (line: 3)



## Setup & Build

### Server

Choose a machine (e.g. `192.168.1.164`) as the master node:

```bash
$ ray start --head
```

Then modify the `IP_ADDRESS` in file [`./include/server.h`](./include/server.h) (line: 10)

Build the server app with bazel:

```bash
$ bazel build :server
```

### Client

Choose another machine and connect to the master node:

```bash
$ ray start --address='192.168.1.164:6379'
```

Build the client app and run it:

```bash
$ bazel build :client
```

## Run

Check the nodes list in the master node and you should see there are two `ACTIVE` nodes with different IP addresses

```bash
$ ray node list
```

Run the server app:

```bash
$ bazel-bin/server
```

Run the client app:

```bash
$ bazel-bin/client
...
Writing to server: {"hello":"ray"}
Client got value from "hello" key: ray
Writing to server: {"hello":"world"}
Client got value from "hello" key: world
```

> Note: Also you can build and run the client app with command `bazel run :client`


Shut down all actors and nodes:

```bash
$ ray stop
```