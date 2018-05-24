# use official Ubuntu image
FROM ubuntu:18.04
# set the working directory
WORKDIR /work

# configure proxy
ENV https_proxy "${https_proxy}"
ENV http_proxy "${http_proxy}"
RUN echo Acquire::http::Proxy \"${http_proxy}\"\; > /etc/apt/apt.conf.d/proxy.conf
RUN echo Acquire::https::Proxy \"${http_proxy}\"\; >> /etc/apt/apt.conf.d/proxy.conf

# install build tools
RUN apt-get update && \
    apt-get install -y git python-pip clang-6.0 clang++-6.0 gcc g++ afl

# configure build tools
RUN update-alternatives --install /usr/bin/llvm-symbolizer llvm-symbolizer /usr/bin/llvm-symbolizer-6.0 100

# build openssl
RUN
    git clone http://github.com/openssl/openssl.git openssl_1_0_1f && \
    cd openssl_1_0_1f && \
    git checkout tags/OpenSSL_1_0_1f && \
    CC=afl-clang-fast CXX=afl-clang-fast++ ./config -d && \
    AFL_USE_ASAN=1 make

# prepare challenges
RUN git clone https://github.com/asomsiko/fuzzing_tutorial.git && \
    cd fuzzing_tutorial/challenges/heartbleed/ && \
    AFL_USE_ASAN=1 afl-clang-fast++ -g handshake.cc /work/openssl_1_0_1f/libssl.a /work/openssl_1_0_1f/libcrypto.a -o handshake -I /work/openssl_1_0_1f/include -ldl
