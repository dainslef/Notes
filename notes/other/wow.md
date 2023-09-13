<!-- TOC -->

- [MaNGOS](#mangos)
	- [MaNGOS服務說明](#mangos服務說明)

<!-- /TOC -->



# MaNGOS
[MaNGOS](https://www.getmangos.eu/)是歷史悠久開源的魔獸世界服務端，
後續從MaNGOS發展出了TrinityCore、AzerothCore等一系列分支。

## MaNGOS服務說明
MaNGOS服務分為兩部分：

- `realmd` 提供服務器登入、驗證等服務
- `mangosd` 提供遊戲主體服務

此外，還需要部署MySQL數據庫提供數據存儲。

不同版本的WOW需要不同版本的mangosd服務，但realmd服務可以共用。

MaNGOS的核心服務mangosd支持下列WOW版本：

| WOW版本 | MaNGOS代號 |
| :- | :- |
| Vanilla | ZERO |
| The Burning Crusade | ONE |
| Wrath of the Lich King | TWO |
| Cataclysm | THREE |

不同版本對應不同的倉庫地址，以ZERO版本爲例：

- 主服務倉庫：https://github.com/mangoszero/server.git
- 數據庫倉庫：https://github.com/mangoszero/database.git

其它版本類似，將倉庫地址中的代號切換為對應版本即可。
