<!-- TOC -->

- [Ansible Config](#ansible-config)
- [Ansible Inventory](#ansible-inventory)
- [Ansible Module](#ansible-module)
	- [模塊分發](#模塊分發)
	- [Command && Shell](#command--shell)
	- [Ansible Console](#ansible-console)

<!-- /TOC -->



# Ansible Config
Ansible會按照順序查找配置：

1. ANSIBLE_CONFIG （環境變量）
1. ansible.cfg （當前路徑下）
1. ~/.ansible.cfg （HOME目錄下）
1. /etc/ansible/ansible.cfg

在Unix環境下，全局配置為`/etc/ansible/ansible.cfg`，優先級最低。
使用系統包管理器安裝的Ansible通常會自動創建該文件，使用pip安裝的Ansible則不會。

使用`ansible-config`指令展示當前環境配置：

```html
$ ansible-config dump <!-- 輸出整個配置清單 -->
$ ansible-config dump --only-changed <!-- 僅列出相比默認配置變化的部分 -->
```



# Ansible Inventory
Ansible中記錄主機信息的配置被稱為[`Inventory (清單)`](https://docs.ansible.com/ansible/latest/user_guide/intro_inventory.html)，默認配置路徑為`/etc/ansible/hosts`，
通過發行版包管理器安裝的Ansible通常會自動生成該文件，但通過pip安裝的Ansible不會生成該文件，
需要手動創建該配置。

Inventory配置路徑可通過配置`ansible.cfg`進行修改：

```ini
[defaults]
inventory = xxx/hosts ;自定義hosts路徑 (行尾注視不要使用 # 語法，否則會造成解析出錯)
```

根據使用插件的不同，hosts文件支持INI或是YAML語法其中之一(通常默認為YAML)，
YAML語法的配置示例：

```yaml
all:
  hosts:
    xxx-hostname:
      ansible_host: xxx.xxx.xxx.xxx
      ansible_user: xxx
      # 更多連結參數，參考文檔 https://docs.ansible.com/ansible/latest/user_guide/intro_inventory.html#behavioral-parameters
  children:
    xxx-group1: # 定義組
      hosts:
        xxx-hostname1: # host參數同上
        xxx-hostname2:
      children:
        ... # 組內可以添加其它的組
    xxx-group2:
      hosts:
        xxx-hostname3:
        xxx-hostname4:
        xxx-hostname5:
      vars:
        ansible_user: xxx
        # 可添加更多參數，參數對整個組生效
```

Ansible使用SSH連接目標服務器進行操作，當首次連接新服務器時，會像普通SSH操作一樣輸出如下提示：

```
The authenticity of host 'xxx.xxx.xxx.xxx (xxx.xxx.xxx.xxx)' can't be established.
RSA key fingerprint is xx:yy:zz:....
Are you sure you want to continue connecting (yes/no)?
```

可在ansible.cfg中添加配置禁用主機key檢查：

```ini
[defaults]
host_key_checking = False
```



# Ansible Module
[`Moudules (模塊)`](https://docs.ansible.com/ansible/latest/user_guide/modules_intro.html)是一組分離的代碼單元，
可被用在命令行以及Playbook任務中。Ansible在每個遠程受控節點執行模塊中的代碼，並收集返回值。

在命令行中執行模塊：

```
$ ansible 主機組/主機 -m 模塊名稱 -a "模塊參數"
```

多數模塊使用`key=value`風格的參數(多組鍵值對使用**空格**分隔)，
部分模塊沒有參數，Command/Shell模塊則直接接收指令內容作為參數。
示例：

```html
$ ansible all -m ping <!-- 無參數 -->
$ ansible all -m command -a "ps -a" <!-- 普通文本參數 -->
$ ansible all -m service -a "name=httpd state=started" <!-- key=value 風格參數 -->
```

在Playbook中使用模塊語法風格類似：

```yaml
# 文本參數風格
- name: xxx
  模塊名稱: args ...

# key=value 參數風格
- name: xxx
  模塊名稱:
    key1: value1
    key2: value2
    ...
```

示例：

```yaml
# 使用 Command 模塊
- name: print the process info
  command: ps -a

# 使用 Service 模塊
- name: start the httpd service
  service:
    name: httpd
    state: started
```

## 模塊分發
Ansible中的模塊分為三類，分別有各自的分發平台和維護者。

| Collection | Code location | Maintained by |
| :- | :- | :- |
| ansible.builtin | [GitHub Repo](https://github.com/ansible/ansible/tree/devel/lib/ansible/modules) | core team |
| [Ansible Galaxy](https://galaxy.ansible.com) | various; follow repo link | community or partners |
| [Automation Hub](https://www.ansible.com/products/automation-hub) | various; follow repo link | content team or partners |

## Command && Shell
Command和Shell是Ansible中的常用模塊，用於在受控主機上執行指令，示例：

```
$ ansible all -m command -a "ps"
oracle-cloud | CHANGED | rc=0 >>
    PID TTY          TIME CMD
  32216 pts/0    00:00:00 fish
  32218 pts/0    00:00:00 sh
  32219 pts/0    00:00:00 python3
  32221 pts/0    00:00:00 ps

$ ansible all -m shell -a "ps"
oracle-cloud | CHANGED | rc=0 >>
    PID TTY          TIME CMD
  32171 pts/0    00:00:00 fish
  32173 pts/0    00:00:00 sh
  32174 pts/0    00:00:00 python3
  32176 pts/0    00:00:00 sh
  32177 pts/0    00:00:00 ps
```

二者基本功能類似，但Command模塊會將參數內容作為一條指令執行，
而Shell模塊會將參數內容作為腳本，開啟一個shell執行。
從前文的進程反饋信息中可知，Shell模塊額外啟動了一個sh進程用於執行指令。

區別示例：

```html
<!-- Command模塊將 ps; 語法解析為了指令名稱，導致執行錯誤 -->
$ ansible all -m command -a "ps; ps;"
oracle-cloud | FAILED | rc=2 >>
[Errno 2] No such file or directory: b'ps;'

<!-- Shell模塊能正確解析語法並返回結果 -->
$ ansible all -m shell -a "ps; ps;"
oracle-cloud | CHANGED | rc=0 >>
    PID TTY          TIME CMD
  32655 pts/0    00:00:00 fish
  32657 pts/0    00:00:00 sh
  32658 pts/0    00:00:00 python3
  32660 pts/0    00:00:00 sh
  32661 pts/0    00:00:00 ps
    PID TTY          TIME CMD
  32655 pts/0    00:00:00 fish
  32657 pts/0    00:00:00 sh
  32658 pts/0    00:00:00 python3
  32660 pts/0    00:00:00 sh
  32662 pts/0    00:00:00 ps
```

使用**重定向**等shell語法特性需要使用Shell模塊。

## Ansible Console
Ansible提供了`ansible-console`工具可進入交互式Shell便於同時、多次對一組機器執行相同指令：

```
$ ansible-console 主機組/主機
```

示例：

```
$ ansible-console 400m
[WARNING]: Invalid characters were found in group names but not replaced, use -vvvv to see details
Welcome to the ansible console. Type help or ? to list commands.

dainslef@400m (4)[f:5]$ uname -a
nmssuperf03 | CHANGED | rc=0 >>
Linux nmssuperf03 3.10.0-1062.el7.x86_64 #1 SMP Wed Aug 7 18:08:02 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
nmssuperf01 | CHANGED | rc=0 >>
Linux nmssuperf01 3.10.0-1062.el7.x86_64 #1 SMP Wed Aug 7 18:08:02 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
nmssuperf02 | CHANGED | rc=0 >>
Linux nmssuperf02 3.10.0-1062.el7.x86_64 #1 SMP Wed Aug 7 18:08:02 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
nmsinstall01 | CHANGED | rc=0 >>
Linux nmsinstall01 3.10.0-1062.el7.x86_64 #1 SMP Wed Aug 7 18:08:02 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
dainslef@400m (4)[f:5]$ uptime
nmsinstall01 | CHANGED | rc=0 >>
 16:18:36 up  6:17,  4 users,  load average: 0.01, 0.02, 0.09
nmssuperf02 | CHANGED | rc=0 >>
 16:19:31 up 15:48,  3 users,  load average: 7.21, 7.12, 7.46
nmssuperf01 | CHANGED | rc=0 >>
 16:19:31 up 15:48,  2 users,  load average: 8.73, 7.41, 7.01
nmssuperf03 | CHANGED | rc=0 >>
 16:19:31 up 15:48,  2 users,  load average: 5.30, 6.25, 6.37
```
