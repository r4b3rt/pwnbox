# 自建服务

```bash
/usr/sbin/xinetd -pidfile /run/xinetd.pid -stayalive -inetd_compat -inetd_ipv6
cat > /etc/xinetd.d/pwn2 <<EOF
service pwn2
{
   disable = no
   socket_type = stream
   wait = no
   user = ctf
   server = /home/ctf/pwn2
   log_on_failure += USERID
}
EOF
#将二进制文件放到/home/ctf/pwn2
#同时安装一个apache2的服务
cp /home/ctf/pwn2 /var/www/html
```