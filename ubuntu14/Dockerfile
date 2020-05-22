#docker build -f $PWD/ubuntu14/Dockerfile -t r4b3rt/pwnbox:ubuntu14 .
#1.指定基础镜像，并且必须是第一条指令
FROM ubuntu:14.04

#2.指明该镜像的作者和其电子邮件
LABEL maintainer="r4b3rt#163.com"

#3.环境变量
ENV TZ Asia/Shanghai

#4.在构建镜像时，指定镜像的工作目录，之后的命令都是基于此工作目录，如果不存在，则会创建目录
WORKDIR /ctf/work

#5.将一些安装包复制到镜像中，语法：ADD/COPY <src>... <dest>
COPY root /root/
COPY linux_server* /ctf/
COPY ubuntu14/sources.list /etc/apt/sources.list

#6.更新Alpine的软件源为阿里云,所有的操作步骤
RUN set -ex && \
    dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get -y install \
    libc6:i386 libc6-dbg:i386 libc6-dbg libncurses5:i386 libstdc++6:i386 libc6-dev-i386 \
    gcc-multilib g++-multilib gdb gdb-multiarch binwalk tcpdump gperf exiftool \
    sudo apt-utils locales build-essential cmake qemu autoconf upx-ucl lib32stdc++6 \
    python-dev python-pip libffi-dev libssl-dev libseccomp-dev libini-config-dev libglib2.0-dev \
    zsh nasm strace ltrace radare2 vim nmap net-tools iputils-ping  ipython \
    tmux netcat socat wget curl git gawk file tzdata bison \
    software-properties-common python-software-properties --fix-missing && \
    apt-add-repository ppa:brightbox/ruby-ng && \
    apt-get update && apt-get -y install ruby2.6 ruby2.6-dev && \
    apt-get -y autoremove && apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* && \
    locale-gen en_US.UTF-8 && update-locale && \
    chsh -s /bin/zsh && chmod a+x /ctf/linux_server* && \
    cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && \
    gem sources --add https://gems.ruby-china.com/ --remove https://rubygems.org/ && \
    gem install one_gadget && rm -rf /var/lib/gems/2.*/cache/* && \
    python -m pip install --upgrade pip==19.2.3 && \
    pip config set global.index-url http://pypi.douban.com/simple && \
    pip config set global.trusted-host pypi.douban.com && \
    pip install --ignore-installed pwntools==3.13.0  future isort python-ptrace pygments enum34 pytest testresources
    
#8.容器启动时需要执行的命令
ENTRYPOINT ["/bin/zsh"]
