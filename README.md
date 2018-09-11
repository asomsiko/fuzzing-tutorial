# Fuzzing tutorial

```
docker build . -t fuzzing-tutorial --build-arg http_proxy=$http_proxy --build-arg https_proxy=$https_proxy
echo core | sudo tee /proc/sys/kernel/core_pattern
```

```
docker run  --cap-add SYS_PTRACE -it fuzzing-tutorial
cd fuzzing-tutorial/challenges/heartbleed/
mkdir in && echo aaaaaaaaaaaaaaa>in/a
afl-fuzz -i in -o out -m none ./handshake
```

```
docker run  --cap-add SYS_PTRACE -it fuzzing-tutorial
cd fuzzing-tutorial/challenges/workflow/
mkdir in && echo aa>in/a
AFL_USE_ASAN=1 afl-g++ func.cc -o func -fsanitize=address
afl-fuzz -i in -o out -m none ./func
```
