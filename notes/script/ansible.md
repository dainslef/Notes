<!-- TOC -->

- [Ansible Config](#ansible-config)
- [Ansible Inventory](#ansible-inventory)

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
