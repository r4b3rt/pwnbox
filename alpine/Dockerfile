#docker build -f $PWD/alpine/Dockerfile -t r4b3rt/pwnbox:alpine .
#1.指定基础镜像，并且必须是第一条指令
FROM alpine:3.11

#2.指明该镜像的作者和其电子邮件
LABEL maintainer="r4b3rt#163.com"

#3.环境变量
ENV GLIBC_REPO=https://github.com/sgerrand/alpine-pkg-glibc \
    GLIBC_VERSION=2.31-r0

#4.在构建镜像时，指定镜像的工作目录，之后的命令都是基于此工作目录，如果不存在，则会创建目录
WORKDIR /ctf/work

#5.将一些安装包复制到镜像中，语法：ADD/COPY <src>... <dest>
COPY linux_server* /ctf/
COPY .zshrc /root/.zshrc
COPY .tmux.conf /root/.tmux.conf

#6.更新Alpine的软件源为阿里云,所有的操作步骤
RUN set -ex && \
    echo http://mirrors.aliyun.com/alpine/v3.11/main/ > /etc/apk/repositories && \
    echo http://mirrors.aliyun.com/alpine/v3.11/community/ >> /etc/apk/repositories && \
    apk add --no-cache --update-cache \
    alpine-sdk build-base gdb libstdc++ ca-certificates zsh bash \
    curl tmux git vim socat tzdata ltrace strace patchelf nasm \
    python3-dev ruby-dev ruby-rdoc openssl-dev libffi-dev capstone-dev && \
    chmod a+x /ctf/linux_server* && \
    cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && \
    wget -q -O /etc/apk/keys/sgerrand.rsa.pub https://alpine-pkgs.sgerrand.com/sgerrand.rsa.pub && \
    for pkg in glibc-${GLIBC_VERSION} glibc-bin-${GLIBC_VERSION} glibc-i18n-${GLIBC_VERSION}; \
    do curl -sSL ${GLIBC_REPO}/releases/download/${GLIBC_VERSION}/${pkg}.apk -o /tmp/${pkg}.apk; done && \
    apk add /tmp/*.apk && rm -rf /tmp/*.apk /var/cache/apk/* && apk del tzdata && \
    /usr/glibc-compat/bin/localedef -i en_US -f UTF-8 en_US.UTF-8 && \
    /usr/glibc-compat/sbin/ldconfig /lib /usr/glibc-compat/lib && \
    gem sources --add https://gems.ruby-china.com/ --remove https://rubygems.org/ && \
    gem install one_gadget && rm -rf /var/lib/gems/2.*/cache/* && \
    ln -s /bin/bash /usr/bin/bash && ln -s /usr/bin/python3 /usr/bin/python && \
    python -m pip install --no-cache-dir --upgrade pip -i http://pypi.douban.com/simple --trusted-host pypi.douban.com && \
    pip config set global.index-url http://pypi.douban.com/simple && \
    pip config set global.trusted-host pypi.douban.com && \
    pip install --no-cache-dir --ignore-installed pwntools --trusted-host pypi.douban.com && \
    git clone --depth 1 https://github.com.cnpmjs.org/ohmyzsh/ohmyzsh.git /root/.oh-my-zsh && \
    git clone --depth 1 https://github.com.cnpmjs.org/pwndbg/pwndbg.git /root/pwndbg && \
    pip install --no-cache-dir --ignore-installed future isort python-ptrace pygments enum34 pytest testresources
    
#8.容器启动时需要执行的命令
ENTRYPOINT ["/bin/zsh"]
