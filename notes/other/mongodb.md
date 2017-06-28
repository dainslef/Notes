<!-- TOC -->

- [安装MongoDB](#安装mongodb)
- [初始化与启动MongoDB](#初始化与启动mongodb)
- [添加MongoDB为Windows服务](#添加mongodb为windows服务)

<!-- /TOC -->



## 安装MongoDB
在`Linux`环境下，主流发行版的源中已经包含了`MonogoDB`的预编译包，在`ArchLinux`中安装`MongoDB`：

```
# pacman -S mongodb
```

在`Windows`环境下，下载zip包解压到指定目录，并将`MongoDB`目录下的`bin`路径加入`PATH`中。



## 初始化与启动MongoDB
使用`mongod`指定启动MongoDB服务，使用`mongo`指定进入MongoDB的交互式shell。

MongoDB默认**没有**设置数据库路径。  
在`Windows`环境下，MongoDB默认的数据库位置为`[盘符]/db`目录，如果该目录没有被创建，则无法正常启动MongoDB服务。  
启动MongoDB服务时可以显式指定数据库的路径：

```
> mongod -dbpath [数据库目录]
```

MongoDB默认会将日志输出到终端，若需要输出日志到文件则需要在启动MongoDB服务中显式指定日志文件的路径：

```
> mongod -logpath [日志文件路径]
```

MongoDB的配置参数可以写入配置文件中，在启动服务时使用`-config`参数加载配置文件即可，无需每次将配置做为指令参数：

```
> mongod -config [配置文件路径]
```

配置文件：

- 在Windows环境下，默认没有生成配置文件，需要自行创建。
- 在Linux系统下，一般配置文件为`/etc/mongodb.conf`。
	以`ArchLinux`为例，默认配置中设定的数据库路径为`/var/lib/mongodb`，日志路径为`/var/log/mongodb/mongod.log`。
- MongoDB默认使用端口号`27017`。



## 添加MongoDB为Windows服务
使用`sc`工具为`mongod`手动创建Windows服务(需要`Admin`用户权限)：

```
> sc create MongoDB binPath="[mongod指令路径] -dbpath=[数据库路径] -logpath=[日志路径] --service"
```

也可以使用`mongod`工具内置的指令创建Windows服务：

```
> mongod -dbpath=[数据库路径] -logpath=[日志路径] -install
```

启动服务：

```
> net start MongoDB
```

使用`sc`工具删除服务：

```
> sc delete MongoDB
```

使用`mongod`内置指令删除服务：

```
> mongod -remove
```
