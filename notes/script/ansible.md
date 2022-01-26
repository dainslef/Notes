<!-- TOC -->

- [Ansible Config](#ansible-config)
- [Ansible Inventory](#ansible-inventory)
- [Ansible Module](#ansible-module)

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
$ ansible 主機 -m 模塊名稱 -a "模塊參數"
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
