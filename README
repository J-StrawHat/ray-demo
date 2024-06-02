# Ray C++ Demo

## Dependencies

Install bazel 3.4 for building apps

```bash
$ wget https://mirrors.huaweicloud.com/bazel/3.4.0/bazel_3.4.0-linux-x86_64.deb
$ sudo dpkg -i bazel_3.4.0-linux-x86_64.deb
$ sudo apt-get install -f
```

Install the latest version of Ray with C++ support:

```bash
$ pip install -U ray[cpp]
```

Then modify the `path` of ray C++ in file [`./WORKSPACE`](./WORKSPACE) (line: 3)



## Build & Run

Choose a machine (e.g. `192.168.1.164`) as the master node:

```bash
$ ray start --head
```

Then modify the `IP_ADDRESS` in file [`./include/server.h`](./include/server.h) (line: 10)

Build the server app and run it:

```bash
$ bazel run :server
```


Build the client app and run it:

```bash
$ bazel run :client
```

Shut down all actors and nodes:

```bash
$ ray stop
```