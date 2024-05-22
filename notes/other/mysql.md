<!-- TOC -->

- [初始化與基本配置](#初始化與基本配置)
	- [數據庫初始化 (MySQL 5.7+)](#數據庫初始化-mysql-57)
	- [數據庫初始化 (MariaDB & MySQL 5.7-)](#數據庫初始化-mariadb--mysql-57-)
	- [手動配置](#手動配置)
	- [使用指定配置啓動](#使用指定配置啓動)
	- [驅動配置](#驅動配置)
- [服務管理](#服務管理)
	- [管理數據庫服務（Windows）](#管理數據庫服務windows)
	- [管理數據庫服務（Linux SystemD）](#管理數據庫服務linux-systemd)
	- [管理數據庫服務（BSD/Linux SysV）](#管理數據庫服務bsdlinux-sysv)
- [用戶登入與管理](#用戶登入與管理)
	- [管理用戶](#管理用戶)
		- [創建用戶](#創建用戶)
		- [授權用戶](#授權用戶)
		- [修改用戶密碼](#修改用戶密碼)
	- [跳過登入驗證](#跳過登入驗證)
	- [關於密碼策略](#關於密碼策略)
- [基本操作](#基本操作)
	- [基本SQL語句](#基本sql語句)
		- [CASE 與 IF](#case-與-if)
	- [內置函數](#內置函數)
	- [系統變量](#系統變量)
	- [複製表格](#複製表格)
	- [主鍵自增](#主鍵自增)
	- [外鍵約束](#外鍵約束)
		- [排查外鍵錯誤信息](#排查外鍵錯誤信息)
		- [臨時禁用/恢復外鍵約束](#臨時禁用恢復外鍵約束)
- [表格優化與修復](#表格優化與修復)
	- [optimize](#optimize)
	- [repair](#repair)
- [文本類型](#文本類型)
	- [CHAR相關類型與TEXT相關類型的區別](#char相關類型與text相關類型的區別)
	- [字符集](#字符集)
	- [字符類型自動轉換](#字符類型自動轉換)
	- [枚舉類型](#枚舉類型)
- [時間類型](#時間類型)
	- [毫秒/微秒支持](#毫秒微秒支持)
- [JSON 類型](#json-類型)
	- [基本JSON操作](#基本json操作)
	- [查找與更新JSON節點](#查找與更新json節點)
- [Index（索引）](#index索引)
	- [索引類型](#索引類型)
	- [索引實現與優化](#索引實現與優化)
	- [索引離散性](#索引離散性)
	- [翻頁查詢優化](#翻頁查詢優化)
- [Row Formats（行格式）](#row-formats行格式)
	- [REDUNDANT Row Format](#redundant-row-format)
	- [COMPACT Row Format](#compact-row-format)
	- [DYNAMIC Row Format](#dynamic-row-format)
- [FEDERATED 存儲引擎](#federated-存儲引擎)
	- [啟用FEDERATED引擎](#啟用federated引擎)
	- [創建FEDERATED表](#創建federated表)
- [Data-at-Rest Encryption（靜態加密）](#data-at-rest-encryption靜態加密)
	- [啟用keyring_file插件](#啟用keyring_file插件)
	- [啟用/禁用表格加密](#啟用禁用表格加密)
	- [Master Key Rotation（主密鑰輪換）](#master-key-rotation主密鑰輪換)
- [MySQL高可用](#mysql高可用)
	- [Replication（複製）](#replication複製)
		- [解決數據衝突](#解決數據衝突)
		- [Binlog位置錯誤](#binlog位置錯誤)
- [常用功能和配置](#常用功能和配置)
	- [導出數據](#導出數據)
	- [導入數據](#導入數據)
	- [設置中文編碼](#設置中文編碼)
	- [二進制數據](#二進制數據)
	- [JSP編碼設置](#jsp編碼設置)
	- [時區問題](#時區問題)
	- [時間轉換](#時間轉換)
	- [禁用 DNS 解析](#禁用-dns-解析)
- [查看數據庫狀態](#查看數據庫狀態)
- [性能測試](#性能測試)
	- [mysqlslap](#mysqlslap)
	- [寫入性能相關優化參數](#寫入性能相關優化參數)
- [C API](#c-api)
	- [連接數據庫](#連接數據庫)
	- [執行SQL語句](#執行sql語句)
	- [處理查詢結果](#處理查詢結果)
	- [切換當前數據庫](#切換當前數據庫)
	- [關閉數據庫連接](#關閉數據庫連接)
- [問題註記](#問題註記)
	- [MySQL error: sql_mode=only_full_group_by](#mysql-error-sql_modeonly_full_group_by)
	- [Error Code: 1175. You are using safe update mode and you tried to update a table without a WHERE that uses a KEY column To disable safe mode, toggle the option in Preferences -> SQL Queries and reconnect.](#error-code-1175-you-are-using-safe-update-mode-and-you-tried-to-update-a-table-without-a-where-that-uses-a-key-column-to-disable-safe-mode-toggle-the-option-in-preferences---sql-queries-and-reconnect)
	- [[42000][1071] Specified key was too long; max key length is 3072 bytes](#420001071-specified-key-was-too-long-max-key-length-is-3072-bytes)
	- [[ERROR] [MY-010123] [Server] Fatal error: Please read "Security" section of the manual to find out how to run mysqld as root!](#error-my-010123-server-fatal-error-please-read-security-section-of-the-manual-to-find-out-how-to-run-mysqld-as-root)
		- [ERROR 1396 (HY000): Operation CREATE USER failed for 'root'@'xxx'](#error-1396-hy000-operation-create-user-failed-for-rootxxx)
		- [MySQL reset auto_increment value in Innodb after server restart](#mysql-reset-auto_increment-value-in-innodb-after-server-restart)
		- [mysqld: Can't create directory 'xxx' (Errcode: 13 - Permission denied)](#mysqld-cant-create-directory-xxx-errcode-13---permission-denied)

<!-- /TOC -->



# 初始化與基本配置
對於`MariaDB`與`MySQL`而言，在初始化操作上有着明顯的區別。

## 數據庫初始化 (MySQL 5.7+)
`MySQL`在`5.7`版本開始變更了初始化的方式，原先使用的`mysql_install_db`指令已被廢棄，
相關功能被整合到了`mysqld`中，通過`--initialize`系列參數進行數據庫初始化：

```
# mysqld --initialize
```

使用`--initialize`參數初始化會默認創建帶有密碼的`root`賬戶，
密碼會記錄在`主機名.err`文件中，日至內容大致爲：

```
[Note] A temporary password is generated for root@localhost: [password]
```

可以使用`--initialize-insecure`參數初始化並創建不帶密碼的`root`賬戶，如下所示：

```
# mysqld --initialize-insecure
```

## 數據庫初始化 (MariaDB & MySQL 5.7-)
`MariaDB`在MySQL被`Oracle`收購之後，被各大Linux發行版作爲默認的MySQL替代版本。

作爲MySQL的分支，並沒有採用`MySQL 5.7`版本引入的新初始化方式，
依舊使用`mysql_install_db`指令進行數據庫初始化，以ArchLinux爲例，初始化操作爲：

```
# mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
```

對於非軟件源安裝的MySQL，可能會找不到mysql_install_db工具，
該工具為perl腳本，不在`$MYSQL_HOME\bin`下，而是位於`$MYSQL_HOME\scripts`路徑中。

## 手動配置
部分Linux發行版將倉庫中默認的MySQL數據庫遷移到了MariaDB分支，
因而在Linux下使用`Oracle MySQL`需要從官網下載二進制包手動進行配置。

Linux下啓動mysql服務需要顯式使用`--basedir`、`--datadir`等參數指定數據庫的相關路徑，
在MySQL的`bin`目錄下執行如下所示指令：

```
$ ./mysqld --initialize-insecure --basedir=軟件路徑 --datadir=數據路徑
```

啓動數據庫服務需要指定一個擁有權限的路徑/文件作爲socket路徑，在啓動時會創建該文件
（使用默認參數啓動數據庫，服務會嘗試使用`/run/mysqld/mysqld.sock`文件作爲鎖文件，
但普通用戶不具有該路徑的權限，因而需要顯式指定`--socket`參數）：

```
$ ./mysql --socket=socket文件路徑 -u root
```

## 使用指定配置啓動
可以將MySQL的啓動參數寫入配置文件中，啓動時指定配置文件的路徑即可：

```
$ ./mysqld --defaults-file=配置文件路徑
```

啓動操作類似：

```
$ ./mysqld --defaults-file=配置文件路徑
```

一個精簡的配置文件大致結構如下：

```ini
[mysqld]
basedir = # 軟件路徑
datadir = # 數據庫路徑
port = # 服務端口
server_id = # 服務id
socket = # 服務socket文件位置

sql_mode=NO_ENGINE_SUBSTITUTION,STRICT_TRANS_TABLES

[server]
character_set_server = # 數據庫編碼

[client]
default-character-set = # 連接編碼
socket = # 客戶端啓動socket文件位置
```

對於root用戶，直接啟動mysqld進程會出現異常，需要指定啟動用戶：

```
# mysqld --user=root
```

## 驅動配置
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

	```html
	# apt-get install libmysqlclient-devel <!-- 大便系 -->
	# yum/dnf install mysql-devel <!-- 紅帽系 -->
	```

	ArchLinux中不需要，ArchLinux中的`mysql`包已經包含了開發頭文件。



# 服務管理
除了使用`mysqld`指令啓動服務之外，在不同的OS上，可以使用OS自帶的服務管理工具啓動MySQL服務。

## 管理數據庫服務（Windows）
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

## 管理數據庫服務（Linux SystemD）
採用Systemd的發行版中可以使用`systemctl`指令管理MySQL服務：

```html
# systemctl status mysqld <!-- 查看mysql服務狀態 -->
# systemctl start mysqld <!-- 啓動mysql服務 -->
# systemctl stop mysqld <!-- 停止mysql服務 -->
# systemctl restart mysqld <!-- 重啓mysql服務 -->
```

## 管理數據庫服務（BSD/Linux SysV）
舊式的Linux發行版以及BSD系列使用`service`指令管理MySQL服務：

```
# service mysql status
# service mysql start
# service mysql stop
# service mysql restart
```



# 用戶登入與管理
在成功啓動了MySQL服務之後，使用`mysql`指令登入：

```
$ mysql -u 用戶名
```

對於有密碼的用戶，需要使用`-p`參數登入：

```
$ mysql -u 用戶名 -p
```

默認情況下爲登入本機的數據庫，如果需要**遠程登入**到其它主機上的數據庫，應該使用`-h`參數：

```
$ mysql -h 目標主機地址 -u 用戶名 -p
```

遠程登入需要注意以下配置：

- 正確創建了遠程帳戶。
- 服務端ip已被添加到數據庫配置中的`bind-address`配置項中，或者**不啓用**bind-address配置。
在Ubuntu發行版中，默認配置中bind-address配置項是**啓用**的。

## 管理用戶
MySQL數據庫的用戶信息記錄在`mysql`庫中的`user`表中，查詢該表即可得到**用戶信息**：

```
mysql> select * from mysql.user;
```

各類用戶管理操作實際均為對該表的操作。

### 創建用戶
在數據庫命令行中使用`create user`指令即可創建用戶：

```sql
mysql> create user 用戶名;
```

默認情況下創建的是不允許本地登錄的遠程用戶，以上指令相當於：

```sql
mysql> create user 用戶名@'%';
```

創建本地用戶：

```sql
mysql> create user 用戶名@localhost;
```

创建用户时可以指定密码：

```sql
mysql> create user 用戶名@'主機' identified by '密码';
# 修改用戶密碼操作類似
mysql> alter user 用戶名@'主機' identified by '新密碼';
```

MySQL中同名本地用戶與遠程用戶間沒有關聯，本地用戶與遠程用戶密碼、權限等各自獨立。

刪除用戶操作類似，使用`drop user`指令：

```sql
mysql> drop user 用戶名@'主機';
```

### 授權用戶
新創建的用戶不具有權限，需要使用管理員賬戶（通常爲`root`）對其進行授權。

授予某個用戶所有權限：

```sql
mysql> grant all on *.* to 用戶名@登錄方式;
```

被授權的用戶默認不能將所擁有的權限授權給其它用戶，
如果需要使授權能夠被傳播則使用（一般不推薦這樣使用，數據庫權限應由DBA統一管理）：

```sql
mysql> grant all on *.* to 用戶名@登錄方式 with grant option;
```

授予某個用戶指定數據庫的查詢與更新權限：

```sql
mysql> grant select,update on 數據庫名.* to 用戶名@登錄方式;
```

也可以通過修改`mysql.user`表來指定賦予權限（不同版本的MySQL權限字段有所不同）：

```sql
mysql> update user set Host='主機名',select_priv='y', insert_priv='y',update_priv='y', Alter_priv='y',delete_priv='y',create_priv='y',drop_priv='y',reload_priv='y',shutdown_priv='y',Process_priv='y',file_priv='y',grant_priv='y',References_priv='y',index_priv='y',create_user_priv='y',show_db_priv='y',super_priv='y',create_tmp_table_priv='y',Lock_tables_priv='y',execute_priv='y',repl_slave_priv='y',repl_client_priv='y',create_view_priv='y',show_view_priv='y',create_routine_priv='y',alter_routine_priv='y',create_user_priv='y' where user='用戶名';
```

更新完用戶權限表之後，刷新權限信息：

```sql
mysql> flush privileges;
```

查看一個用戶的權限可以在數據庫命令行中使用`show grants`指令：

```sql
mysql> show grants; # 顯示當前用戶的權限信息
mysql> show grants for 用戶名@主機地址; # 顯示指定用戶的權限信息
```

### 修改用戶密碼
使用`mysqladmin`工具修改密碼：

```html
$ mysqladmin -u 用戶名 password '密碼內容' <!-- 目標用戶不存在舊密碼時可用 -->
$ mysqladmin -u 用戶名 -p password '密碼內容' <!-- 目標用戶存在舊密碼時可用，會提示輸入舊密碼 -->
$ mysqladmin -u 用戶名 -h 主機 -p password '密碼內容' <!-- 修改遠程用戶密碼 -->
```

提示輸入新密碼時，直接使用回車鍵輸入空白密碼則會清除指定用戶的密碼。

若出现如下错误：

```
You cannot use 'password' command as mysqld runs
 with grant tables disabled (was started with --skip-grant-tables).
Use: "mysqladmin flush-privileges password '*'" instead
```

则应按照提示添加`flush-privileges`參數：

```
$ mysqladmin -u 用戶名 -p flush-privileges password '密碼內容'
```

亦可直接在數據庫中執行指令修改密碼：

```sql
mysql> alter user 用戶名@'主機' identified by '新密碼';
```

在`MySQL 8.0`之前，可使用`set password`指令修改密碼：

```sql
mysql> set password = password('密碼內容')
```

用戶密碼存儲在`mysql.user`表中，因此還可采用更新表字段的方式來更新密碼；
`MySQL 5.6`及以下版本，密碼列名稱為`password`，
`MySQL 5.7`及之後版本密碼列為`authentication_string`。

```sql
-- MySQL 5.6-
mysql> update mysql.user set password=password('密碼') where user='用戶名' and host='主機';

-- MySQL 5.7+
mysql> update mysql.user set authentication_string=password('密碼') where user='用戶名' and host='主機';
```

更新密碼或Host主機限制等規則後，若未立即生效，則可嘗試刷新權限：

```
mysql> flush privileges;
Query OK, 0 rows affected (0.00 sec)
```

## 跳過登入驗證
對於忘記密碼的情形，可通過配置跳過登入密碼，免密登入后再修改密碼。

修改`my.cnf`文件，在`[mysqld]`配置段添加：

```ini
[mysqld]
...
skip-grant-tables
...
```

之後重啓數據庫服務即可免密登入。

以免密登錄方式登錄數據庫后，不能直接使用`set passowrd`的方式更新密碼，
但依舊可以修改`mysql.user`表來更新密碼。

## 關於密碼策略
儅出現密碼策略相關的異常信息時，可查看相關環境變量：

```sql
mysql> SHOW VARIABLES LIKE 'validate_password%';
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



# 基本操作
基本的數據庫管理、操作指令：

| 指令 | 說明 |
| :- | :- |
| `status;` | 查看數據庫基本狀態 |
| `show status;` | 查看數據庫環境變量 |
| `show databases;` | 查看數據庫列表 |
| `create database 數據庫名;` | 創建數據庫 |
| `drop database 數據庫名;` | 刪除數據庫 |
| `use 數據庫名;` | 切換正在使用的數據庫 |
| `desc 表名;` | 查看數據表結構(以表格形式列出字段定義) |
| `show create table 表名` | 查看數據表的創建SQL |
| `drop table [表名]` | 刪除指定表格 |
| `truncate table [表名];` | 清除指定表格的內容(速度快，但不可恢復) |
| `delete from [表名];` | 刪除指定表格的內容(速度慢，但可以恢復) |

## 基本SQL語句
SQL語句的詳細語法說明參考[官方文檔](https://dev.mysql.com/doc/refman/en/sql-statements.html)。
常用的數據增刪改查語句如下：

```sql
-- 增
insert into 表名 (列名1, 列名2, ....) values (值1, 值2, ....);

-- 刪
delete from 表名 where 限制條件;

-- 改
update 表名 set 列名 = '內容' where 列名 = '內容';

-- 查
select 列名 from 表名 where 限制條件;
select 列名 from 表名 limit 數量 offset 起始行; -- 從指定行開始查詢指定數量的記錄
select 列名 from 表名 limit 起始行, 數量; -- 從指定行開始查詢指定數量的記錄
```

### CASE 與 IF
使用`case`或`if`語法可實現對指定字段的條件判斷，並根據條件設定值。

case用於多重條件判斷：

```sql
CASE
    WHEN condition1 THEN result1
    WHEN condition2 THEN result2
    WHEN conditionN THEN resultN
    ELSE result
END;
```

if用於單一條件判斷：

```sql
IF(expression, expr_true, expr_false);
```

case與if可用於多種場景，如查詢、排序、更新中：

```sql
# 數據查詢
SELECT OrderID, Quantity,
CASE
    WHEN Quantity > 30 THEN "The quantity is greater than 30"
    ELSE "The quantity is under 30"
END
FROM OrderDetails;

SELECT OrderID, Quantity,
IF(Quantity > 30, "The quantity is greater than 30", "The quantity is under 30")
FROM OrderDetails;

# 數據排序
SELECT CustomerName, City, Country
FROM Customers
ORDER BY
CASE
    WHEN City IS NULL THEN Country
    ELSE City
END;

SELECT CustomerName, City, Country
FROM Customers
ORDER BY IF(City IS NULL, Country, City);

# 數據更新
UPDATE OrderDetails SET Quantity = IF(Quantity > 0, Quantity, -1);
UPDATE OrderDetails SET Quantity = CASE WHEN Quantity > 0 THEN Quantity ELSE -1 END;
```

## 內置函數
MySQL提供了大量**內置函數**，包含各類功能。

- 信息查詢類

	MySQL環境中的信息可通過對應函數查詢。

	```html
	user() <!-- 查詢當前登錄的用戶 -->
	database() <!-- 查詢正在使用的數據庫名稱 -->
	version() <!-- 查詢數據庫的版本信息 -->
	```

- 聚合函數

	聚合函數用於實現統計類功能，通常對一個數據集進行操作。

	```html
	count() <!-- 統計數據數目 -->
	max() <!-- 統計數據最大值 -->
	min() <!-- 統計數據最小值 -->
	avg() <!-- 統計數據平均值 -->
	```

常規函數可進行嵌套、組合使用，但聚合函數之間嵌套則需要搭配子查詢
（聚合函數輸入參數則為數據集，輸出結果是單個值，不能直接被其它聚合函數使用）。

## 系統變量
MySQL使用`@@變量名`語法訪問變量，MySQL定義了大量系統變量用於配置數據庫、提供內部信息等功能。

變量按作用域可分為GLOBAL（**全局變量**）和SESSION（**會話變量**），
查詢、修改全局變量需要使用`global`關鍵字修飾，無關鍵字修飾時默認訪問會話變量。
語法示例：

```sql
-- 查詢變量
> select @@變量名; -- 查詢當前會話變量
> select @@session.變量名; -- 等價於 select @變量名;
> select @@global.變量名; -- 查詢全局變量

-- 修改變量
> set @@變量名 = '內容'; -- 設置當前會話變量
> set @@session.變量名 = '內容'; -- 等價於 set @@變量名 = '內容';
> set @@global.變量名 = '內容'; -- 設置全局變量
```

常用變量說明：

| 系統變量 | 說明 |
| :- | :- |
| `@@version_compile_os` | 數據庫編譯平臺 |
| `@@sql_mode` | 數據庫的SQL特性 |
| `@@time_zone` | 數據庫時間使用時區 |

## 複製表格
僅複製表格結構：

```sql
create table 新表名 like 舊表名;
```

複製表格的結構和數據：

```sql
create table 新表 select * from 舊表;
```

## 主鍵自增
設置指定表格主鍵自增：

```sql
alter table 表名 auto_increment=數字; -- 設置自增屬性
alter table 表名 change 主鍵列名 auto_increment;
```

取消主鍵自增：

```sql
alter table 表名 change 列名 列名 屬性;
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

默認的自增偏移和自增步長均爲1，
可通過`SET GLOBAL auto_increment_increment/auto_increment_offset = xxx`進行修改。

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

創建外鍵約束時，可通過`reference_option`設置外鍵數據的更新(`ON UPDATE`)、刪除(`ON DELETE`)行爲：

| 約束類型 | 說明 |
| :- | :- |
| RESTRICT | 檢測主表數據是否被從表引用，未引用數據可刪除、修改，已被引用則不可刪除、修改 |
| NO ACTION | 標準SQL中的關鍵字，等價於RESTRICT |
| CASCADE | 級聯，同步更新、刪除從表數據 |
| SET NULL | 主表變化，從表的引用字段設爲NULL |
| DEFAULT | 默認操作，等價於RESTRICT |

移除外鍵在`ALTER TABLE`中使用`DROP FOREIGN KEY fk_symbol`子句。

主表字段需要與從表的字段類型相同(範圍不同的類型如`INT`/`BIGINT`會造成外鍵創建失敗)。
約束名稱可以不指定，但若顯式指定約束名稱，則需要保證同一個數據庫內的約束名稱**唯一**，
約束名稱重複時會造成以下錯誤：

```
Error Code: 1022. Can't write; duplicate key in table '***'
```

使用VARCHAR類型作為外鍵時，不僅要注意字符長度，
還要注意`DEFAULT CHARACTER SET`（**字符編碼類型**）和`COLLATE`（**校驗類型**），
二者不同會造成外鍵創建失敗。`ROW_FORMAT`（行類型）不同不影響外鍵的創建。

### 排查外鍵錯誤信息
外鍵約束創建失敗時會出現如下錯誤信息：

```
Error Code: 1215. Cannot add the foreign key constraint
```

可使用`SHOW ENGINE INNODB STATUS`語句輸出最近的SQL執行的詳細狀態，查閱具體的錯誤信息。

已建立外鍵關聯的表格可直接根據表格名稱查詢外鍵被引用的信息：

```sql
select * from INFORMATION_SCHEMA.KEY_COLUMN_USAGE where REFERENCED_TABLE_NAME='被引用的表名稱';
```

### 臨時禁用/恢復外鍵約束
在某些特殊場景下（truncate等），可以通過修改配置`FOREIGN_KEY_CHECKS`臨時禁用/禁用外鍵約束檢查：

```sql
# 禁用外鍵約束
mysql> SET FOREIGN_KEY_CHECKS = 0;

# 啟用外鍵約束
mysql> SET FOREIGN_KEY_CHECKS = 1;
```



# 表格優化與修復
使用`optimize/repair`指令對表格進行優化與修復：

- `optimize table 表名;` 優化表（整理磁盤排布，優化表格性能，釋放額外佔用的空間）
- `repair table 表名;` 修復表（用於表格原數據損壞的情形）

## optimize
使用`delete`語句刪除數據時，表格佔用的磁盤空間並未立即回收，需要使用`optimize`指令對表格進行優化，
執行optimize後磁盤上對應表格的數據會被重排，索引會被優化，佔用的多餘數據/索引空間會被回收，。

對於數據量較大的表，通常需要定期執行optimize指令以保證表格處於最佳狀態，擁有最好的性能。
若表格長時間未執行過optimize指令，則優化過程會耗時較長，根據表格數據量大小，會佔用屬分鐘乃至數小時。
執行優化操作期間表格會被加鎖，因而需要避免在業務高峰期進行表格優化操作。

## repair
當部分操作失敗（如創建索引、優化表格等）、磁盤數據表文件被意外修改時，
可能會造成表格元數據異常，導致查詢等操作抱錯。
此時可嘗試使用`repair`指令對表格進行修復，repair指令會嘗試修復表格，重建元數據信息。



# 文本類型
常用的文本類型包括`CHAR`、`VARCHAR`、`TINYTEXT`，`TEXT`、`MEDIUMTEXT`、`LONGTEXT`等。

`CHAR/VARCHAR`類型在定義時需要指示字段的長度：

- CHAR類型為固定長度（無論字符串實際長度多少佔用空間均衡定，剩餘空間在字符串右側填充空格），範圍0~255；
- VARCHAR類型為可變長度（佔用空間根據字符串實際長度變化），範圍0~65535。

`TINYTEXT/TEXT/MEDIUMTEXT/LONGTEXT`等類型則無需指定長度，長度範圍固定：

- TINYTEXT(255 - 255B)
- TEXT(65,535 - 64KB)
- MEDIUMTEXT(16,777,215 - 16MB)
- LONGTEXT(4,294,967,295 - 4GB)

## CHAR相關類型與TEXT相關類型的區別
CHAR相關類型與TEXT相關類型存在顯著的區別：

- 在MyISAM引擎中，CHAR系列類型直接存儲在表格內部，
而TEXT系列類型數據存儲在表外部，表內對應的列中僅存儲一個指針指向表外的數據區。
因此，CHAR系列類型速度相對於TEXT類型更快（內聯數據，節省一次尋址時間）。
- 在InnoDB引擎中，根據行格式（Row Format）可能會存在多種情形，但對變長文本類型（VARCHAR/TEXT）一視同仁。
- 設置普通索引時，CHAR系列不需要指定範圍，TEXT系列類型僅支持前N個字符索引，在創建索引時需要指定範圍。

## 字符集
不同字符集下單個字符佔用的實際空間存在差異，因此文本類型實際可容納字符數目並不一定能達到設定的大小。
例如`VARCHAR(255)`類型的列理論上能存儲最大255個字符，但只有在使用單字節字符集(如`latin1`)時才能達到設定的容量，
若字符集為`utf8`(`utf8mb3`，一個字符佔用3字節)、`utf8mb4`(一個字符佔用4字節)等。

實際可用字符數目計算方式為：

```
實際可容納的字符數目 = 設置的字符的數目 / 編碼的單字符字節佔用數目
```

即對於使用utf8編碼的VARCHAR類型，最大可容納字符數目僅有`65535 / 3 == 21845`，
使用JDBC與MySQL交互時，操作utf8編碼的VARCHAR類型常見的一種異常即為：

```
Caused by: com.mysql.jdbc.exceptions.jdbc4.MySQLSyntaxErrorException: Column length too big for column 'xxx' (max = 21845); use BLOB or TEXT instead
...
```

## 字符類型自動轉換
MySQL支持自動轉換`VARCHAR(n)`(n > 65,535)到合適的類型(MEDIUMTEXT/LONGTEXT等)。

在未開啟SQL MODE`STRICT_TRANS_TABLES/STRICT_ALL_TABLES`的MySQL中，
創建CHAR/VARCHAR超過長度上限(如`VARCHAR(65536)`)，MySQL根據實際長度將其轉換為匹配的TEXT類型，
同時會輸出如下警告信息：

```
0 row(s) affected, 1 warning(s): 1246 Converting column 'xxx' from VARCHAR to TEXT
```

## 枚舉類型
MySQL提供了可限制文本內容的[**枚舉類型**](https://dev.mysql.com/doc/refman/en/enum.html)。
枚舉類型是一個文本對象，但內容只能為列出的特定文本，語法示例：

```sql
CREATE TABLE Xxx (
	...
    Xxx ENUM('abc', 'cde', 'efg'), # 該列的內容只能為'abc', 'cde', 'efg'其中之一
	...
);
```



# 時間類型
MySQL中時間類型包括`DATE`、`TIME`、`DATETIME`、`TIMESTAMP`等，
詳情參考[MySQL官方文檔](https://dev.mysql.com/doc/refman/en/datetime.html)。

DATETIME/TIMESTAMP標準時間格式為`YYYY-MM-DD hh:mm:ss[.fraction]`，
DATETIME時間範圍為`1000-01-01 00:00:00`到`9999-12-31 23:59:59`，
TIMESTAMP時間範圍為`1970-01-01 00:00:01`到`2038-01-19 03:14:07`。

二者均支持使用CURRENT_TIMESTAMP設置默認值：

```sql
CREATE TABLE t1 (
  ts TIMESTAMP DEFAULT CURRENT_TIMESTAMP ,
  dt DATETIME DEFAULT CURRENT_TIMESTAMP
);
```

僅設置默認值會在數據插入時設置時間戳（之後更新操作時不再變化），
可設置時間隨更新操作自動更新：

```sql
CREATE TABLE t1 (
  ts TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  dt DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
```

參考[MySQL官方文檔](https://dev.mysql.com/doc/refman/en/timestamp-initialization.html)

## 毫秒/微秒支持
MySQL從5.6開始支持高精度時間，詳情參考
[MySQL文檔](https://dev.mysql.com/doc/refman/en/fractional-seconds.html)。

默認時間類型僅精確到**秒**級，更高精度的時間使用語法`type_name(fsp)`，
type_name可為TIME/DATETIME/TIMESTAMP，fsp為數值，範圍`0 ~ 6`。

DATETIME精確到毫秒：

```
DATETIME(3)
```

TIMESTAMP精確到微秒：

```
TIMESTAMP(6)
```

使用CURRENT_TIMESTAMP為時間設置默認值時，需要與時間精度匹配，
即DATETIME(3)對應使用`CURRENT_TIMESTAMP(3)`，TIMESTAMP(6)對應使用`CURRENT_TIMESTAMP(6)`。



# JSON 類型
JSON類型是`MySQL 5.7.8`中引入的特性，原生提供對JSON數據類型的支持，
並提供一系列JSON操作相關的內置函數。

JSON類型在存儲上大致類似於`LONGBLOB`或`LONGTEXT`；
与`BLOB`、`TEXT`等类型类似，JSON類型字段不能帶有**默认值**。

詳細說明參考[MySQL官方文檔](https://dev.mysql.com/doc/refman/en/json.html)。

## 基本JSON操作
使用`JSON_ARRAY()`/`JSON_OBJECT()`函數定義JSON數組/對象；

```sql
mysql> SELECT JSON_ARRAY(1, 2, 3, 4);
+------------------------+
| JSON_ARRAY(1, 2, 3, 4) |
+------------------------+
| [1, 2, 3, 4]           |
+------------------------+
1 row in set (0.00 sec)

mysql> SELECT JSON_OBJECT(1, 2, 3, 4);
+-------------------------+
| JSON_OBJECT(1, 2, 3, 4) |
+-------------------------+
| {"1": 2, "3": 4}        |
+-------------------------+
1 row in set (0.00 sec)
```

使用`->`/`->>`函數訪問對象中的屬性：

```sql

```

以MySQL 8.0為例，完整的JSON函數列表參照
[MySQL官方文檔 12.18 JSON Functions](https://dev.mysql.com/doc/refman/8.0/en/json-functions.html)。

## 查找與更新JSON節點
MySQL沒有直接提供基於內容刪除節點、替換節點內容的函數，相關功能可通過函數組合實現。
MySQL提供的JSON_REMOVE()函數基於索引刪除內容，而JSON_SEARCH()函數可基於內容查找節點位置，
因此組合兩個函數即可實現目標功能。

- 根據內容刪除節點

	組合函數調用：

	```sql
	JSON_REMOVE(xxx_json_cloumn, JSON_UNQUOTE(JSON_SEARCH(xxx_json_cloumn, 'all', 'content_need_be_deleted')))
	```

	完整查找並刪除內容SQL語句：

	```sql
	update xxx_table set xxx_json_cloumn = JSON_REMOVE(xxx_json_cloumn, JSON_UNQUOTE(JSON_SEARCH(xxx_json_cloumn, 'all', 'content_need_be_deleted'))) where JSON_CONTAINS(xxx_json_cloumn, '"content_need_be_deleted"') = 1;
	```

	需要注意，JSON_REMOVE()函數僅能移除單個節點，當JSON_SEARCH()找到了多個節點時會產生錯誤。

- 替換目標節點的內容

	```sql
	JSON_REPLACE(xxx_json_cloumn, JSON_UNQUOTE(JSON_SEARCH(xxx_json_cloumn, 'all', 'old_content')), 'new_content')
	```

使用JSON_SEARCH()函數查找得到的節點位置結果使用雙引號包裹，不可直接使用，
需要使用JSON_UNQUOTE()處理後才能被其它接收JSON位置的函數(如JSON_REPLACE())使用。



# Index（索引）
索引被用於快速查找包含特定列值的行。在無索引的情況下，MySQL會從首行開始讀取整張表來查找相關的行。
查找的消耗會隨著表格的增大而增大。若表格查詢的列已建立索引，則MySQL能夠快速地找到數據文件中的位置，
而不必查找所有數據，相比順序地讀取每一行要快得多。

## 索引類型
索引分為`Clustered Index`（聚簇索引）和`Secondary Index`（輔助索引/二級索引）。

對InnoDB引擎而言，聚簇索引實際是Primary Key（主鍵索引）的同義詞；
而輔助索引則包含Unique Key、Index、Prefix、Full Text等多種。

| 索引類型 | 說明 |
| :- | :- |
| Primary Key | 每張表只能擁有一個主鍵索引，在InnoDB中，未顯式設定主鍵時，會自動將帶有唯一索引的字段作為主鍵，不滿足則否則將自動創建一個6 Byte的自增字段作為主鍵 |
| Unique Key | 帶有唯一性約束的索引，數據不可重複，可為NULL |
| Index | 常規索引，數據可重複，可為NULL |
| Prefix | 前綴索引，僅適用於文本相關類型，對文本的前幾個字符創建索引，相比常規索引數據量更小 |
| Full Text | 全文索引，僅用於文本相關類型，主要用於優化大數據量的自然語言文本的搜索 |

## 索引實現與優化
大多數索引（Unique Key、Index、Prefix、Full Text）使用`B-trees`實現。
MySQL 5.7中引入的Spatial Data Types（地理空間數據類型）使用`R-trees`；
MEMORY Tables（內存存儲引擎）還支持哈希索引；InnoDB使用倒序列表實現Full Text索引。

以`MySQL 8.0`為例，索引相關的詳細內容參考
[官方文檔第8.3節 Optimization and Indexes](https://dev.mysql.com/doc/refman/8.0/en/optimization-indexes.html)。

MySQL在以下操作中使用索引：

- 快速地查找匹配的數據行。
- 優化選擇索引，存在多個索引可供選擇時，
MySQL通常會使用查找行數最小的索引（the most selective index，最具選擇性的索引）。
- 若表格帶有組合索引（多列索引），任何索引的左側前綴可用於優化查找行。
例如已經存在一個三列的組合索引`(col1, col2, col3)`，
則列`(col1)`、`(col1, col2)`、`(col1, col2, col3)`等均建立了索引。
- 當執行join操作，從其它表中獲取行時，
MySQL能夠更有效地在列上使用索引當它們定義為相同的類型和大小時。

## 索引離散性
MySQL索引通常採用B樹實現，使用索引的字段需要內容具備足夠的離散性，
索引離散性不足會在B樹中會出現大量值相同的節點，導致下列問題：

1. 索引效率降低

	大大增加從B樹的找到目標位置需要的時間。

1. 查詢優化器選擇不當

	查詢優化器可能錯誤得選擇索引導致查詢性能下降，實際離散性過低的數據全表掃描的性能可能高於使用索引。

1. 更新與插入性能下降

	索引中的大量相同元素導致更新插入操作在維護索引結構時需要移動大量數據。

## 翻頁查詢優化
傳統分頁查詢通常使用`LIMIT 偏移量,數目`，在MySQL中的實現是全表掃描，讀取前`偏移量 + 數目`的數據，
丟棄偏移量之前的數據發送給客戶端，該實現會導致查詢速度隨著翻頁位置下降，翻頁越靠後的數據查詢耗時越長。

對於逐頁翻頁的情況，若表中存在自增主鍵，直接根據主鍵過濾指定數目效率會顯著提升：

```sql
# 向後翻頁
SELECT * FROM id > 上一頁末條數據主鍵 LIMIT 頁面大小;
# 向前翻頁
SELECT * FROM id < 後一頁首條數據主鍵 ORDER BY id DESC LIMIT 頁面大小;
# 向前翻頁，使用子查詢恢復輸出順序
SELECT * FROM (SELECT * FROM id < 後一頁首條數據主鍵 ORDER BY id DESC LIMIT 頁面大小) AS temp_result ORDER BY id;
```

MySQL會根據主鍵索引直接定位到數據位置，不再全表掃描。



# Row Formats（行格式）
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

當使用`ROW_FORMAT = DYNAMIC`創建表時，
InnoDB可以完全在頁外存儲長的變長列值（VARCHAR，VARBINARY，BLOB和TEXT），
聚集索引記錄只包含20字節的指針指向溢出頁面。大於或等於768字節定長字段被編碼為變長字段。

列是否存儲在頁外是否取決於頁面大小和行的總大小。
當行太長時，選擇最長的列進行頁外存儲，直到聚簇索引記錄適合B-tree頁面。
小於或等於40字節的TEXT和BLOB列會存儲在行中。

DYNAMIC行格式保持在索引節點中存儲整行的效率（類似COMPACT和REDUNDANT），
但避免了用長列的大量數據内容填充B-tree節點的問題。
DYNAMIC行格式基於以下思想：
若一個大的數據值一部分存儲在頁外，則通常最有效的存儲方式是將整個值存儲在頁外。
使用DYNAMIC格式時，較短的列可能會保留在B樹節點中，從而最大限度地減少一行所需的溢出頁數。



# FEDERATED 存儲引擎
`FEDERATED`存儲引擎允許用戶訪問其它MySQL實例中的表，而不需要使用複製、集群等技術。
查詢本地的FEDERATED表會從實際遠端的表中拉取數據。

相關完整內容可參考[官方文檔](https://dev.mysql.com/doc/refman/en/federated-storage-engine.html)。

## 啟用FEDERATED引擎
默認配置下，FEDERATED存儲引擎未被開啟，需要在MySQL配置中啟用：

```conf
# my.cnf / my.ini
[mysqld]
federated
```

或者在啟動MySQL實例時添加`--federated`參數。

## 創建FEDERATED表
創建FEDERATED表的步驟與創建普通表類似，使用CREATE TBALE語句進行創建；
FEDERATED表的結構需要與引用的實際表格完全一致，僅在存儲引擎部分需要設定為`FEDERATED`，
並且需要額外附加`CONNECTION`信息，用於指定遠程表所處的MySQL實例信息：

```sql
CREATE TABLE federated_table (
	... # same as remote table
)
ENGINE=FEDERATED
CONNECTION='mysql://fed_user@remote_host:9306/federated/test_table'
...
```

其中CONNECTION字段的語法規則如下：

```url
scheme://user_name[:password]@host_name[:port_num]/db_name/tbl_name
```

- `scheme` 數據庫協議，對於MySQL數據庫，僅支持`mysql`協議
- `user_name` 遠程數據庫實例的用戶名
- `password`（可選） 遠程數據庫實例用戶對應的密碼
- `host_name` 遠程數據庫實例的主機地址
- `port_num`（可選） 遠程數據庫實例監聽的端口號
- `db_name` 遠程表所處的遠程數據庫名稱
- `tbl_name` 遠程表的表名，本地表與關聯的遠程表表名稱不需要一致



# Data-at-Rest Encryption（靜態加密）
`MySQL 5.7`開始支持InnoDB存儲引擎的靜態加密，
詳細說明可參考[官方文檔](https://dev.mysql.com/doc/refman/en/innodb-data-encryption.html#innodb-schema-tablespace-encryption-default)。

InnoDB使用兩層加密架構，包括**主加密密鑰（master encryption key）**和**表空間密鑰（tablespace keys）**。
當一個表空間被加密，表空間密鑰被加密存儲在**表空間頭(tablespace header)**中。
當應用或認證的用戶訪問加密數據時，InnoDB使用主加密密鑰解密表空間密鑰。
解密後的表空間密鑰不會改變，但主加密密鑰可按需求更改，更改操作被稱為**主密鑰輪換（master key rotation）**。

MySQL的靜態加密特性依賴與密鑰插件（keyring plugin）進行主密鑰加密管理。

所有版本的MySQL均提供了`keyring_file`插件，將密鑰數據存儲在服務端的本地文件中。
企業版的MySQL額外提供了`keyring_encrypted_file`、`keyring_okv`、`keyring_aws`等插件。

數據靜態加密特性支持AES（Advanced Encryption Standard）加密算法。

## 啟用keyring_file插件
`keyring_file`插件默認已被包含在MySQL中，但默認不啟用，
在MySQL配置的`[mysqld]`配置段中添加下列配置：

```ini
[mysqld]
early-plugin-load = keyring_file.so # 設定加載keyring_file插件
keyring_file_data = /var/lib/mysql-keyring/keyring # Debian係發行版key默認存放該位置，可替換為其它路徑
```

配置需要重啟MySQL服務生效。重啟服務後，查詢插件的啟用狀態：

```sql
mysql> SELECT PLUGIN_NAME, PLUGIN_STATUS, PLUGIN_LIBRARY FROM INFORMATION_SCHEMA.PLUGINS WHERE PLUGIN_NAME LIKE 'keyring%';
+--------------+---------------+-----------------+
| PLUGIN_NAME  | PLUGIN_STATUS | PLUGIN_LIBRARY  |
+--------------+---------------+-----------------+
| keyring_file | ACTIVE        | keyring_file.so |
+--------------+---------------+-----------------+
1 row in set (0.00 sec)
```

keyring_file的PLUGIN_STATUS為ACTIVE則代表插件已成功啟用。

關於keyring_file插件更詳細的說明參考[官方文檔](https://dev.mysql.com/doc/refman/en/keyring-file-plugin.html)

## 啟用/禁用表格加密
在創建表格時，添加`ENCRYPTION = 'Y'`參數即可開啟加密支持：

```sql
-- 創建加密表格
mysql> CREATE TABLE Test.test (c1 INT) ENCRYPTION = 'Y';
Query OK, 0 rows affected (0.03 sec)

-- 查詢表格的加密狀態
mysql> SELECT TABLE_SCHEMA, TABLE_NAME, CREATE_OPTIONS FROM INFORMATION_SCHEMA.TABLES WHERE CREATE_OPTIONS LIKE '%ENCRYPTION%';
+--------------+------------+----------------+
| TABLE_SCHEMA | TABLE_NAME | CREATE_OPTIONS |
+--------------+------------+----------------+
| Test         | test       | ENCRYPTION="Y" |
+--------------+------------+----------------+
1 row in set (0.01 sec)
```

修改已存在表格的加密狀態：

```sql
-- 啟用表格加密
mysql> ALTER TABLE Test.test ENCRYPTION = 'Y';
Query OK, 0 rows affected (0.02 sec)
Records: 0  Duplicates: 0  Warnings: 0

-- 禁用表格加密
mysql> ALTER TABLE Test.test ENCRYPTION = 'N';
Query OK, 0 rows affected (0.03 sec)
Records: 0  Duplicates: 0  Warnings: 0
```

`MySQL 5.7`僅支持單表加密（file-per-table tablespaces），
`MySQL 8.0`中引入了數據庫加密，全局加密等機制。

## Master Key Rotation（主密鑰輪換）
當懷疑主加密密鑰被洩露時，密鑰應該被定期輪換，執行操作：

```sql
mysql> ALTER INSTANCE ROTATE INNODB MASTER KEY;
Query OK, 0 rows affected (0.01 sec)
```

主加密密鑰輪換是原子性（atomic）、實例級（instance-level）的操作。
每次主密鑰輪換，所有表空間密鑰會重新生成，並保存到對應的表空間頭中。



# MySQL高可用
MySQL提供了多種高可用方案，包括Galera Cluster、Replication、Group Replication等。

## Replication（複製）
[Replication](https://dev.mysql.com/doc/refman/en/replication.html)是MySQL中傳統的數據同步機制。
相關配置項參見[官方文檔](https://dev.mysql.com/doc/refman/en/replication-options-binary-log.html)。

MySQL中的複製基於binlog機制（默認已開啟，除非顯式使用skip_log_bin關閉），
需要為每個源設置唯一的server ID，配置項：

```ini
[mysqld]
...
server_id = 1 # 每個MySQL實例需要不同的ID
log-bin = /var/log/mysql/mysql-bin.log # 自定義binlog基礎名稱，可以為路徑
...
```

MySQL默認會啟用`log_slave_updates`（MySQL 8.0.26後改為`log_replica_updates`），
該配置用於控制replica server收到的更新是否應該寫入自身的binlog。

根據業務需求配置需要同步的數據庫/表：

```ini
[mysqld]
# Master設置哪些數據庫寫入binlog
binlog-do-db = ...
binlog-ignore-db = ...

# Slave設置接收哪些binlog數據
replicate-do-db = ...
replicate-do-table = ...
replicate-ignore-db = ...
replicate-ignore-table = ...
```

注意binlog-do-db/replicate-do-db等參數每行僅能添加單個數據庫/表名稱，
配置多個數據庫/表需要多行寫入配置。

之後在作為備份的數據庫（Slave）中設置複製來源（Master），並將本機啟動為slave：

```sql
-- 備機配置數據的複製目標
-- 用於傳輸數據的帳號需要具有 REPLICATION SLAVE 權限
mysql> change master to master_host='x.x.x.x', master_user='user', master_password='password';

-- 將本機啟動為slave
mysql> start slave;

-- 查看slave狀態
-- 直接使用 show master status; 會以表格輸出結果，但不便於觀看
mysql> show slave status\G
*************************** 1. row ***************************
               Slave_IO_State: Waiting for master to send event
                  Master_Host: x.x.x.x
                  Master_User: user
                  Master_Port: 3306
                Connect_Retry: 60
              Master_Log_File: mysql-bin.000007
          Read_Master_Log_Pos: 1226609
               Relay_Log_File: tsc1-relay-bin.000019
                Relay_Log_Pos: 21531
        Relay_Master_Log_File: mysql-bin.000007
             Slave_IO_Running: Yes
            Slave_SQL_Running: Yes
              Replicate_Do_DB: aaa,bbb,ccc
          Replicate_Ignore_DB:
           Replicate_Do_Table:
       Replicate_Ignore_Table:
      Replicate_Wild_Do_Table:
  Replicate_Wild_Ignore_Table:
                   Last_Errno: 0
                   Last_Error:
                 Skip_Counter: 0
          Exec_Master_Log_Pos: 1226609
              Relay_Log_Space: 21903
              Until_Condition: None
               Until_Log_File:
                Until_Log_Pos: 0
           Master_SSL_Allowed: No
           Master_SSL_CA_File:
           Master_SSL_CA_Path:
              Master_SSL_Cert:
            Master_SSL_Cipher:
               Master_SSL_Key:
        Seconds_Behind_Master: 0
Master_SSL_Verify_Server_Cert: No
                Last_IO_Errno: 0
                Last_IO_Error:
               Last_SQL_Errno: 0
               Last_SQL_Error:
  Replicate_Ignore_Server_Ids:
             Master_Server_Id: 2
                  Master_UUID: 29084997-6989-11ec-8437-3868dd696de8
             Master_Info_File: /opt/mysql/master.info
                    SQL_Delay: 0
          SQL_Remaining_Delay: NULL
      Slave_SQL_Running_State: Slave has read all relay log; waiting for more updates
           Master_Retry_Count: 86400
                  Master_Bind:
      Last_IO_Error_Timestamp:
     Last_SQL_Error_Timestamp:
               Master_SSL_Crl:
           Master_SSL_Crlpath:
           Retrieved_Gtid_Set:
            Executed_Gtid_Set:
                Auto_Position: 0
         Replicate_Rewrite_DB:
                 Channel_Name:
           Master_TLS_Version:
1 row in set (0.01 sec)

-- 展示master狀態
mysql> show master status\G
*************************** 1. row ***************************
             File: mysql-bin.000010
         Position: 1262268
     Binlog_Do_DB: MDM_Common,MDM_AppStore,MDM_TerminalControl
 Binlog_Ignore_DB:
Executed_Gtid_Set:
1 row in set (0.00 sec)
```

master機器信息亦可配置在數據庫配置中：

```ini
[mysqld]
master-host = x.x.x.x
master-user = user
master-password = password
```

### 解決數據衝突
當MySQL出現binlog數據同步衝突時，使用`show slave status\G`查看同步狀態，
輸出內容中的`Slave_SQL_Running_State`、`Last_Error`等項目說明當前同步狀態，正常和異常的輸出示例：

```html
<!-- 正常同步 -->
Last_Errno: 0
Last_Error:
Slave_SQL_Running_State: Slave has read all relay log; waiting for more updates

<!-- 同步失敗 -->
Last_Errno: 1032
Last_Error: Could not execute Delete_rows event on table xxx; Can't find record in 'xxx', Error_code: 1032; handler error HA_ERR_KEY_NOT_FOUND; the event's master log mysql-bin.000011, end_log_pos 21792122
Slave_SQL_Running_State:
```

Last_Errno說明了同步的錯誤編號，常見的錯誤如`1062`（重複主鍵）、`1032`（刪除目標記錄不存在）。

刪除衝突的數據內容即可恢復同步狀態，亦可在MySQL配置中添加`slave-skip-errors`配置項，
用於忽略特定類型的錯誤：

```ini
[mysqld]
slave-skip-errors=1062,1032 # 跳過指定類型的錯誤
# slave-skip-errors=all # 忽略所有同步錯誤
```

對於常見的重複主鍵錯誤，可採用不同主鍵自增偏移量的方案。
示例，對於雙主的MySQL集群，兩台主機可分別加入配置：

```ini
# 主機1，主鍵按照1，3，5生成
[mysqld]
auto_increment_offset = 1
auto_increment_increment = 2

# 主機2，主鍵按照2，4，6生成
[mysqld]
auto_increment_offset = 2
auto_increment_increment = 2
```

通過主鍵自增偏移量僅能解決多Master節點寫入數據的主鍵衝突，
對於UNIQUE KEY等其它衝突，依舊需要使用額外的機制。

### Binlog位置錯誤
MySQL會定期清理Binlog文件，當數據庫服務器長時間未啟動，
則之前同步的Binlog文件可能在下次啟動服務時被清除。
當設置同步的Binlog文件不存在，則查看同步狀態時會得到下列錯誤：

```sql
mysql> show slave status\G
...
Last_IO_Errno: 1236
Last_IO_Error: Got fatal error 1236 from master when reading data from binary log: 'Could not find first log file name in binary log index file'
...
```

解決此問題需要查看對應Master主機當前的Binlog文件：

```sql
mysql> show master logs
+------------------+-----------+
| Log_name         | File_size |
+------------------+-----------+
| mysql-bin.000020 | 154       |
| mysql-bin.000021 | 154       |
| mysql-bin.000022 | 1320      |
| mysql-bin.000023 | 4062986   |
+------------------+-----------+
4 rows in set
Time: 0.008s
```

Binlog文件亦可在Master主機的`/var/log/mysql`路徑下查找到：

```html
<!-- 以Ubuntu系統下的MySQL默認配置為例 -->
$ ls -al /var/log/mysql/
total 132
drwxr-x---  2 mysql adm     4096 Feb 10 15:15 .
drwxrwxr-x 11 root  syslog  4096 Jan 28 06:25 ..
-rw-r-----  1 mysql adm    20985 Feb 10 15:25 error.log
-rw-r-----  1 mysql adm        0 Jan 27 06:25 error.log.1
-rw-r-----  1 mysql mysql    539 Feb 10 15:15 mysql-bin.000014
-rw-r-----  1 mysql mysql  87612 Feb 10 15:32 mysql-bin.000015
-rw-r-----  1 mysql mysql     64 Feb 10 15:15 mysql-bin.index
```

之後重新設置master_file：

```sql
mysql> change master to master_log_file='mysql-bin.000014', master_log_pos=1;
```



# 常用功能和配置
補充一些常用周邊功能說明。

## 導出數據
使用`mysqldump`工具可以導出數據庫的內容，基本操作指令如下：

```html
$ mysqldump -u"用戶名" -p"密碼" -A <!-- 導出所有數據庫 -->
$ mysqldump -u"用戶名" -p"密碼" 備份數據庫 <!-- 導出指定數據庫 -->
$ mysqldump -u"用戶名" -p"密碼" 備份數據庫 備份表 <!-- 導出指定數據庫中的指定表的內容 -->
```

默認情況下，mysqldump工具會將導出的數據以SQL語句的形式輸出到終端，可以使用重定向將導出的內容寫入文本中：

```html
$ mysqldump -u"用戶名" -p"密碼" -A > xxx.sql <!-- 導出的內容寫入 xxx.sql 文件中 -->
```

mysqldump支持根據條件導出指定的內容（使用`-w`參數）：

```
$ mysqldump -u"用戶名" -p"密碼" -w"限制條件" 數據庫名 表名
```

導出內容時支持設定只導出數據（`-t`）或只導出表結構（`-d`）。
導出指定數據庫時，默認不會生成`USE xxx_db`語句，若需要生成該語句，則使用`-B`參數。

## 導入數據
導入數據需要在數據庫命令行中使用`source`指令：

```
mysql> source 數據庫備份文件
```

導入數據庫時需要注意編碼問題，數據庫編碼、連接編碼、備份文件的編碼需要相同纔不會產生中文亂碼問題。

亦可直接使用命令行重定向進行數據導入：

```
$ mysql -u用戶 -p密碼 < xxx.sql
```

## 設置中文編碼
默認情況下，舊版的mysql數據庫的編碼爲`latin1`，
此編碼不支持東亞語系的文字顯示，需要修改爲支持各國文字的`UTF-8`編碼。
對於部分使用`MariaDB`的發行版（如`ArchLinux`），默認的編碼爲`UTF-8`，無需額外配置。

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

- `character_set_client`、`character_set_connection`
可以通過配置文件中的`[client]`段進行修改。
- `character_set_database`、`character_set_results`、`character_set_server`
可以通過修改配置文件中的`[server]`段進行修改。

需要注意的是，每個數據庫可以擁有不同的編碼信息，查看指定數據庫的編碼：

```
mysql> use 數據庫名稱;
mysql> show variables like 'character_set_database';
```

修改指定數據庫的編碼：

```
mysql> alter database 數據庫名稱 CHARACTER SET 編碼類型;
```

如果需要修改數據庫的默認編碼，則需要修改配置文件：

- 在Debian系中，配置文件爲`/etc/mysql/mariadb.conf.d/client.cnf`。
- 在RedHat系中，配置文件爲`/etc/my.cnf`。
- 在ArchLinux中，配置文件爲`/etc/mysql/my.cnf`。

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
如果需要向數據庫中存儲二進制信息（比如**圖片**），則字段應選擇`BLOB`類型（`binary large object`）。

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
	timestamp.getTime() / 1000; // 獲取與MySQL中等價的Unix時間戳
	```

- C#中的`System.DateTime`類型：

	將在C#中獲得的`DateTime`實例與表示`1970-1-1`至今的時間相減，得到`System.TimeSpan`類型表示的時間間隔，
	訪問`TimeSpan.TotalSeconds`屬性獲得Unix時間戳。
	如下所示：

	```cs
	(dateTime - DateTime.Parse("1970-1-1")).TotalSeconds; // 獲取時間戳
	```

## 禁用 DNS 解析
MySQL默認開啓了DNS解析，但在DNS服務器異常時，一次數據庫操作會異常緩慢，
並在`/var/log/mysql/error.log`中寫入類似日誌：

```
[Warning] IP address 'xxx.xxx.xxx.xxx' could not be resolved: Temporary failure in name resolution
```

解決方法是禁用MySQL的DNS解析，在配置`my.cnf`中添加以下內容：

```ini
[mysqld]
skip-host-cache
skip-name-resolve
```



# 查看數據庫狀態
`information_schema`庫中存儲了MySQL數據庫的元數據。
通過使用SQL語句對庫中的各類表格進行查詢操作，可獲取MySQL中的各類狀態信息，
如數據庫/表的名稱、列的數據類型、訪問權限等。

常用表格的功能：

| 表名 | 功能 |
| :- | :- |
| PROCESSLIST | 正在執行的綫程信息 |
| TABLES | 表格信息 |
| COLUMNS | 表格列信息 |
| SCHEMA_PRIVILEGES | 數據庫權限信息(自mysql.db表獲取) |
| USER_PRIVILEGES | 用戶權限信息(自mysql.user表獲取) |



# 性能測試
MySQL内置了`mysqlslap`工具可用於性能測試，`sysbench`亦提供了mysql數據庫的性能測試功能。

## mysqlslap
mysqlslap基本用法：

```
$ mysqlslap -h 主機地址 -u用戶 -p密碼 --iterations=測試輪數 --concurrency=客戶端數目 --number-of-queries=操作數目 --auto-generate-sql-load-type=測試類型 ...
```

mysqlslap工具的連接認證相關參數與mysql客戶端工具相同，其它常用參數說明：

| 參數 | 說明 |
| :- | :- |
| --iterations | 測試輪數 |
| --concurrency | 客戶端數目，設置多個客戶端時，mysqlslap會啟用多線程並行操作 |
| --number-of-queries | 單次測試的操作數目 |
| --auto-generate-sql-load-type | 測試類型，取值read/write等 |

自動生成SQL寫入測試操作示例：

```
$ mysqlslap -h 主機地址 -u用戶 -p密碼 --auto-generate-sql --number-int-cols=數值列數 --number-char-cols=文本列數 --auto-generate-sql-load-type=write
```

## 寫入性能相關優化參數
寫入性能優化參考[MySQL官方文檔 Optimizing InnoDB Disk I/O](https://dev.mysql.com/doc/refman/8.0/en/optimizing-innodb-diskio.html)，
主要分為幾大部分：

- [`Redo Log`](`https://dev.mysql.com/doc/refman/en/innodb-redo-log.html`)

	Redolog記錄數據庫的事務日誌，用於數據崩潰恢復，以及糾正未完成事務的數據寫入。

	相關參數：

	`innodb_flush_log_at_trx_commit` 設置日誌如何同步到磁盤

	- 默認取值`1`，在每次事務均同步磁盤，高頻讀寫下會產生大量同步操作
	- 取值為`0`，每秒集中同步事務到磁盤，能顯著提升IO性能

- [`Binlog`](https://dev.mysql.com/doc/refman/en/binary-log.html)

	Binlog記錄數據庫的所有變更記錄，用於數據恢復和主從節點數據複製；
	對於單實例、數據可靠性要求不高的場景下可通過關閉Binlog提升寫入性能。

	相關參數：

	- `disable_log_bin/skip-log-bin` 無取值，使用該參數則關閉Binlog機制
	- `sync_binlog` 設置寫入Binlog的頻率
		- 默認取值為`1`，每次寫入操作都同步到Binlog
		- 取值為`0`關閉Binlog寫入
		- 取值大於1則**指定次數**操作後寫入Binlog

需要注意，通過上述參數提升IO性能同時也會損失部分數據安全性。



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
- `port`參數用於顯式指定連接端口，`unix_socket`參數爲socket連接類型，
`clientflag`爲mysql運行ODBC的標記，一般本地連接這三個參數全填`NULL`。

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

- `mysql_store_result()`和`mysql_use_result()`用於獲取查詢語句之後的結果集內容，
二者的區別是前者會將結果集拷貝到本地，開銷大，後者直接讀取服務器中的數據，每次只拷貝一行，開銷小，
但是後者需要在下一次SQL語句執行之前將結果集中的數據全部讀出，但前者就不需要。
- `mysql_field_count()`用於獲取最近查詢的列數。
- `mysql_num_fields()`用於獲取指定查詢結果的列數。
- `mysql_fetch_row()`用於按行讀取結果集中的內容，
每次執行`mysql_fetch_row()`會返回下一行結果集的指針。
返回值類型`MYSQL_ROW`的實際類型爲二維指針`char**`，保存了每一列的字符數組指針。
- `mysql_data_seek()`用於設置結果集讀取位置到指定的偏移量，
`offset`參數取值爲`0`時，則重置結果集的讀取位置。

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
- 立即訪問執行`mysql_close()`之後的MYSQL指針會報錯（野指針），
如果在關閉連接之後需要重新啓用連接，需要重新執行初始化操作`mysql_init()`。



# 問題註記
記錄MySQL在使用、配置中遇到的問題。

## MySQL error: sql_mode=only_full_group_by
`MySQL 5.7.5`開始默認啟用`only_full_group_by`特性，
select的列需要包含在group by子句中，否則會出現類似的錯誤信息：

```
Expression #6 of SELECT list is not in GROUP BY clause and contains nonaggregated column 'Xxx.xxx' which is not functionally dependent on columns in GROUP BY clause; this is incompatible with sql_mode=only_full_group_by
```

詳細可參考[MySQL官方文檔](https://dev.mysql.com/doc/refman/5.7/en/group-by-handling.html)中對應章節。

以`MySQL 8.0.15`為例，在Shell中查看當前的sqlmode：

```
mysql> select @@sql_mode;
+-----------------------------------------------------------------------------------------------------------------------+
| @@sql_mode                                                                                                            |
+-----------------------------------------------------------------------------------------------------------------------+
| ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION |
+-----------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)
```

可以看到，輸出的模式信息中包含`ONLY_FULL_GROUP_BY`，說明啟用了only_full_group_by特性。
關閉該模式：

```
mysql> SET GLOBAL sql_mode=(SELECT REPLACE(@@sql_mode,'ONLY_FULL_GROUP_BY',''));
Query OK, 0 rows affected (0.00 sec)
```

從MySQL Shell中修改該配置在下次數據庫重啟後會恢復，要永久關閉該特性需要修改MySQL配置，
編輯配置文件（Unix環境下通常為`/etc/my.cnf`或`/etc/mysql/my.cnf`），
修改`[mysqld]`配置段的`sql_mode`配置項（該配置項不存在時應手動創建），
填寫當前啟用的sql_mode中除ONLY_FULL_GROUP_BY之外的其它項：

```
[mysqld]
sql_mode=STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION
```

## Error Code: 1175. You are using safe update mode and you tried to update a table without a WHERE that uses a KEY column To disable safe mode, toggle the option in Preferences -> SQL Queries and reconnect.
若MySQL的會話中開啓了`SAFE MODE`，則可在會話中手動設置`SQL_SAFE_UPDATES`屬性關閉該模式：

```sql
> SET SQL_SAFE_UPDATES = 0;
```

添加global關鍵字全局關閉安全模式（通常不推薦）。

若需要恢復安全模式，則可將該屬性置為1：

```sql
> SET SQL_SAFE_UPDATES = 1;
```

## [42000][1071] Specified key was too long; max key length is 3072 bytes
MySQL對索引字段的長度有限制，使用VARCHAR類型作為索引時，需要注意不要讓索引字段限制長度。
參考[StackOverflow](https://stackoverflow.com/questions/8746207/1071-specified-key-was-too-long-max-key-length-is-1000-bytes)上相關問答。

## [ERROR] [MY-010123] [Server] Fatal error: Please read "Security" section of the manual to find out how to run mysqld as root!
Unix環境下，root用戶直接使用`mysqld`指令直接手動啟動時會出現該錯誤，
參考[StackOverflow](https://stackoverflow.com/questions/25700971/fatal-error-please-read-security-section-of-the-manual-to-find-out-how-to-run)。

解決方法是啟動時添加`--user=root`參數：

```
# mysqld --user=root
```

### ERROR 1396 (HY000): Operation CREATE USER failed for 'root'@'xxx'
https://stackoverflow.com/questions/5555328/error-1396-hy000-operation-create-user-failed-for-jacklocalhost

### MySQL reset auto_increment value in Innodb after server restart
https://dba.stackexchange.com/questions/16602/prevent-reset-of-auto-increment-id-in-innodb-database-after-server-restart

### mysqld: Can't create directory 'xxx' (Errcode: 13 - Permission denied)
問題說明：<br>
在Ubuntu Server系統下，修改MySQL Data Dir，已正確創建了數據目錄，
並已修改用戶/用戶組為mysql，使用`mysqld --initialize`初始化數據庫時，出現該錯誤。

解決方案：<br>
Ubuntu Server默認啟用了[AppArmor](https://apparmor.net/)，
該服務提供了更嚴格的目錄權限控制，導致mysqld初始化失敗。

解決該初始化問題可直接關閉AppArmor服務，或修改MySQL對應的AppArmor服務配置文件：

```
/etc/apparmor.d/usr.sbin.mysqld
```

在該文件中修改對應部分：

```sh
...
# Allow data dir access
  /var/lib/mysql/ r,
  /var/lib/mysql/** rwk,
...
```

在該部分配置中加入自定義的數據路徑即可，修改其它路徑時類似。
