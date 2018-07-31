# 问题注记
记录Zookeeper使用过程中遇到的错误信息以及对应解决方法。

## Will not attempt to authenticate using SASL (unknown error)
错误说明：<br>
Zookeeper日志中反复提示Socket被关闭，且SASL鉴权失败。<br>
错误信息如下：

```
2018-06-25 00:20:02,755 [myid:] - INFO  [main-SendThread(localhost:2181):ClientCnxn$SendThread@1161] - Unable to read additional data from server sessionid 0x0, likely server has closed socket, closing socket connection and attempting reconnect
2018-06-25 00:20:03,065 [myid:] - INFO  [main-SendThread(localhost:2181):ClientCnxn$SendThread@1035] - Opening socket connection to server localhost/127.0.0.1:2181. Will not attempt to authenticate using SASL (unknown error)
2018-06-25 00:20:03,066 [myid:] - INFO  [main-SendThread(localhost:2181):ClientCnxn$SendThread@877] - Socket connection established to localhost/127.0.0.1:2181, initiating session
```

解决方案：<br>
查看防火墙服务是否开启，关闭防火墙服务：

```
# systemctl status firewalld.service
# systemctl stop firewalld.service
```

执行`hostname`指令，查看`/etc/hosts`文件，当主机名称不为`localhost`且在host文件中配置了主机IP映射时，
在Zookeeper配置文件中设置`server.xxx`配置项时，使用主机名代替IP。

如：

```
server.1=172.16.0.126:2888:3888
server.2=172.16.0.127:2888:3888
server.3=172.16.0.128:2888:3888
```

改为：

```
server.1=spark-master:2888:3888
server.2=spark-slave0:2888:3888
server.3=spark-slave1:2888:3888
```
