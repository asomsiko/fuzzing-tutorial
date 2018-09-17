# Fuzzing Practice Tutorial
This is AFL tutorial

## Prerequisites
To follow this tutorial you need:
- Basic, theoretical knowledge on the fuzzing
- Ubuntu with sudo and Docker
- Hard drive enough to setup Ubuntu with development tools in a container.
- Multi core CPU.
- Internet access from the machine.
- Interned access from within a docker containers. 

## Setting up Environment
Build the docker container and configure your Ubuntu machine to support AFL.

```
docker build ./docker -t fuzzing-tutorial --build-arg http_proxy=$http_proxy --build-arg https_proxy=$https_proxy
echo core | sudo tee /proc/sys/kernel/core_pattern
```

## Challenges
This tutorial will guide you through the fuzzing challenges.  

Run each challenge from within the docker container. To get into the container
execute:

    docker run  --cap-add SYS_PTRACE -it fuzzing-tutorial

### Challenge: Capture Noisy Bug in 60 Seconds
In 2014 [Heartbleed bug](http://heartbleed.com/) was found in OpenSSL.
Here is how it could have been found with fuzzing in a minutes:

    cd fuzzing-tutorial/challenges/heartbleed/
    mkdir in && echo aaaaaaaaaaaaaaa>in/a
    AFL_USE_ASAN=1 afl-clang-fast++ -g handshake.cc /work/openssl_1_0_1f/libssl.a /work/openssl_1_0_1f/libcrypto.a -o handshake -I /work/openssl_1_0_1f/include -ldl
    afl-fuzz -i in -o out -m none ./handshake

Fuzzing will find a crash in less than 2 minutes. Stop the fuzzing by
prssing `^C` as you see  `total crashes` updates in fuzzing dashboad.
Fuzzing engine stores the test cases reproducing a crash under
`out/crashes`. Explore the crash found:

    ./handshake < out/crashes/id*

### Challenge: Parallel fuzzing
Try running artificial example with several defects.

    cd fuzzing-tutorial/challenges/workflow/
    mkdir in && echo aa>in/a
    afl-g++ -g -O0 -fstack-protector-all app.cc -o app
    afl-fuzz -i in -o out -m none ./app

Notice it takes some time until it fund all crashes.

Run 4 parallel fuzzing jobs
    
    afl-multicore -c workflow.conf start 4

Query current fuzzing status

    afl-whatsup out_multicore


Collect crashes

    afl-collect -d crashes.db -e gdb_scriptg -r -rr ./out_multicore/ ./findings -- ./app
    