<!-- TOC -->

- [初始化与基本配置](#初始化与基本配置)
	- [Windows下初始化 *MySQL*](#windows下初始化-mysql)
	- [Linux下初始化 *MariaDB*](#linux下初始化-mariadb)
	- [在Linux下手动配置 *MySQL*](#在linux下手动配置-mysql)
	- [使用指定配置启动 *MySQL*](#使用指定配置启动-mysql)
- [服务管理](#服务管理)
	- [在Windows下启动服务](#在windows下启动服务)
	- [*systemd* Linux发行版中管理服务](#systemd-linux发行版中管理服务)
	- [*SysV init* Linux发行版以及BSD中管理服务](#sysv-init-linux发行版以及bsd中管理服务)
- [用户登陆与管理](#用户登陆与管理)
	- [远程登陆](#远程登陆)
	- [修改用户密码](#修改用户密码)
	- [查看用户信息](#查看用户信息)
	- [创建/删除用户](#创建删除用户)
	- [授权用户](#授权用户)
- [驱动配置](#驱动配置)
- [基本操作](#基本操作)
	- [常用的SQL语句](#常用的sql语句)
	- [内置函数](#内置函数)
	- [主键自增](#主键自增)
- [常用设置](#常用设置)
	- [导出数据](#导出数据)
	- [导入数据](#导入数据)
	- [设置中文编码](#设置中文编码)
	- [存储二进制数据](#存储二进制数据)
	- [JSP编码设置](#jsp编码设置)
	- [时区问题](#时区问题)
	- [禁用 *DNS* 解析](#禁用-dns-解析)
- [*MySQL* 的 *C API*](#mysql-的-c-api)
	- [连接数据库](#连接数据库)
	- [执行SQL语句](#执行sql语句)
	- [处理查询结果](#处理查询结果)
	- [切换当前数据库](#切换当前数据库)
	- [关闭数据库连接](#关闭数据库连接)

<!-- /TOC -->



## 初始化与基本配置
对于`MariaDB`与`MySQL`而言，在初始化操作上有着明显的区别。

### Windows下初始化 *MySQL*
`MySQL`在`5.5`版本之后变更了初始化的方式，原先使用的`mysql_install_db`指令已被废弃，现在应该使用`--initialize`系列参数进行数据库初始化，如下所示：

```
> mysqld --initialize
```

使用`--initialize`参数初始化会默认创建带有密码的`root`账户，密码会记录在`[主机名].err`文件中，日至内容大致为：

```
[Note] A temporary password is generated for root@localhost: [password]
```

可以使用`--initialize-insecure`参数初始化并创建不带密码的`root`账户，如下所示：

```
>  mysqld --initialize-insecure
```

### Linux下初始化 *MariaDB*
`MariaDB`在`MySQL`被`Oracle`收购之后，被各大Linux发行版作为默认的`MySQL`版本。

作为`MySQL`的分支，并没有采用`MySQL 5.5`之后的新初始化方式，依旧使用`mysql_install_db`指令进行数据库初始化，以`ArchLinux`为例，初始化指令为：

```
# mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
```

### 在Linux下手动配置 *MySQL*
几乎所有的主流Linux发行版都将仓库中默认的`MySQL`数据库迁移到了`MariaDB`分支，因而在Linux下使用`Oracle MySQL`需要从官网下载二进制包手动进行配置。

与Windows下不同，在Linux下启动mysql服务需要显式使用`--basedir`、`--datadir`等参数指定数据库的相关路径，在`MySQL`的`bin`目录下执行如下所示指令：

```
$ ./mysqld --initialize-insecure --basedir=[软件路径] --datadir=[数据路径]
```

启动数据库服务需要指定一个拥有权限的路径/文件作为socket路径，在启动时会创建该文件(使用默认参数启动数据库服务会尝试使用`/run/mysqld/mysqld.sock`文件作为锁文件，但普通用户不具有该路径的权限，因而需要显式指定`--socket`参数)：

```
$ ./mysql --socket=[socket文件路径] -u root
```

### 使用指定配置启动 *MySQL*
可以将`MySQL`的启动参数写入配置文件中，启动时指定配置文件的路径即可：

```
$ ./mysqld --defaults-file=[配置文件路径]
```

启动操作类似：

```
$ ./mysqld --defaults-file=[配置文件路径]
```

一个精简的配置文件大致结构如下：

```sh
[mysqld]
basedir = #软件路径
datadir = #数据库路径
port = #服务端口
server_id = #服务id
socket = #服务socket文件位置

sql_mode=NO_ENGINE_SUBSTITUTION,STRICT_TRANS_TABLES

[server]
character_set_server = #数据库编码

[client]
default-character-set = #连接编码
socket = #客户端启动socket文件位置
```



## 服务管理
除了使用`mysqld`指令启动服务之外，在不同的OS上，可以使用OS自带的服务管理工具启动`MySQL`服务。

### 在Windows下启动服务
在Windows系统下，可以使用`--install`参数将`MySQL`注册到系统服务上：

```
> mysqld --install
```

之后可以使用Windows自带的服务管理工具`net`启动`MySQL`服务：

```
> net start mysql
```

如果不再需要`MySQL`服务，则使用`--remove`参数移除服务：

```
> mysqld --remove
```

### *systemd* Linux发行版中管理服务
采用`systemd`的发行版中可以使用`systemctl`指令管理`MySQL`服务：

```
# systemctl status mysqld //查看mysql服务状态
# systemctl start mysqld //启动mysql服务
# systemctl stop mysqld //停止mysql服务
# systemctl restart mysqld //重启mysql服务
```

### *SysV init* Linux发行版以及BSD中管理服务
旧式的Linux发行版以及`*BSD`中使用`service`指令管理`MySQL`服务：

```
# service mysql status
# service mysql start
# service mysql stop
# service mysql restart
```



## 用户登陆与管理
在成功启动了`MySQL`服务之后，使用`mysql`指令登陆：

```
$ mysql -u [用户名]
```

对于有密码的用户，需要使用`-p`参数登陆：

```
$ mysql -u [用户名] -p
```

### 远程登陆
默认情况下为登陆本机的数据库，如果需要**远程登陆**到其它主机上的数据库，应该使用`-h`参数：

```
$ mysql -h [目标主机ip] -u [用户名] -p
```

远程登陆要求本机的ip已被添加到mysql服务端配置中的`bind-address`配置项中，或者不启用`bind-address`配置。  
在发行版`Ubuntu`中，mysql的默认配置中`bind-address`配置项是**启用**的。

### 修改用户密码
登陆数据库之后，在数据库命令行中输入：

```
mysql> set password = password('[密码内容]')
```

也可以使用`mysqladmin`工具进行密码修改操作：

```
$ mysqladmin -u [用户名] password '[密码内容]'
```

### 查看用户信息
在`MySQL`数据库中，用户的信息记录在`mysql`库中的`user`表中，查询该表即可得到**用户信息**：

```
mysql> select * from mysql.user;
```

### 创建/删除用户
在数据库命令行中使用`create user`指令即可创建用户：

```
mysql> create user [用户名];
```

默认情况下创建的是不允许本地登录的远程用户，以上指令相当于：

```
mysql> create user [用户名@'%'];
```

创建本地用户：

```
mysql> create user [用户名@localhost];
```

删除用户操作类似，使用`drop user`指令：

```
mysql> drop user [用户名@主机名/主机地址];
```

### 授权用户
新创建的用户不具有权限，需要使用管理员账户(一般为`root`)对其进行授权。

授予某个用户指定数据库的查询与更新权限：

```sql
mysql> grant select, update on [数据库名].* to [用户名]@[登录方式];
```

授予某个用户所有权限：

```sql
mysql> grant all privileges on *.* to [用户名]@[登录方式];
```

被授权的用户默认不能将所拥有的权限授权给其它用户，如果需要使授权能够被传播则使用(一般不推荐这样使用，数据库权限应由DBA统一管理)：

```sql
mysql> grant all privileges on *.* to [用户名]@[登录方式] with grant option;
```

也可以通过修改`mysql.user`表来赋予权限：

```sql
mysql> update user set Host='[主机名称]',select_priv='y', insert_priv='y',update_priv='y', Alter_priv='y',delete_priv='y',create_priv='y',drop_priv='y',reload_priv='y',shutdown_priv='y',Process_priv='y',file_priv='y',grant_priv='y',References_priv='y',index_priv='y',create_user_priv='y',show_db_priv='y',super_priv='y',create_tmp_table_priv='y',Lock_tables_priv='y',execute_priv='y',repl_slave_priv='y',repl_client_priv='y',create_view_priv='y',show_view_priv='y',create_routine_priv='y',alter_routine_priv='y',create_user_priv='y' where user='[用户名]';
```

更新完用户权限表之后，刷新权限信息：

```sql
mysql> flush privileges;
```

查看一个用户的权限可以在数据库命令行中使用`show grants`指令：

```sql
mysql> show grants; //显示当前用户的权限信息
mysql> show grants for [用户名]@[主机地址]; //显示指定用户的权限信息
```



## 驱动配置
在`Java`语言中与`MySQL`交互一般使用通用的`JDBC`接口，加载mysql对应的JDBC驱动即可。  
使用`Java`语言编写的IDE如`NetBeans`、`Eclipse`、`IntelliJ IDEA`等提供的`MySQL`数据库管理功能也需要添加mysql的JDBC驱动。

在`ArchLinux`中使用使用Qt5操作mysql数据无需安装额外的包(驱动已被集成至`Qt5`包组中)。  
在`Debian`系发行版中使用Qt5操作mysql数据库需要安装`libqt5sql-mysql`包。  
在`Debian/RedHat`系发行版中使用`C API`连接mysql数据库时需要安装额外的开发头文件包：

```
# apt-get install libmysqlclient-devel //大便系
# yum/dnf install mysql-devel //红帽系
```

在`ArchLinux`中不需要，`ArchLinux`中的数据库包已经包含了开发头文件。



## 基本操作
基本的数据库管理、操作指令：

- `status;` 查看数据库基本状态
- `show databases;` 查看数据库列表
- `create database [数据库名];` 创建数据库
- `drop database [数据库名];` 删除数据库
- `use [数据库名];` 切换正在使用的数据库
- `desc [表名];` 查看指定表格的结构
- `truncate table [表名];` 清除指定表格的内容(速度快，但不可恢复)
- `delete from [表名];` 删除指定表格的内容(速度慢，但可以恢复)

### 常用的SQL语句
- `insert into [表名] ([列名1], [列名2], ....) values([值1], [值2], ....);` 增
- `delete from [表名] where [限制条件];` 删
- `update [表名] set [列名] = '[内容]' where [列名] = '[内容]';` 改
- `select [列名] from [表名] where [限制条件];` 查
- `select count([统计内容]) from [表名];` 统计表中的指定记录数
- `select [列名] from [表名] limit [数量] offset [起始行];` 从指定行开始查询指定数量的记录
- `select [列名] from [表名] limit [起始行], [数量];` 从指定行开始查询指定数量的记录

### 内置函数
使用**内置函数**可以查询一些特殊的信息：

- `select user();` 查询当前登录的用户
- `select database();` 查询正在使用的数据库名称
- `select version();` 查询数据库的版本信息
- `select @@version_compile_os;` 查询数据编译平台

### 主键自增
设置主键自增：

```
mysql> alert table [表名] auto_increment=[数字]; //设置自增属性
mysql> alter table [表名] change [主键列名] [主键列名] [属性] auto_increment;
```

取消主键自增：

```sql
mysql> alter table [表名] change [列名] [列名] [属性];
```

设置主键自增对于已有数据的列需要清空已有数据才能正常显示。
必须是**主键**才能设置自增属性。



## 常用设置

### 导出数据
使用`mysqldump`工具可以导出数据库的内容，基本操作指令如下：

```
$ mysqldump -u"[用户名]" -p"[密码]" -A //导出所有数据库
$ mysqldump -u"[用户名]" -p"[密码]" [要备份的数据库名称] //导出指定数据库
$ mysqldump -u"[用户名]" -p"[密码]" [要备份的数据库名称] [要备份的表名称] //导出指定数据库中的指定表的内容
```

默认情况下，`mysqldump`工具会将导出的数据以`SQL`语句的形式输出到终端，可以使用重定向将导出的内容写入文本中：

```
$ mysqldump -u"[用户名]" -p"[密码]" -A > xxx.sql //导出的内容写入 xxx.sql 文件中
```

`mysqldump`支持根据条件导出指定的内容(使用`-w`参数)：

```
$ mysqldump -u"[用户名]" -p"[密码]" -w"[限制条件]" [数据库名] [表名]
```

导出内容时支持设定只导出数据(`-t`)或只导出表结构(`-d`)。

### 导入数据
导入数据需要在数据库命令行中使用`source`指令：

```
mysql> source [数据库备份文件]
```

导入数据库时需要注意编码问题，数据库编码、连接编码、备份文件的编码需要相同才不会产生中文乱码问题。

### 设置中文编码
默认情况下，旧版的mysql数据库的编码为`latin1`，此编码不支持东亚语系的文字显示，需要修改为支持各国文字的`UTF-8`编码。  
对于部分使用`MariaDB`的发行版(如`ArchLinux`)，默认的编码为`UTF-8`，无需额外配置。

查看数据库的默认的所有编码信息：

```
mysql> show variables like 'character_set_%';
```

典型的结果如下所示：

```
+--------------------------+------------------------------------------------------------+
| Variable_name            | Value                                                      |
+--------------------------+------------------------------------------------------------+
| character_set_client     | gbk                                                        |
| character_set_connection | gbk                                                        |
| character_set_database   | gbk                                                        |
| character_set_filesystem | binary                                                     |
| character_set_results    | gbk                                                        |
| character_set_server     | gbk                                                        |
| character_set_system     | utf8                                                       |
| character_sets_dir       | D:\ProtableApplication\mysql-5.6.21-winx64\share\charsets\ |
+--------------------------+------------------------------------------------------------+
```

其中：

- `character_set_client`、`character_set_connection`可以通过配置文件中的`[client]`段进行修改。
- `character_set_database`、`character_set_results`、`character_set_server`可以通过修改配置文件中的`[server]`段进行修改。

需要注意的是，每个数据库可以拥有不同的编码信息，查看指定数据库的编码：

```
mysql> use [数据库名称];
mysql> show variables like 'character_set_database';
```

修改指定数据库的编码：

`mysql> alter database [数据库名称] CHARACTER SET [编码类型(gbk/utf8)];`

如果需要修改数据库的默认编码，则需要修改配置文件：

- 在`Debian`系中，配置文件为`/etc/mysql/mariadb.conf.d/client.cnf`。
- 在`RedHat`系中，配置文件为`/etc/my.cnf`。
- 在`ArchLinux`中，配置文件为`/etc/mysql/my.cnf`。

在配置文件中加入下列配置：

```ini
[client]
# Default is Latin1, if you need UTF-8 set this (also in server section)
default-character-set = utf8
[server]
default-character-set = utf8
```

在`Windows`系统下，配置文件位于mysql的软件主目录下，名称为`my.ini`，该配置文件需要手动创建：

```ini
[server]
# mysql5.5版本之后[server]配置段不再使用default-character-set=utf8，该配置已被废弃
character_set_server = utf8
[client]
# 客户端配置不变
default-character-set = utf8
```

### 存储二进制数据
如果需要向数据库中存储二进制信息(比如**图片**)，则字段应选择`BLOB`类型(`binary large object`)。

在`MySQL`中，与`BLOB`相关的类型有四种，分别为：`TinyBlob`、`Blob`、`MediumBlum`、`LongBlum`。  
这四种类型之间的区别在于存储文件大小上限不同。  
`TinyBlob`最大`255B`，`Blob`最大`65KB`，`MediumBlob`最大`16MB`，`LongBlob`最大`4GB`。

### JSP编码设置
在`JSP`开发中，编码问题主要体现在以下几个方面：

- 数据库表的编码：`ENGINE=InnoDB DEFAULT CHARSET=utf8`。
- 数据库连接编码：`jdbc:mysql://localhost:3306/xxx?useUnicode=true&characterEncoding=UTF-8`。
- 页面提交内容的编码：`request.setCharacterEncoding("UTF-8");response.setCharacterEncoding("UTF-8");`。

数据表的编码需要与连接的编码相同，否则读取数据会出现中文乱码，而JSP页面中的内容编码可以单独指定。

### 时区问题
`MySQL`连接出现如下所示错误：

```
The server time zone value 'XXX' is unrecognized or represents more than one time zone. You must configure either the server or JDBC driver (via the serverTimezone configuration property) to use a more specifc time zone value if you want to utilize time zone support.
```

原因是服务端的时区信息未能正常获取，需要在连接中显式指明时区信息，如下所示：

```
jdbc:mysql://localhost:3306/xxx?serverTimezone=UTC //服务端时区信息不为UTC时，需要改为与服务端相匹配的时区
```

### 禁用 *DNS* 解析
`MySQL`默认开启了`DNS`解析，但在`DNS`服务器异常时，一次数据库操作会异常缓慢，并在`/var/log/mysql/error.log`中写入类似日志：

```
[Warning] IP address 'xxx.xxx.xxx.xxx' could not be resolved: Temporary failure in name resolution
```

解决方法是禁用`MySQL`的`DNS`解析，在配置`my.cnf`中添加以下内容：

```
[mysqld]
skip-host-cache
skip-name-resolve
```



## *MySQL* 的 *C API*
`MySQL`数据库提供了**C语言**接口用于数据库交互，在`*nix`中，头文件为`/usr/include/mysql/mysql.h`。

在使用Unix工具链进行编译时，需要添加参数`-lmysqlclient`用于链接`libmysqlclient.so`动态库。

mysql的C语言绑定主要涉及以下几种结构体类型：

- `MYSQL` 存储连接相关信息
- `MYSQL_RES` 存储查询操作相关返回信息

### 连接数据库
使用`mysql_init()`初始化连接信息结构体，使用`mysql_real_connect()`连接数据库。

```c
MYSQL* mysql_init(MYSQL *mysql);
MYSQL* mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long clientflag);
```

- `mysql`参数标识连接。
- `host`、`user`、`passwd`参数依次为**主机地址**、**数据库用户名**、**数据库密码**。
- `db`参数为连接到的数据库名称。
- `port`参数用于显式指定连接端口，`unix_socket`参数为socket连接类型，`clientflag`为mysql运行ODBC的标记，一般本地连接这三个参数全填`NULL`。

旧式的连接函数`mysql_connect()`已不再推荐使用，仅仅为兼容而保留。

### 执行SQL语句
使用`mysql_query()`以及`mysql_real_query()`执行SQL语句：

```c
int mysql_query(MYSQL *mysql, const char *q);
int mysql_real_query(MYSQL *mysql, const char *q, unsigned long length);
```

两个函数的区别如下：

- 一般性的SQL语句可以直接使用`mysql_query()`执行，`q`参数为需要执行的SQL语句字符数组指针。
- `mysql_real_query()`相比`mysql_query()`而言效率更高，因为其内部实现不调用`strlen()`来获取字符数组长度。此外，如果执行的sql语句中包含有二进制内容，则一定需要使用`mysql_real_query()`，因为`mysql_query()`会调用`strlen()`来获取字符数组长度，而`strlen()`判断字符数组结束是以`\0`作为标志的，但对于二进制数据而言，数据中的`\0`可能是有效值，因而使用`mysql_query()`可能会造成对数据长度的误判使得程序未按预期执行。

函数执行成功返回`0`，执行失败时返回错误代码。

### 处理查询结果
使用下列函数对结果集进行操作：

```c
MYSQL_RES* mysql_store_result(MYSQL *mysql);
MYSQL_RES* mysql_use_result(MYSQL *mysql);
unsigned int mysql_field_count(MYSQL *mysql);
unsigned int mysql_num_fields(MYSQL_RES *res);
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
void mysql_data_seek(MYSQL_RES *result, my_ulonglong offset);
```

- `mysql_store_result()`和`mysql_use_result()`用于获取查询语句之后的结果集内容，二者的区别是前者会将结果集拷贝到本地，开销大，后者直接读取服务器中的数据，每次只拷贝一行，开销小，但是后者需要在下一次SQL语句执行之前将结果集中的数据全部读出，但前者就不需要。
- `mysql_field_count()`用于获取最近查询的列数。
- `mysql_num_fields()`用于获取指定查询结果的列数。
- `mysql_fetch_row()`用于按行读取结果集中的内容，每次执行`mysql_fetch_row()`会返回下一行结果集的指针。返回值类型`MYSQL_ROW`的实际类型为二维指针`char**`，保存了每一列的字符数组指针。
- `mysql_data_seek()`用于设置结果集读取位置到指定的偏移量，`offset`参数取值为`0`时，则重置结果集的读取位置。

### 切换当前数据库
使用`mysql_select_db()`函数切换数据库：

```c
int mysql_select_db(MYSQL *mysql,const char *db);
```

相当于mysql指令`use [数据库名]`。

### 关闭数据库连接
使用`mysql_close()`函数关闭数据库连接：

```c
void mysql_close(MYSQL *sock);
```

- 如果传入的参数是指针，则指针所指向的MYSQL结构体内存区域会被释放掉。
- 立即访问执行`mysql_close()`之后的MYSQL指针会报错(野指针)，如果在关闭连接之后需要重新启用连接，需要重新执行初始化操作`mysql_init()`。
