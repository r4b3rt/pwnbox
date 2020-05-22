#docker build -f $PWD/ubuntu16/Dockerfile -t r4b3rt/pwnbox:ubuntu16 .
#1.指定基础镜像，并且必须是第一条指令
FROM ubuntu:16.04

#2.指明该镜像的作者和其电子邮件
LABEL maintainer="r4b3rt#163.com"

#3.环境变量
ENV TZ Asia/Shanghai

#4.在构建镜像时，指定镜像的工作目录，之后的命令都是基于此工作目录，如果不存在，则会创建目录
WORKDIR /ctf/work

#5.将一些安装包复制到镜像中，语法：ADD/COPY <src>... <dest>
COPY root /root/
COPY linux_server* /ctf/
COPY ubuntu16/sources.list /etc/apt/sources.list

#6.更新Alpine的软件源为阿里云,所有的操作步骤
RUN set -ex && \
    dpkg --add-architecture i386 && \
    DEBIAN_FRONTEND=noninteractive apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get -y install \
    libc6:i386 libc6-dbg:i386 libc6-dbg libncurses5:i386 libstdc++6:i386 libc6-dev-i386 \
    gcc-multilib g++-multilib gdb gdb-multiarch binwalk tcpdump gperf  exiftool  libtool-bin \
    sudo apt-utils locales build-essential cmake qemu autoconf upx-ucl lib32stdc++6 \
    python3-dev python3-pip ruby-dev libffi-dev libssl-dev libseccomp-dev libini-config-dev libglib2.0-dev \
    zsh nasm strace ltrace patchelf radare2 vim nmap net-tools iputils-ping ruby ipython \
    tmux netcat socat wget curl git gawk file tzdata bison --fix-missing && \
    DEBIAN_FRONTEND=noninteractive apt-get -y autoremove && \
    DEBIAN_FRONTEND=noninteractive apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* && \
    locale-gen en_US.UTF-8 && update-locale && \
    chsh -s /bin/zsh && chmod a+x /ctf/linux_server* && \
    cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && \
    gem sources --add https://gems.ruby-china.com/ --remove https://rubygems.org/ && \
    gem install one_gadget seccomp-tools && rm -rf /var/lib/gems/2.*/cache/* && \
    python3 -m pip install --no-cache-dir --upgrade pip -i http://pypi.douban.com/simple --trusted-host pypi.douban.com && \
    pip config set global.index-url http://pypi.douban.com/simple && \
    pip config set global.trusted-host pypi.douban.com && \
    pip install --no-cache-dir --ignore-installed ipython pwntools future isort python-ptrace pygments enum34 pytest testresources
    
#8.容器启动时需要执行的命令
ENTRYPOINT ["/bin/zsh"]
