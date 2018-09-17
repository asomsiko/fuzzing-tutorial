# use official Ubuntu image
FROM ubuntu:18.04
# set the working directory
WORKDIR /work

# configure proxy
ENV https_proxy ${https_proxy}
ENV http_proxy ${http_proxy}
RUN echo Acquire::http::Proxy \"${http_proxy}\"\; > /etc/apt/apt.conf.d/proxy.conf
RUN echo Acquire::https::Proxy \"${http_proxy}\"\; >> /etc/apt/apt.conf.d/proxy.conf

# add ubuntu-toolchain-r/ppa with AFL bug fixes:
#   https://bugs.launchpad.net/ubuntu/+source/afl/+bug/1774816
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository -y ppa:ubuntu-toolchain-r/ppa && \
    apt-get upgrade -y

# install build tools
RUN apt-get update && \
    apt-get install -y git python3 python3-pip python-pip clang-6.0 clang++-6.0 gcc g++ afl screen

# configure build tools
RUN update-alternatives --install /usr/bin/llvm-symbolizer llvm-symbolizer /usr/bin/llvm-symbolizer-6.0 100

# build openssl
RUN git clone http://github.com/openssl/openssl.git openssl_1_0_1f && \
    cd openssl_1_0_1f && \
    git checkout tags/OpenSSL_1_0_1f && \
    CC=afl-clang-fast CXX=afl-clang-fast++ ./config -d && \
    AFL_USE_ASAN=1 make

# prepare challenges
RUN git clone http://github.com/asomsiko/fuzzing-tutorial.git

# install afl-utils
RUN git clone http://github.com/rc0r/afl-utils.git && \
    cd afl-utils && \
    git checkout tags/v1.33a && \
    python3 setup.py install && \
    echo "source /usr/lib/python3.6/site-packages/exploitable-1.32_rcor-py3.6.egg/exploitable/exploitable.py" >> ~/.gdbinit
