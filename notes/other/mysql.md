<!-- TOC -->

- [初始化與基本配置](#初始化與基本配置)
	- [數據庫初始化 (MySQL 5.7+)](#數據庫初始化-mysql-57)
	- [數據庫初始化 (MariaDB & MySQL 5.6-)](#數據庫初始化-mariadb--mysql-56-)
	- [手動配置](#手動配置)
	- [使用指定配置啓動](#使用指定配置啓動)
- [服務管理](#服務管理)
	- [管理數據庫服務 (Windows)](#管理數據庫服務-windows)
	- [管理數據庫服務 (Linux SystemD)](#管理數據庫服務-linux-systemd)
	- [管理數據庫服務 (BSD/Linux SysV)](#管理數據庫服務-bsdlinux-sysv)
- [用戶登陸與管理](#用戶登陸與管理)
	- [遠程登陸](#遠程登陸)
	- [修改用戶密碼](#修改用戶密碼)
	- [跳過登陸驗證](#跳過登陸驗證)
	- [關於密碼策略](#關於密碼策略)
	- [查看用戶信息](#查看用戶信息)
	- [創建/刪除用戶](#創建刪除用戶)
	- [授權用戶](#授權用戶)
- [驅動配置](#驅動配置)
- [基本操作](#基本操作)
	- [基本SQL語句](#基本sql語句)
	- [內置函數](#內置函數)
	- [複製表格](#複製表格)
	- [主鍵自增](#主鍵自增)
	- [外鍵約束](#外鍵約束)
- [Row Formats (行格式)](#row-formats-行格式)
	- [REDUNDANT Row Format](#redundant-row-format)
	- [COMPACT Row Format](#compact-row-format)
	- [DYNAMIC Row Format](#dynamic-row-format)
- [常用設置](#常用設置)
	- [導出數據](#導出數據)
	- [導入數據](#導入數據)
	- [設置中文編碼](#設置中文編碼)
	- [二進制數據](#二進制數據)
	- [JSP編碼設置](#jsp編碼設置)
	- [時區問題](#時區問題)
	- [時間轉換](#時間轉換)
	- [禁用 DNS 解析](#禁用-dns-解析)
- [查看數據庫狀態](#查看數據庫狀態)
- [C API](#c-api)
	- [連接數據庫](#連接數據庫)
	- [執行SQL語句](#執行sql語句)
	- [處理查詢結果](#處理查詢結果)
	- [切換當前數據庫](#切換當前數據庫)
	- [關閉數據庫連接](#關閉數據庫連接)

<!-- /TOC -->



# 初始化與基本配置
對於`MariaDB`與`MySQL`而言，在初始化操作上有着明顯的區別。

## 數據庫初始化 (MySQL 5.7+)
`MySQL`在`5.7`版本開始變更了初始化的方式，原先使用的`mysql_install_db`指令已被廢棄，
現在應該使用`--initialize`系列參數進行數據庫初始化，如下所示：

```
> mysqld --initialize
```

使用`--initialize`參數初始化會默認創建帶有密碼的`root`賬戶，密碼會記錄在`[主機名].err`文件中，日至內容大致爲：

```
[Note] A temporary password is generated for root@localhost: [password]
```

可以使用`--initialize-insecure`參數初始化並創建不帶密碼的`root`賬戶，如下所示：

```
> mysqld --initialize-insecure
```

## 數據庫初始化 (MariaDB & MySQL 5.6-)
`MariaDB`在MySQL被`Oracle`收購之後，被各大Linux發行版作爲默認的MySQL替代版本。

作爲MySQL的分支，並沒有採用`MySQL 5.5`之後的新初始化方式，依舊使用`mysql_install_db`指令進行數據庫初始化，
以ArchLinux爲例，初始化操作爲：

```
# mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
```

## 手動配置
幾乎所有的主流Linux發行版都將倉庫中默認的MySQL數據庫遷移到了MariaDB分支，
因而在Linux下使用`Oracle MySQL`需要從官網下載二進制包手動進行配置。

與Windows下不同，在Linux下啓動mysql服務需要顯式使用`--basedir`、`--datadir`等參數指定數據庫的相關路徑，
在MySQL的`bin`目錄下執行如下所示指令：

```
$ ./mysqld --initialize-insecure --basedir=[軟件路徑] --datadir=[數據路徑]
```

啓動數據庫服務需要指定一個擁有權限的路徑/文件作爲socket路徑，
在啓動時會創建該文件(使用默認參數啓動數據庫服務會嘗試使用`/run/mysqld/mysqld.sock`文件作爲鎖文件，
但普通用戶不具有該路徑的權限，因而需要顯式指定`--socket`參數)：

```
$ ./mysql --socket=[socket文件路徑] -u root
```

## 使用指定配置啓動
可以將MySQL的啓動參數寫入配置文件中，啓動時指定配置文件的路徑即可：

```
$ ./mysqld --defaults-file=[配置文件路徑]
```

啓動操作類似：

```
$ ./mysqld --defaults-file=[配置文件路徑]
```

一個精簡的配置文件大致結構如下：

```sh
[mysqld]
basedir = #軟件路徑
datadir = #數據庫路徑
port = #服務端口
server_id = #服務id
socket = #服務socket文件位置

sql_mode=NO_ENGINE_SUBSTITUTION,STRICT_TRANS_TABLES

[server]
character_set_server = #數據庫編碼

[client]
default-character-set = #連接編碼
socket = #客戶端啓動socket文件位置
```



# 服務管理
除了使用`mysqld`指令啓動服務之外，在不同的OS上，可以使用OS自帶的服務管理工具啓動MySQL服務。

## 管理數據庫服務 (Windows)
在Windows系統下，可以使用`--install`參數將MySQL註冊到系統服務上：

```
> mysqld --install
```

之後可以使用Windows自帶的服務管理工具`net`啓動MySQL服務：

```
> net start mysql
```

如果不再需要MySQL服務，則使用`--remove`參數移除服務：

```
> mysqld --remove
```

## 管理數據庫服務 (Linux SystemD)
採用`systemd`的發行版中可以使用`systemctl`指令管理MySQL服務：

```
# systemctl status mysqld //查看mysql服務狀態
# systemctl start mysqld //啓動mysql服務
# systemctl stop mysqld //停止mysql服務
# systemctl restart mysqld //重啓mysql服務
```

## 管理數據庫服務 (BSD/Linux SysV)
舊式的Linux發行版以及`*BSD`中使用`service`指令管理MySQL服務：

```
# service mysql status
# service mysql start
# service mysql stop
# service mysql restart
```



# 用戶登陸與管理
在成功啓動了`MySQL`服務之後，使用`mysql`指令登陸：

```
$ mysql -u [用戶名]
```

對於有密碼的用戶，需要使用`-p`參數登陸：

```
$ mysql -u [用戶名] -p
```

## 遠程登陸
默認情況下爲登陸本機的數據庫，如果需要**遠程登陸**到其它主機上的數據庫，應該使用`-h`參數：

```
$ mysql -h [目標主機ip] -u [用戶名] -p
```

遠程登陸需要注意以下配置：

- 正確創建了遠程帳戶。
- 服務端ip已被添加到數據庫配置中的`bind-address`配置項中，或者**不啓用**bind-address配置。
在Ubuntu發行版中，默認配置中bind-address配置項是**啓用**的。

## 修改用戶密碼
登陸數據庫之後，在數據庫命令行中輸入：

```
mysql> set password = password('[密碼內容]')
```

在`MySQL 8.0`之後，密碼不可使用`set password = password('xxx')`的方式修改，但新增了如下修改方式：

```
mysql> use mysql;
mysql> alter user '[用戶名]'@'[主機]' identified with mysql_native_password by '[新密碼]';
```

亦可使用`mysqladmin`工具修改密碼：

```
$ mysqladmin -u [用戶名] password '[密碼內容]' # 目標用戶不存在舊密碼時可用
$ mysqladmin -u [用戶名] -p password '[密碼內容]' # 目標用戶存在舊密碼時可用，會提示輸入舊密碼
$ mysqladmin -u [用戶名] -h [主機] -p password '[密碼內容]' # 修改遠程用戶密碼
```

還可采用更新`mysql.user`表的方式來更新密碼。

在`MySQL 5.6`及以下版本，密碼列名稱為`password`，`MySQL 5.7`及之後版本密碼列為`authentication_string`。

```sql
-- MySQL 5.6-
mysql> update mysql.user set password=password('[密碼]') where user='[用戶名]' and host='[主機]';

-- MySQL 5.7+
mysql> update mysql.user set authentication_string=password('[密碼]') where user='[用戶名]' and host='[主機]';
```

## 跳過登陸驗證
對於忘記密碼的情形，可通過配置跳過登陸密碼，免密登陸后再修改密碼。

修改`my.cnf`文件，在`[mysqld]`配置段添加：

```
skip-grant-tables
```

之後重啓數據庫服務即可免密登陸。

需要注意，以免密登錄方式登錄數據庫后，不能直接使用`set passowrd`的方式更新密碼，但依舊可以修改`mysql.user`表來更新密碼。

## 關於密碼策略
儅出現密碼策略相關的異常信息時，可查看相關環境變量：

```sql
> SHOW VARIABLES LIKE 'validate_password%';
+--------------------------------------+-------+
| Variable_name                        | Value |
+--------------------------------------+-------+
| validate_password_check_user_name    | OFF   |
| validate_password_dictionary_file    |       |
| validate_password_length             | 8     |
| validate_password_mixed_case_count   | 1     |
| validate_password_number_count       | 1     |
| validate_password_policy             | LOW   |
| validate_password_special_char_count | 1     |
+--------------------------------------+-------+
7 rows in set (0.01 sec)
```

可通過修改此類環境變量避免密碼策略相關的異常信息。

## 查看用戶信息
MySQL數據庫的用戶信息記錄在`mysql`庫中的`user`表中，查詢該表即可得到**用戶信息**：

```
mysql> select * from mysql.user;
```

## 創建/刪除用戶
在數據庫命令行中使用`create user`指令即可創建用戶：

```
mysql> create user [用戶名];
```

默認情況下創建的是不允許本地登錄的遠程用戶，以上指令相當於：

```
mysql> create user [用戶名@'%'];
```

創建本地用戶：

```
mysql> create user [用戶名@localhost];
```

需要注意，MySQL中同名本地用戶與遠程用戶間沒有關聯，本地用戶與遠程用戶密碼、權限等各自獨立。

刪除用戶操作類似，使用`drop user`指令：

```
mysql> drop user [用戶名@主機名/主機地址];
```

## 授權用戶
新創建的用戶不具有權限，需要使用管理員賬戶(一般爲`root`)對其進行授權。

授予某個用戶指定數據庫的查詢與更新權限：

```sql
mysql> grant select, update on [數據庫名].* to [用戶名]@[登錄方式];
```

授予某個用戶所有權限：

```sql
mysql> grant all privileges on *.* to [用戶名]@[登錄方式];
```

被授權的用戶默認不能將所擁有的權限授權給其它用戶，
如果需要使授權能夠被傳播則使用(一般不推薦這樣使用，數據庫權限應由DBA統一管理)：

```sql
mysql> grant all privileges on *.* to [用戶名]@[登錄方式] with grant option;
```

也可以通過修改`mysql.user`表來賦予權限：

```sql
mysql> update user set Host='[主機名稱]',select_priv='y', insert_priv='y',update_priv='y', Alter_priv='y',delete_priv='y',create_priv='y',drop_priv='y',reload_priv='y',shutdown_priv='y',Process_priv='y',file_priv='y',grant_priv='y',References_priv='y',index_priv='y',create_user_priv='y',show_db_priv='y',super_priv='y',create_tmp_table_priv='y',Lock_tables_priv='y',execute_priv='y',repl_slave_priv='y',repl_client_priv='y',create_view_priv='y',show_view_priv='y',create_routine_priv='y',alter_routine_priv='y',create_user_priv='y' where user='[用戶名]';
```

更新完用戶權限表之後，刷新權限信息：

```sql
mysql> flush privileges;
```

查看一個用戶的權限可以在數據庫命令行中使用`show grants`指令：

```sql
mysql> show grants; //顯示當前用戶的權限信息
mysql> show grants for [用戶名]@[主機地址]; //顯示指定用戶的權限信息
```



# 驅動配置
使用不同的開發語言/庫/平臺需要配置對應的驅動。

- `Java API`

	Java語言中與MySQL交互一般使用通用的JDBC接口，加載MySQL官方的JDBC驅動即可。
	Java IDE如`NetBeans`、`Eclipse`、`IntelliJ IDEA`等提供的MySQL數據庫管理功能也需要添加MySQL的JDBC驅動。

- `Qt API`

	使用Qt官方安裝包的Qt環境中無須額外配置(驅動已被集成至安裝包中)。
	ArchLinux中使用使用Qt5操作MySQL數據無需安裝額外的包(驅動已被集成至`Qt5`包組中)。
	Debian系發行版中使用Qt5操作MySQL數據庫需要安裝`libqt5sql-mysql`包。

- `C API`

	Debian/RedHat系發行版中使用`C API`連接mysql數據庫時需要安裝額外的開發頭文件包：

	```
	# apt-get install libmysqlclient-devel //大便系
	# yum/dnf install mysql-devel //紅帽系
	```

	ArchLinux中不需要，ArchLinux中的`mysql`包已經包含了開發頭文件。



# 基本操作
基本的數據庫管理、操作指令：

- `status;` 查看數據庫基本狀態
- `show status;` 查看數據庫環境變量
- `show databases;` 查看數據庫列表
- `create database [數據庫名];` 創建數據庫
- `drop database [數據庫名];` 刪除數據庫
- `use [數據庫名];` 切換正在使用的數據庫
- `desc [表名];` 查看指定表格的結構
- `truncate table [表名];` 清除指定表格的內容(速度快，但不可恢復)
- `delete from [表名];` 刪除指定表格的內容(速度慢，但可以恢復)

## 基本SQL語句
- `insert into [表名] ([列名1], [列名2], ....) values([值1], [值2], ....);` 增
- `delete from [表名] where [限制條件];` 刪
- `update [表名] set [列名] = '[內容]' where [列名] = '[內容]';` 改
- `select [列名] from [表名] where [限制條件];` 查
- `select count([統計內容]) from [表名];` 統計表中的指定記錄數
- `select [列名] from [表名] limit [數量] offset [起始行];` 從指定行開始查詢指定數量的記錄
- `select [列名] from [表名] limit [起始行], [數量];` 從指定行開始查詢指定數量的記錄

## 內置函數
使用**內置函數**可以查詢一些特殊的信息：

- `select user();` 查詢當前登錄的用戶
- `select database();` 查詢正在使用的數據庫名稱
- `select version();` 查詢數據庫的版本信息
- `select @@version_compile_os;` 查詢數據編譯平臺

## 複製表格
僅複製表格結構：

```sql
create table [新表] like [舊錶]
```

複製表格的結構和數據：

```sql
create table [新表] select * from [舊錶]
```

## 主鍵自增
設置指定表格主鍵自增：

```sql
mysql> alert table [表名] auto_increment=[數字]; //設置自增屬性
mysql> alter table [表名] change [主鍵列名] [主鍵列名] [屬性] auto_increment;
```

取消主鍵自增：

```sql
mysql> alter table [表名] change [列名] [列名] [屬性];
```

設置主鍵自增對於已有數據的列需要清空已有數據才能正常顯示。
必須是**主鍵**才能設置自增屬性。

可配置數據庫全局的自增起始值和自增步長，查看相關配置：

```
mysql> show global variables like "auto_increment%";
+--------------------------+-------+
| Variable_name            | Value |
+--------------------------+-------+
| auto_increment_increment | 1     |
| auto_increment_offset    | 1     |
+--------------------------+-------+
2 rows in set (0.00 sec)
```

- `auto_increment_increment` 自增步長
- `auto_increment_offset` 自增起始值

默認的自增偏移和自增步長均爲1，可通過`set global auto_increment_increment/auto_increment_offset = xxx`進行修改。

## 外鍵約束
InnoDB引擎支持外鍵約束，從表可引用主表的鍵/主鍵作爲外鍵，外鍵字段的值必須爲主表中對應字段已存在的值。
外鍵可用在`CREATE TABLE`和`ALTER TABLE`語句中，語法如下：

```sql
[CONSTRAINT [symbol]] FOREIGN KEY
    [index_name] (col_name, ...)
    REFERENCES tbl_name (col_name,...)
    [ON DELETE reference_option]
    [ON UPDATE reference_option]

reference_option:
    RESTRICT | CASCADE | SET NULL | NO ACTION | SET DEFAULT
```

創建外鍵約束時，可通過`reference_option`設置外鍵數據的更新、刪除行爲：

- `RESTRICT` 檢測主表數據是否被從表引用，未引用數據可刪除、修改，已被引用則不可刪除、修改
- `NO ACTION` 標準SQL中的關鍵字，等價於RESTRICT
- `CASCADE` 級聯，同步更新、刪除從表數據
- `SET NULL` 主表變化，從表的引用字段設爲NULL
- `DEFAULT` 默認操作，等價於RESTRICT

移除外鍵在`ALTER TABLE`中使用`DROP FOREIGN KEY fk_symbol`子句。

主表字段需要與從表的字段類型相同(範圍不同的類型如`INT`/`BIGINT`會造成外鍵創建失敗)。
約束名稱可以不指定，但若顯式指定約束名稱，則需要保證同一個數據庫內的約束名稱**唯一**，
約束名稱重複時會造成以下錯誤：

```
Error Code: 1022. Can't write; duplicate key in table '***'
```

使用VARCHAR類型作為外鍵時，不僅要注意字符長度，還要注意字符編碼類型(`DEFAULT CHARACTER SET`)和校驗類型(`COLLATE`)，
二者不同會造成外鍵創建失敗。
行類型(`ROW_FORMAT`)不同不影響外鍵的創建。
外鍵約束創建失敗時會出現如下錯誤信息：

```
Error Code: 1215. Cannot add the foreign key constraint
```

可使用`SHOW ENGINE INNODB STATUS`語句輸出最近的SQL執行的詳細狀態，查閱具體的錯誤信息。



# Row Formats (行格式)
表格的行格式決定了行的物理排列，會影響查詢、DML操作的性能。
隨著多個行存入相同的磁盤頁，查詢、索引查找等操作執行速度加快，並在寫出更新內容時消耗更少的緩存和IO。

MySQL使用的InnoDB存儲引擎支持四種行格式：`REDUNDANT`、`COMPACT`、`DYNAMIC`、`COMPRESSED`。

格式特性比較：

| Row Format | Compact Storage Characteristics | Enhanced Variable-Length Column Storage	Large | Index Key Prefix Support | Compression Support | Supported Tablespace Types | Required File Format |
| :- | :- | :- | :- | :- | :- | :- |
| REDUNDANT | No | No | No | No | system, file-per-table, general | Antelope or Barracuda |
| COMPACT | Yes | No | No | No | system, file-per-table, general | Antelope or Barracuda |
| DYNAMIC | Yes | Yes | Yes | No | system, file-per-table, general | Barracuda |
| COMPRESSED | Yes | Yes | Yes | Yes | file-per-table, general | Barracuda |

## REDUNDANT Row Format
REDUNDANT格式用於兼容舊版本的MySQL。

使用REDUNDANT行格式的表會將前768字節的變長列字段(VARCHAR、VARBINARY、BLOB、TEXT)存儲到B-tree節點索引中，
其餘内容存儲到溢出頁面中(overflow pages)。
大於等於768字節的定長列(fixed-length column)被編碼為變長列(variable-length column)，
從而可以在頁外存儲。
例如，在每個字符的最大大小可超過3字節時，CHAR(255)類型可以超過768字節(類似於`uff8mb4`編碼)。

若列小於等於768字節，溢出頁不會被使用，可能會降低某些IO開銷，因爲值完全存儲在B-tree節點中。
這在相對較小的BLOB列中工作良好，但會導致B-tree節點填充數據而非鍵值，進而降低效率。
若一張表帶有許多BLOB列會導致B-tree節點過滿，包含較少的行，使得整個索引效率低於行較短或列值存儲在頁外的情形。

## COMPACT Row Format
與REDUNDANT格式相比，COMPACT行格式能降低大約20％的存儲空間，但會某些操作的CPU開銷。
在受緩存命中率和磁盤速度限制的場景下，使用COMPACT格式可能會更快。
在CPU受限的場景下，使用COMPACT行格式可能會變慢。

## DYNAMIC Row Format
DYNAMIC行格式提供與REDUNDANT格式相同的存儲特徵，但增强了長變長列的存儲能力，並支持大型索引前綴。

當使用`ROW_FORMAT = DYNAMIC`創建表時，InnoDB可以完全在頁外存儲長的變長列值(VARCHAR，VARBINARY，BLOB和TEXT)，
聚集索引記錄只包含20字節的指針指向溢出頁面。大於或等於768字節定長字段被編碼為變長字段。

列是否存儲在頁外是否取決於頁面大小和行的總大小。當行太長時，選擇最長的列進行頁外存儲，直到聚簇索引記錄適合B-tree頁面。
小於或等於40字節的TEXT和BLOB列會存儲在行中。

DYNAMIC行格式保持在索引節點中存儲整行的效率(類似COMPACT和REDUNDANT)，但避免了用長列的大量數據内容填充B-tree節點的問題。
DYNAMIC行格式基於以下思想：
若一個大的數據值一部分存儲在頁外，則通常最有效的存儲方式是將整個值存儲在頁外。
使用DYNAMIC格式時，較短的列可能會保留在B樹節點中，從而最大限度地減少一行所需的溢出頁數。



# 常用設置

## 導出數據
使用`mysqldump`工具可以導出數據庫的內容，基本操作指令如下：

```
$ mysqldump -u"[用戶名]" -p"[密碼]" -A //導出所有數據庫
$ mysqldump -u"[用戶名]" -p"[密碼]" [要備份的數據庫名稱] //導出指定數據庫
$ mysqldump -u"[用戶名]" -p"[密碼]" [要備份的數據庫名稱] [要備份的表名稱] //導出指定數據庫中的指定表的內容
```

默認情況下，mysqldump工具會將導出的數據以SQL語句的形式輸出到終端，可以使用重定向將導出的內容寫入文本中：

```
$ mysqldump -u"[用戶名]" -p"[密碼]" -A > xxx.sql //導出的內容寫入 xxx.sql 文件中
```

mysqldump支持根據條件導出指定的內容(使用`-w`參數)：

```
$ mysqldump -u"[用戶名]" -p"[密碼]" -w"[限制條件]" [數據庫名] [表名]
```

導出內容時支持設定只導出數據(`-t`)或只導出表結構(`-d`)。

## 導入數據
導入數據需要在數據庫命令行中使用`source`指令：

```
mysql> source [數據庫備份文件]
```

導入數據庫時需要注意編碼問題，數據庫編碼、連接編碼、備份文件的編碼需要相同纔不會產生中文亂碼問題。

## 設置中文編碼
默認情況下，舊版的mysql數據庫的編碼爲`latin1`，此編碼不支持東亞語系的文字顯示，需要修改爲支持各國文字的`UTF-8`編碼。
對於部分使用`MariaDB`的發行版(如`ArchLinux`)，默認的編碼爲`UTF-8`，無需額外配置。

查看數據庫的默認的所有編碼信息：

```
mysql> show variables like 'character_set_%';
```

典型的結果如下所示：

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

- `character_set_client`、`character_set_connection`可以通過配置文件中的`[client]`段進行修改。
- `character_set_database`、`character_set_results`、`character_set_server`可以通過修改配置文件中的`[server]`段進行修改。

需要注意的是，每個數據庫可以擁有不同的編碼信息，查看指定數據庫的編碼：

```
mysql> use [數據庫名稱];
mysql> show variables like 'character_set_database';
```

修改指定數據庫的編碼：

```
mysql> alter database [數據庫名稱] CHARACTER SET [編碼類型(gbk/utf8)];
```

如果需要修改數據庫的默認編碼，則需要修改配置文件：

- 在`Debian`系中，配置文件爲`/etc/mysql/mariadb.conf.d/client.cnf`。
- 在`RedHat`系中，配置文件爲`/etc/my.cnf`。
- 在`ArchLinux`中，配置文件爲`/etc/mysql/my.cnf`。

在配置文件中加入下列配置：

```ini
[client]
# Default is Latin1, if you need UTF-8 set this (also in server section)
default-character-set = utf8
[server]
default-character-set = utf8
```

在`Windows`系統下，配置文件位於mysql的軟件主目錄下，名稱爲`my.ini`，該配置文件需要手動創建：

```ini
[server]
# mysql5.5版本之後[server]配置段不再使用default-character-set=utf8，該配置已被廢棄
character_set_server = utf8
[client]
# 客戶端配置不變
default-character-set = utf8
```

## 二進制數據
如果需要向數據庫中存儲二進制信息(比如**圖片**)，則字段應選擇`BLOB`類型(`binary large object`)。

MySQL中與BLOB相關的類型有四種，分別爲：`TinyBlob`、`Blob`、`MediumBlum`、`LongBlum`。
這四種類型之間的區別在於存儲文件大小上限不同。
`TinyBlob`最大`255B`，`Blob`最大`65KB`，`MediumBlob`最大`16MB`，`LongBlob`最大`4GB`。

## JSP編碼設置
在`JSP`開發中，編碼問題主要體現在以下幾個方面：

- 數據庫表的編碼：`ENGINE=InnoDB DEFAULT CHARSET=utf8`。
- 數據庫連接編碼：`jdbc:mysql://localhost:3306/xxx?useUnicode=true&characterEncoding=UTF-8`。
- 頁面提交內容的編碼：`request.setCharacterEncoding("UTF-8");response.setCharacterEncoding("UTF-8");`。

數據表的編碼需要與連接的編碼相同，否則讀取數據會出現中文亂碼，而JSP頁面中的內容編碼可以單獨指定。

## 時區問題
MySQL連接出現如下所示錯誤：

```
The server time zone value 'XXX' is unrecognized or represents more than one time zone. You must configure either the server or JDBC driver (via the serverTimezone configuration property) to use a more specifc time zone value if you want to utilize time zone support.
```

原因是服務端的時區信息未能正常獲取，需要在連接中顯式指明時區信息，如下所示：

```
jdbc:mysql://localhost:3306/xxx?serverTimezone=UTC //服務端時區信息不爲UTC時，需要改爲與服務端相匹配的時區
```

## 時間轉換
MySQL中使用內置函數`unix_timestamp(xxx)`可將時間轉換爲Unix時間戳(從`1970-1-1`至今的秒數)。

MySQL中的內置時間類型(`datetime`類型)在不同語言中的對應類型：

- Java中的`java.sql.Timestamp`類型：

	使用`Timestamp.getTime()`獲取時間對應的Unix時間戳。
	在Java中Timestamp類型精確到**微秒**，而MySQL中datetime類型精確到**秒**，
	相同時間在Java中獲得的時間戳應除以`1000`才能與MySQL中的時間戳相比較。
	如下所示：

	```java
	timestamp.getTime() / 1000; //獲取與MySQL中等價的Unix時間戳
	```

- C#中的`System.DateTime`類型：

	將在C#中獲得的`DateTime`實例與表示`1970-1-1`至今的時間相減，得到`System.TimeSpan`類型表示的時間間隔，
	訪問`TimeSpan.TotalSeconds`屬性獲得Unix時間戳。
	如下所示：

	```cs
	(dateTime - DateTime.Parse("1970-1-1")).TotalSeconds; //獲取時間戳
	```

## 禁用 DNS 解析
MySQL默認開啓了DNS解析，但在DNS服務器異常時，一次數據庫操作會異常緩慢，並在`/var/log/mysql/error.log`中寫入類似日誌：

```
[Warning] IP address 'xxx.xxx.xxx.xxx' could not be resolved: Temporary failure in name resolution
```

解決方法是禁用MySQL的DNS解析，在配置`my.cnf`中添加以下內容：

```
[mysqld]
skip-host-cache
skip-name-resolve
```



# 查看數據庫狀態
`information_schema`庫中存儲了MySQL數據庫的元數據。
通過使用SQL語句對庫中的各類表格進行查詢操作，可獲取MySQL中的各類狀態信息，如數據庫/表的名稱、列的數據類型、訪問權限等。

常用表格的功能：

| 表名 | 功能 |
| :- | :- |
| PROCESSLIST | 正在執行的綫程信息 |
| TABLES | 表格信息 |
| COLUMNS | 表格列信息 |
| SCHEMA_PRIVILEGES | 數據庫權限信息(自mysql.db表獲取) |
| USER_PRIVILEGES | 用戶權限信息(自mysql.user表獲取) |



# C API
MySQL數據庫提供了**C語言**接口用於數據庫交互，在`*nix`中，頭文件爲`/usr/include/mysql/mysql.h`。

在使用Unix工具鏈進行編譯時，需要添加參數`-lmysqlclient`用於鏈接`libmysqlclient.so`動態庫。

mysql的C語言綁定主要涉及以下幾種結構體類型：

- `MYSQL` 存儲連接相關信息
- `MYSQL_RES` 存儲查詢操作相關返回信息

## 連接數據庫
使用`mysql_init()`初始化連接信息結構體，使用`mysql_real_connect()`連接數據庫。

```c
MYSQL* mysql_init(MYSQL *mysql);
MYSQL* mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long clientflag);
```

- `mysql`參數標識連接。
- `host`、`user`、`passwd`參數依次爲**主機地址**、**數據庫用戶名**、**數據庫密碼**。
- `db`參數爲連接到的數據庫名稱。
- `port`參數用於顯式指定連接端口，`unix_socket`參數爲socket連接類型，`clientflag`爲mysql運行ODBC的標記，一般本地連接這三個參數全填`NULL`。

舊式的連接函數`mysql_connect()`已不再推薦使用，僅僅爲兼容而保留。

## 執行SQL語句
使用`mysql_query()`以及`mysql_real_query()`執行SQL語句：

```c
int mysql_query(MYSQL *mysql, const char *q);
int mysql_real_query(MYSQL *mysql, const char *q, unsigned long length);
```

兩函數區別如下：

- 一般性的SQL語句可以直接使用`mysql_query()`執行，`q`參數爲需要執行的SQL語句字符數組指針。
- `mysql_real_query()`相比`mysql_query()`而言效率更高，因爲其內部實現不調用`strlen()`來獲取字符數組長度。
此外，如果執行的sql語句中包含有二進制內容，則一定需要使用`mysql_real_query()`，
因爲`mysql_query()`會調用`strlen()`來獲取字符數組長度，而`strlen()`判斷字符數組結束是以`\0`作爲標誌的，
但對於二進制數據而言，數據中的`\0`可能是有效值，因而使用`mysql_query()`可能會造成對數據長度的誤判使得程序未按預期執行。

函數執行成功返回`0`，執行失敗時返回錯誤代碼。

## 處理查詢結果
使用下列函數對結果集進行操作：

```c
MYSQL_RES* mysql_store_result(MYSQL *mysql);
MYSQL_RES* mysql_use_result(MYSQL *mysql);
unsigned int mysql_field_count(MYSQL *mysql);
unsigned int mysql_num_fields(MYSQL_RES *res);
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
void mysql_data_seek(MYSQL_RES *result, my_ulonglong offset);
```

- `mysql_store_result()`和`mysql_use_result()`用於獲取查詢語句之後的結果集內容，二者的區別是前者會將結果集拷貝到本地，開銷大，後者直接讀取服務器中的數據，每次只拷貝一行，開銷小，但是後者需要在下一次SQL語句執行之前將結果集中的數據全部讀出，但前者就不需要。
- `mysql_field_count()`用於獲取最近查詢的列數。
- `mysql_num_fields()`用於獲取指定查詢結果的列數。
- `mysql_fetch_row()`用於按行讀取結果集中的內容，每次執行`mysql_fetch_row()`會返回下一行結果集的指針。返回值類型`MYSQL_ROW`的實際類型爲二維指針`char**`，保存了每一列的字符數組指針。
- `mysql_data_seek()`用於設置結果集讀取位置到指定的偏移量，`offset`參數取值爲`0`時，則重置結果集的讀取位置。

## 切換當前數據庫
使用`mysql_select_db()`函數切換數據庫：

```c
int mysql_select_db(MYSQL *mysql,const char *db);
```

相當於mysql指令`use [數據庫名]`。

## 關閉數據庫連接
使用`mysql_close()`函數關閉數據庫連接：

```c
void mysql_close(MYSQL *sock);
```

- 如果傳入的參數是指針，則指針所指向的MYSQL結構體內存區域會被釋放掉。
- 立即訪問執行`mysql_close()`之後的MYSQL指針會報錯(野指針)，如果在關閉連接之後需要重新啓用連接，需要重新執行初始化操作`mysql_init()`。
