<!-- TOC -->

- [Haskell 開發環境](#haskell-開發環境)
	- [GHC 常用功能](#ghc-常用功能)
	- [REPL (GHCi)](#repl-ghci)
- [Debug (調試)](#debug-調試)
	- [Debug.Trace](#debugtrace)
	- [GHCi Debugger](#ghci-debugger)
- [常用函數](#常用函數)
	- [`$` 函數](#-函數)
	- [`.` 函數](#-函數)
- [Module (模塊)](#module-模塊)
	- [定義模塊](#定義模塊)
	- [導入內容](#導入內容)
	- [Re-Export](#re-export)
- [Collections (集合)](#collections-集合)
	- [List (列表)](#list-列表)
- [Printf (格式化)](#printf-格式化)
	- [轉換明細(conversion specification)](#轉換明細conversion-specification)
	- [格式化結果](#格式化結果)
	- [參數解析](#參數解析)
- [Currying (柯里化)](#currying-柯里化)
- [Fixity Declarations (操作符結合性、優先級定義)](#fixity-declarations-操作符結合性優先級定義)
- [Pointfree Style](#pointfree-style)
	- [概念解釋](#概念解釋)
	- [pointfree應用](#pointfree應用)
	- [pointfree變換技巧](#pointfree變換技巧)
	- [有趣的pointfree變換](#有趣的pointfree變換)
- [CPS (Continuation Passing Style)](#cps-continuation-passing-style)
- [求值策略](#求值策略)
	- [Lazy evaluation 的實現](#lazy-evaluation-的實現)
	- [Lazy evaluation 的優劣](#lazy-evaluation-的優劣)
	- [惰性求值與內存泄漏](#惰性求值與內存泄漏)
	- [強制求值](#強制求值)
	- [BangPatterns](#bangpatterns)
- [Type Class](#type-class)
	- [變長參數重載](#變長參數重載)
	- [使用TypeClass定義可無限遞歸的接口](#使用typeclass定義可無限遞歸的接口)
	- [Multi-parameter Type Classes](#multi-parameter-type-classes)
	- [Functional Dependencies](#functional-dependencies)
- [Exception](#exception)
	- [異常類型](#異常類型)
	- [異常 API](#異常-api)
	- [異常捕獲與求值策略](#異常捕獲與求值策略)
	- [異常安全](#異常安全)
	- [自定義異常](#自定義異常)
- [Monad](#monad)
	- [do 語法](#do-語法)
	- [ApplicativeDo](#applicativedo)
	- [Control.Monad](#controlmonad)
- [STM](#stm)
	- [STM 概念](#stm-概念)
	- [STM API 介紹](#stm-api-介紹)
	- [TVar](#tvar)
	- [TChan](#tchan)
- [GADTs](#gadts)
	- [ADT 的限制](#adt-的限制)
	- [使用 GADT](#使用-gadt)
- [Type Families](#type-families)
	- [Data Families](#data-families)
	- [Type Synonym Families](#type-synonym-families)
	- [Type Families Kind](#type-families-kind)
- [Concurrent](#concurrent)
	- [Async 包](#async-包)
- [RankNTypes](#rankntypes)
	- [RankNTypes 示例](#rankntypes-示例)

<!-- /TOC -->



# Haskell 開發環境
`Haskell`的主流編譯器是`GHC`，即`Glasgow Haskell Compiler`。

- **Linux/Unix**系統：

	使用發行版自帶的包管理器安裝`GHC`。

	`Debian`系發行版

	```
	# apt install ghc
	```

	`Arch`系發行版

	```
	# pacman -S ghc
	```

	`macOS`

	```
	$ brew install ghc
	```

- **Widnows**系統：

	在`https://www.haskell.org/platform/windows.html`下載`Haskell Platform`。
	`Haskell Platform`包含了`GHC`編譯器、`Cabal`構建工具等。

推薦使用`Stack`來配置`GHC`編譯器。

## GHC 常用功能
Haskell源碼後綴爲`*.hs`，使用`ghc`指令編譯Haskell代碼：

```
$ ghc xxx.hs
```

GHC編譯器會直接將Haskell源碼編譯爲對應平臺的二進制文件。

GHC還提供了`runhaskell`指令，可直接將Haskell源碼視作腳本運行：

```
$ runhaskell xxx.hs
```

## REPL (GHCi)
與Scala類似，GHC編譯器同樣提供了REPL環境，即GHCi。

使用`ghci`指令進入REPL，在REPL環境下直接輸入代碼可立即獲得反饋。如下所示：

```hs
$ ghci
Configuring GHCi with the following packages:
GHCi, version 8.0.2: http://www.haskell.org/ghc/  :? for help
Prelude> print "Hello World"
"Hello World"
Prelude> :quit
Leaving GHCi.
```

REPL環境下的內部指令均以`:`爲前綴，常用指令如下：

| 指令 | 功能 |
| :- | :- |
| :{\n ..lines.. \n:}\n | 多行指令/代碼 |
| :help, :? | 查看REPL指令幫助信息 |
| :quit | 退出GHCi環境 |
| :!\<command\> | 在外部Shell中執行指令 |
| :info[!] [\<name\> ...] | 顯示指定名稱的信息 |
| :type \<expr\> | 顯示給定表達式的Type |
| :kind[!] \<type\> | 顯示指定類型的Kind |
| :set -X\<extensions\> | 開啓指定語言擴展 |
| :unset -X\<extensions\> | 關閉指定語言擴展 |
| :show languages | 顯示已開啓的語言擴展 |
| :module [+/-] [*]<mod> ... | 導入/移除指定的模塊路徑 |



# Debug (調試)
在Haskell中，可以使用trace系列函數打印調試信息，或者在GHCi中進行斷點調試。
相關介紹參考[Haskell Wiki](https://wiki.haskell.org/Debugging)。

## Debug.Trace
`Debug.Trace`模塊下提供了trace系列函數，能夠將錯誤信息打印到輸出流(`*nix`下為`stderr`)中。

常用的trace函數：

```hs
trace :: String -> a -> a 	-- Defined in ‘Debug.Trace’
traceShow :: Show a => a -> b -> b 	-- Defined in ‘Debug.Trace’
traceShowId :: Show a => a -> a 	-- Defined in ‘Debug.Trace’
```

使用示例：

```hs
Prelude> import           Debug.Trace
Prelude Debug.Trace> let i = 1
Prelude Debug.Trace> 1 + trace ("Value i: " ++ show i) i
Value i: 1
2
Prelude Debug.Trace> 1 + traceShowId i
1
2
```

trace系列函數應該僅用於調試或監控執行狀況，該系列函數雖然帶有純函數的簽名(未標記為IO Monad)，
但函數的內部實現存在**side effects**(向外部輸出流中輸出trace信息)。

完整的Trace API可參考[Hackage文檔](https://hackage.haskell.org/package/base/docs/Debug-Trace.html)。

## GHCi Debugger
GHCi內置了調試器功能，可在Shell中加載指定源碼，並設置斷點進行調試。

假設存在源碼文件`~/Main.hs`：

```hs
main :: IO ()
main = do
  let (line1, line2, line3) = (1, 2, 3)
  print $ "Line 1 ..." ++ show line1
  print $ "Line 2 ..." ++ show line2
  print $ "Line 3 ..." ++ show line3
```

在GHCi Shell中加載源碼、添加斷點進行調試：

```hs
*Main> :load ~/Main.hs -- 載入模塊
[1 of 1] Compiling Main             ( /Users/dainslef/Main.hs, interpreted )
Ok, one module loaded.
*Main> :break 5 -- 設置斷點
Breakpoint 3 activated at /Users/dainslef/Main.hs:5:3-36
*Main> main -- 執行待調試的函數
"Line 1 ...1"
Stopped in Main.main, /Users/dainslef/Main.hs:5:3-36
_result :: IO () = _
line2 :: Integer = _
[/Users/dainslef/Main.hs:5:3-36] [/Users/dainslef/Main.hs:5:3-36] *Main> print line2 -- 打印該斷點環境下的變量
2
[/Users/dainslef/Main.hs:5:3-36] [/Users/dainslef/Main.hs:5:3-36] *Main> :step -- 繼續單步調試
"Stopped in Main.main, /Users/dainslef/Main.hs:5:11-36
_result :: [Char] = _
line2 :: Integer = 2
[/Users/dainslef/Main.hs:5:11-36] [/Users/dainslef/Main.hs:5:11-36] *Main> :continue -- 繼續執行函數到下一個斷點或或函數結束
Line 2 ...2"
"Line 3 ...3"
```

更多GHCi Debugger相關功能可參考[GHC官方手冊](https://downloads.haskell.org/ghc/latest/docs/html/users_guide/ghci.html#the-ghci-debugger)。



# 常用函數
Haskell中可以使用符號做爲函數名。

## `$` 函數
`$`常用於消除函數中的括號，函數定義：

```hs
($) ::
  forall (r :: GHC.Types.RuntimeRep) a (b :: TYPE r).
  (a -> b) -> a -> b
  	-- Defined in ‘GHC.Base’
infixr 0 $
```

`$`函數優先級爲0，低於幾乎所有的常見函數/操作符，使用`$`運算符將函數與之後的參數分隔開，
能代替括號操作符改變操作優先級。示例：

```hs
Prelude> print ("abc" ++ "cde") -- 使用括號改變表達式優先級，與傳統命令式語言類似
"abccde"
Prelude> print $ "abc" ++ "cde" -- 使用"$"函數改變優先級更符合Haskell代碼風格
"abccde"
```

## `.` 函數
`.`用於組合兩個函數，函數定義：

```hs
(.) :: (b -> c) -> (a -> b) -> a -> c 	-- Defined in ‘GHC.Base’
infixr 9 .
```

示例：

```hs
Prelude> print ("abc" ++ "cde" ++ "efg") -- 使用括號改變表達式優先級，與傳統命令式語言類似
"abccdeefg"
Prelude> print $ "abc" ++ "cde" ++ "efg" -- 使用"$"函數改變優先級更符合Haskell代碼風格
"abccdeefg"
Prelude> print . ("abc"++) . ("cde"++) $ "efg" -- 使用"."組合函數
```

`.`函數常用於`Pointfree`風格中，通過函數組合來代替多個連續的函數調用。



# Module (模塊)
`Module`是一組值、類型、類型別名、type class等的集合。
模塊中可以導入其它模塊的資源，也可以導出自身模塊的部分/全部內容。
關於模塊的更多介紹，可參考[GHC官網文檔](https://www.haskell.org/onlinereport/haskell2010/haskellch5.html)。

## 定義模塊
使用`module`關鍵字定義一個模塊，示例：

```hs
-- 模塊 Xxx 對應需要定義在 Xxx.hs 文件中
module Xxx where

xxxA = ...
xxxB = ...
...
```

與Java的包命名類似，Haskell中模塊的名稱需要和模塊所屬的源碼文件名稱相同，
例如，模塊`Xxx`對應的源碼文件為`Xxx.hs`；
模塊路徑需要與源碼目錄對應，例如模塊`Xxx1.Xxx2.Xxx`對應源碼路徑為`Xxx1/Xxx2/Xxx.hs`。

默認模塊導出時會導出當前模塊的所有內容，定義模塊時可指定需要導出的內容：

```hs
-- 僅導出 xxxA
module Xxx (xxxA) where

xxxA = ...
xxxB = ...
...
```

## 導入內容
使用`import`關鍵字從其它模塊導入內容，示例：

```hs
import Xxx1 -- 導入模塊 Xxx1 中的所有內容
import Xxx2 (xxxA, xxxB) -- 導入模塊 Xxx2 模塊中的部分內容(顯式指定需要導入的部分)
import Xxx3 hiding (xxxA, xxxB) -- 導入 Xxx3 模塊中的部分內容(僅排除不需要導入的部分)
import Xxx.Xxx.Xxx as X -- 導入模塊並為模塊定義別名
```

導入模塊後可以使用直接訪問模塊內容，或使用完整的模塊路徑來訪問模塊內容。

當多個模塊中出現名稱相同的內容時，未避免歧義，需要使用**限定導入**，示例：

```hs
import qualified Xxx1 -- 導入模塊 Xxx1，僅能使用完整模塊路徑訪問模塊內容
import qualified Xxx.Xxx.Xxx as X -- 限定導入，同時設置別名，僅能通過設定的別名進行訪問
```

限定導入的模塊僅能使用完整的模塊路徑進行訪問。

## Re-Export
導出模塊時，不僅可以導出本模塊的內容，亦可導出其它模塊的內容：

```hs
-- 導出本模塊的部分內容時，將 Xxx2 模塊的內容一併導出
module Xxx1 (module Xxx2, ...) where
...
```

其它模塊在導入本模塊時，同樣可以訪問本模塊重導出的其它模塊內容。



# Collections (集合)
與其它函數式語言類似，Haskell中提供了多種集合類型，包括最基礎的`[a]`(列表)，
以及`Data.Array`(數組)、`Data.Vector`(向量)、`Data.Sequence`(序列)。

## List (列表)
**列表**是Haskell的基礎數據結構，使用`[a]`表示。

列表在Haskell中的定義非常簡單：

```hs
Prelude> :info []
data [] a = [] | a : [a] 	-- Defined in ‘GHC.Types’
instance Applicative [] -- Defined in ‘GHC.Base’
instance Eq a => Eq [a] -- Defined in ‘GHC.Classes’
instance Functor [] -- Defined in ‘GHC.Base’
instance Monad [] -- Defined in ‘GHC.Base’
instance Monoid [a] -- Defined in ‘GHC.Base’
instance Ord a => Ord [a] -- Defined in ‘GHC.Classes’
instance Semigroup [a] -- Defined in ‘GHC.Base’
instance Show a => Show [a] -- Defined in ‘GHC.Show’
instance Read a => Read [a] -- Defined in ‘GHC.Read’
instance [safe] IsChar c => PrintfArg [c]
  -- Defined in ‘Text.Printf’
instance [safe] IsChar c => PrintfType [c]
  -- Defined in ‘Text.Printf’
instance Foldable [] -- Defined in ‘Data.Foldable’
instance Traversable [] -- Defined in ‘Data.Traversable’
```

Haskell中列表的實現為linked list，因此在數據量較大時與傳統語言中基於數組的數據結構相比，
查找性能與內存佔用均表現不佳，對性能有較高要求的場景應考慮使用`Data.Vector`。

Haskell中的列表支持函數式語言中常見的範圍操作符進行初始化：

```hs
Prelude> [1 .. 10]
[1,2,3,4,5,6,7,8,9,10]
Prelude> [1, 3 .. 10] -- 間隔輸出
[1,3,5,7,9]
Prelude> [10, 8 .. 0] -- 降序輸出
[10,8,6,4,2,0]
```

列表生成式(List comprehension)：

```hs
Prelude> [2 * i | i <- [1 .. 10]]
[2,4,6,8,10,12,14,16,18,20]
-- 可以使用多個列表
Prelude> [(x, y) | x <- [1, 2], y <- [3 .. 5]]
[(1,3),(1,4),(1,5),(2,3),(2,4),(2,5)]
-- 支持穿插普通語句
Prelude> [(x, y) | x <- [1, 2], let y = "[" ++ show x ++ "]"]
[(1,"[1]"),(2,"[2]")]
-- 允許使用Bool語句篩選需要生成的內容
Prelude> [(x, y) | x <- [1 .. 5], let y = "[" ++ show x ++ "]", mod x 2 == 0]
[(2,"[2]"),(4,"[4]")]
```

列表的增刪改查操作：

```hs
Prelude> l = [1, 2, 3, 4, 5]
Prelude> 0:l -- 添加元素，鏈表的添加元素在頭部
[0,1,2,3,4,5]
Prelude> [0, 0, 0] ++ l -- 拼接兩個鏈表
[0,0,0,1,2,3,4,5]
Prelude> l ++ [6] -- 利用拼接鏈表操作向尾部添加元素
[1,2,3,4,5,6]
Prelude> length l -- 獲取大小
5
Prelude> null l -- 判斷是否為空
False
Prelude> l !! 0 -- 按索引獲取對應位置的內容(注意鏈表的按索引訪問尾部元素的時間複雜度為O(n))
1
Prelude> filter (>2) l -- 按指定條件過濾
[3,4,5]
Prelude> reverse l -- 反轉列表
[5,4,3,2,1]
Prelude> init l -- 取出頭部元素
[1,2,3,4]
Prelude> tail l -- 取出尾部元素
[2,3,4,5]
Prelude> take 3 l -- 取其中部分指定元素
[1,2,3]
Prelude> splitAt 3 l -- 從指定位置開始切分列表
([1,2,3],[4,5])
```

列表類型實現了`Foldable`、`Monad`等一系列type class：

```hs
Prelude> any (>1) l -- 檢測是否存在任意成員滿足條件
True
Prelude> all (>1) l -- 檢測是否全部成員滿足條件
False
Prelude> sum l -- 求和
15
```



# Printf (格式化)
`Text.Printf`包提供了類似C語言`printf(3)`函數風格的文本格式化功能，支持幾乎所有的`printf(3)`格式化語法。

函數簽名：

```hs
printf :: Text.Printf.PrintfType r => String -> r
  	-- Defined in ‘Text.Printf’
```

函數接收的參數為格式化字符串，返回結果為格式化後的內容。

## 轉換明細(conversion specification)
轉換明細(格式化字符串)語法與C語言printf基本相同：

```hs
%[+/-][0/space][數值寬度.浮點部分寬度][格式化字符]
```

使用`%`開始格式化的轉換明細，之後是對齊方式(`+/-`，左右對齊)，填充內容(`0/space`)：

```
-      left adjust (default is right adjust)
+      always use a sign (+ or -) for signed conversions
space  leading space for positive numbers in signed conversions
0      pad with zeros rather than spaces
#      use an \"alternate form\": see below
```

轉換明細以一個表示格式的字符結尾：

```
c      character               Integral
d      decimal                 Integral
o      octal                   Integral
x      hexadecimal             Integral
X      hexadecimal             Integral
b      binary                  Integral
u      unsigned decimal        Integral
f      floating point          RealFloat
F      floating point          RealFloat
g      general format float    RealFloat
G      general format float    RealFloat
e      exponent format float   RealFloat
E      exponent format float   RealFloat
s      string                  String
v      default format          any type
```

實例：

```
%010.5f
```

說明：

寬度為10位的浮點數，小數點後保留5位，寬度不足的部分從左邊開始補零。

```hs
Prelude Text.Printf> printf "%010.5f\n" 1.0
0001.00000
```

## 格式化結果
返回內容的類型為`PrintfType`，該類型為type class，定義如下：

```hs
class Text.Printf.PrintfType t where
  Text.Printf.spr :: String -> [Text.Printf.UPrintf] -> t
  {-# MINIMAL spr #-}
  	-- Defined in ‘Text.Printf’
instance [safe] Text.Printf.IsChar c => Text.Printf.PrintfType [c]
  -- Defined in ‘Text.Printf’
instance [safe] (a ~ ()) => Text.Printf.PrintfType (IO a)
  -- Defined in ‘Text.Printf’
instance [safe] (Text.Printf.PrintfArg a,
                 Text.Printf.PrintfType r) =>
                Text.Printf.PrintfType (a -> r)
  -- Defined in ‘Text.Printf’
```

默認實現了該type class的類型包括`String`、`IO ()`等，分別對應不同的情形：

```hs
Prelude Text.Printf> printf "%010.5f\n" 1.0 :: IO () -- 直接輸出到終端
0001.00000
Prelude Text.Printf> printf "%010.5f\n" 1.0 :: String -- 輸出為String類型供其它函數使用
"0001.00000\n"
```

## 參數解析
`Text.Printf.printf`函數簽名僅接收一個轉換明細文本，用於告知函數格式化的目標樣式，
但實際該函數在格式化時根據不同格式還要接收不定數目的格式化參數：

```hs
Prelude Text.Printf> printf "%s, %d, %.4f\n" "hello" 123 pi
hello, 123, 3.1416
Prelude Text.Printf> printf "%d, %.4f\n" 123 pi
123, 3.1416
```

官方文檔中解釋是類型類PrintfType提供了變長參數魔法(variable argument magic)，
實現原理可參考[StackOverflow](https://stackoverflow.com/questions/7828072/how-does-haskell-printf-work)
以及[本文type class章節](#使用typeclass定義可無限遞歸的接口)的說明，
基本思路是在type class接口函數中返回自身，使之能夠遞歸調用type class中定義的接口方法。
該type class的實現在該模塊中不可見。

用於參與格式化的參數需要實現類型類`PrintfArg`，否則會得到編譯錯誤。



# Currying (柯里化)
`Currying`(柯里化)是一類函數的轉換過程，將通過元組接收多個參數的函數轉換爲接收單一參數並返回接收另一個參數的函數，
以此逐級遞推，通過不斷返回接收其它參數的函數來逐漸接收元組中的所有參數。

以簽名如下的函數爲例：

```hs
f :: (Int, Int, Int, Int) -> Int
```

函數`f`爲接收一個四元組作爲參數，進行柯里化：

```hs
c1 :: (Int, Int, Int) -> (Int -> Int) -- 從元組中分離出一個參數，返回接收該參數的函數
c2 :: (Int, Int) -> (Int -> (Int -> Int)) -- 再分離出一個參數，返回接收該參數的函數
... -- 重複該操作，直至元組中的參數被完全解構
cN :: Int -> (Int -> (Int -> (Int -> Int))) -- 最終結果
cN :: Int -> Int -> Int -> Int -> Int -- 依據Haskell中的操作符優先級，該簽名與上述簽名等價
```

`Data.Tuple`模塊中提供了`curry/uncurry`函數，用於將函數進行柯里化與逆柯里化：

```hs
curry :: ((a, b) -> c) -> a -> b -> c 	-- Defined in ‘Data.Tuple’
uncurry :: (a -> b -> c) -> (a, b) -> c 	-- Defined in ‘Data.Tuple’
```

示例：

```hs
Prelude> :{
Prelude| f :: (Int, Int) -> Int
Prelude| f (a, b) = a + b
Prelude| :}
Prelude> c = curry f -- 柯里化
Prelude> :type c
c :: Int -> Int -> Int
Prelude> f (1, 2) == c 1 2
True
Prelude> uc = uncurry c -- 逆柯里化
Prelude> :type uc
uc :: (Int, Int) -> Int
Prelude> c 1 2 == uc (1, 2)
True
```

在Haskell中，每個函數實際僅能接收一個參數，多參數函數應用單個參數後返回新函數，從而逐步應用多個參數。
示例：

```hs
Prelude> :{
Prelude| c :: Int -> Int -> Int -> Int -- 定義多參數函數，參數優先級"Int -> (Int -> (Int -> Int))"
Prelude| c x y z = x + y + z
Prelude| :}
Prelude> c 1 2 3
6
Prelude> ((c 1) 2) 3 -- 函數傳入多個參數實際是逐步應用單個參數
6
```

對於多參數函數，Haskell允許僅應用部分參數，應用部分參數後生成新的函數，稱爲`Partial Application`(部分應用函數)。
示例：

```hs
Prelude> :type c
c :: Int -> Int -> Int -> Int
Prelude> :type c 1
c 1 :: Int -> Int -> Int
Prelude> :type c 1 2
c 1 2 :: Int -> Int
Prelude> :type c 1 2 3
c 1 2 3 :: Int
```



# Fixity Declarations (操作符結合性、優先級定義)
在Haskell中，操作符的優先級可以自行顯式定義，語法示例：

```hs
infix/infixl/infixr [優先級數值] [操作符]
```

語法詳細說明：

| 關鍵字 | 說明 |
| :- | :- |
| infix | 定義操作符為**不可結合** |
| infixl | 定義操作符為**左結合性** |
| infixr | 定義操作符為**右結合性** |
| 優先級數值(可選) | 定義操作符優先級，範圍[0, 9]，操作符和函數默認的優先級為9(最高優先級) |
| op1, ... , opn | 操作符名稱(可多個並列) |

以標準庫中的`+`操作符為例：

```hs
Prelude> :info +
class Num a where
  (+) :: a -> a -> a
  ...
  	-- Defined in ‘GHC.Num’
infixl 6 +
```

其中`infixl 6 +`定義了`+`操作符的結合性為左結合，優先級為6。

示例：

```hs
Prelude> :{
Prelude| (...), (|||) :: IO Int -> IO Int -> IO Int
Prelude| n1 ... n2 = do
Prelude|   v1 <- n1
Prelude|   v2 <- n2
Prelude|   print $ "left: " ++ show v1 ++ " right: " ++ show v2
Prelude|   return $ v1 + v2
Prelude| (|||) = (...)
Prelude|
Prelude| -- 定義操作符結合性和優先級
Prelude| infixl 5 ...
Prelude| infixr 6 |||
Prelude| :}
Prelude> return 1 ... return 2 ... return 3 -- 操作符左結合
"left: 1 right: 2" -- 先執行 return 1 ... return 2
"left: 3 right: 3"
6
Prelude> return 1 ||| return 2 ||| return 3 -- 操作符右結合
"left: 2 right: 3" -- 先執行 return 2 ||| return 3
"left: 1 right: 5"
6
Prelude> return 1 ... return 2 ||| return 3 ||| return 4 --- 多種操作符結合
"left: 3 right: 4"
"left: 2 right: 7"
"left: 1 right: 9"
10
Prelude> :{
Prelude| infix 7 @@@ -- 定義操作符為不可結合
Prelude| (@@@) = (...)
Prelude| :}
Prelude> return 1 @@@ return 2 @@@ return 3 -- 連接不可結合的操作符會得到錯誤信息

<interactive>:28:1: error:
    Precedence parsing error
        cannot mix ‘@@@’ [infix 7] and ‘@@@’ [infix 7] in the same infix expression
Prelude> (return 1 @@@ return 2) @@@ return 3 -- 正確連接多個不可結合操作符需要使用括號
"number left: 1 number right: 2"
"number left: 3 number right: 3"
6
```



# Pointfree Style
在函數式編程中，通常使用函數之間相互組合來實現新函數，而非顯式地提及需要被應用的參數。

考慮如下函數：

```hs
f n = a (b (c n))
```

函數`f`的邏輯是將參數n按順序依次調用函數`c`、`b`、`a`，使用pointfree風格可以寫成：

```hs
f = a . b . c
```

pointfree的作用：

- 能更清晰地展示函數的調用邏輯
- 在某些邏輯中參數名稱難以找到合適的名稱描述，使用pointfree風格可避免爲參數命名

## 概念解釋
pointfree名稱源自數學領域中的**拓撲**(研究由點組成的空間以及空間之間的函數)，
對函數而言，pointfree是不顯式提及在函數作用空間的點
(does not explicitly the points of the space on which the function acts, 即參數)的一類函數。
在Haskell中，**空間**(space)是某些類型，**點**(points)是參數。

更詳細的概念解釋可參考[Haskell Wiki](https://wiki.haskell.org/Pointfree)。

## pointfree應用
pointfree風格不僅限於使用`.`組合函數，例如使用Partial application作爲函數實現：

```hs
Prelude> :{
Prelude| f :: Int -> Int
Prelude| f x = x + 1
Prelude| :}
Prelude> f 1
2

-- pointfree版本
Prelude> :{
Prelude| f :: Int -> Int
Prelude| f = (+1) -- 生成簽名同樣爲 Int -> Int 函數作爲實現
Prelude| :}
Prelude> f 1
2
```

函數實現與簽名中位置完全相同的參數可直接省略：

```hs
Prelude> :{
Prelude| f :: (Int -> Int) -> Int -> Int
Prelude| f f' x = f' x
Prelude| :}
Prelude> f (+1) 1
2

-- pointfree版本
Prelude> :{
Prelude| f :: (Int -> Int) -> Int -> Int
Prelude| f f' = f'
Prelude| :}
Prelude> f (+1) 1
2
```

在一些需要使用Lambda的場景下，同樣可以通過ETA Conversion和Partial application，直接傳遞函數，例如：

```hs
Prelude> filter (\x -> x > 5) [1 .. 10]
[6,7,8,9,10]

-- pointfree版本
Prelude> filter (>5) [1 .. 10]
[6,7,8,9,10]
```

## pointfree變換技巧
常用的pointfree變換技巧：

1. 使用`.`函數組合多個函數，`.`函數為右結合性，參數會優先執行`.`函數右側的函數

	```hs
	a (b (c n)) = a . b . c $ n
	```

1. 使用`.`函數組合單個函數改變函數簽名

	```hs
	f :: a -> b
	(.f) :: (b -> c) -> a -> c
	(f.) :: (a -> b) -> a -> c
	```

1. 靈活使用`flip`函數調換參數位置，使表達式的參數位置匹配簽名位置
1. 當表達式結果類型完全匹配函數簽名時則變形完成

以一個更複雜的函數作爲例子：

```hs
p x y z = f (g x y) z
```

逐步變換為pointfree形式：

```hs
p = \x -> \y -> \z -> f (g x y) z
  = \x -> \y -> f (g x y)
  = \x -> \y -> (f . (g x)) y
  = \x -> f . (g x)
  = \x -> ((.) f) (g x)
  = \x -> (((.) f) . g) x
  = ((.) f) . g
```

即函數`p x y z = f (g x y) z`的pointfree形式為：

```hs
p = ((.) f) . g
```

## 有趣的pointfree變換
[Haskell Wiki](https://wiki.haskell.org/Pointfree)中介紹了多種有趣的pointfree變換。

- `owl`

	```hs
	Prelude> :{
	Prelude| owl :: (a -> c -> d) -> a -> (b -> c) -> b -> d
	Prelude| owl = (.) (.)
	Prelude| :}

	-- 使用示例
	Prelude> owl (==) 1 (+1) 0
	True
	```

- `dot`

	```hs
	Prelude> :{
	Prelude| dot :: (c -> d) -> (a -> b -> c) -> a -> b -> d
	Prelude| dot = (.) . (.)
	Prelude| :}

	-- 使用示例
	Prelude> dot print (++) "Hello " " World"
	"Hello  World"
	```

使用pointfree風格需要**適可而止**，過度使用會造成代碼難以理解。



# CPS (Continuation Passing Style)
CPS(Continuation Passing Style，延續傳遞風格)是一種編程風格，函數不直接返回計算結果，
而是將計算結果傳遞到一個continuation(通常是回調)中，由continuation對結果進行操作。

關於CPS的詳細概念，可參考[WikiBooks](https://en.wikibooks.org/wiki/Haskell/Continuation_passing_style)中的介紹。





# 求值策略
Haskell默認採用`Lazy evaluation`(懶執行/惰性求值/非嚴格求值)，字段、函數參數在真正被使用前，不會被求值，
即一個表達式綁定到字段時並沒有立即，而是延遲到該表達式的結果被其它計算需要時再執行(進行求值)。

關於Lazy evaluation的詳細概念，可參考[Haskell Wiki](https://wiki.haskell.org/Lazy)中的描述。

示例：

```hs
main :: IO ()
main = do
  let f = 1 + error "Error Arg!"
  print "Before..."
  print $ "After: " ++ show f -- 打印結果，此時會對f字段進行求值
```

輸出結果：

```
"Before..."
Lazy: Error Arg!
CallStack (from HasCallStack):
  error, called at ... in main:Main
```

由輸出結果可知，異常並未在表達式創建時就觸發，而是真正使用字段時纔對表達式求值，從而觸發異常。

若一個字段自始自終沒有被計算結果依賴，則該字段不會被求值。
包含異常的代碼若沒有被真正求值，則異常不會觸發：

```hs
main :: IO ()
main = do
  let f = 1 + error "Error Arg!"
  print "Before..."
  let s = f - 1
  print $ "After..."
```

輸出結果：

```
"Before..."
"After..."
```

由結果可知，包含異常的表達式沒有被真正執行，程序正常退出。

## Lazy evaluation 的實現
在Haskell中，Lazy evaluation技術上是`Call by name`加上`Sharing`。
Call by name意味着在字段在需要時再被執行；
Sharing意味着被多次使用的臨時數據會被存儲，例如在如下表達式中：

```hs
let x = 1 + 1 in x * x
```

字段`x`在之後的表達式中被使用了兩次，但字段x不會被多次計算，而是在首次計算後被存儲並用於之後的使用。

Lazy evaluation也被稱爲`Call by need`，Call by need是Call by name的帶有記憶性的變體，
Call by need的字段在需要時被求值(Call by name)，字段綁定的表達式執行後結果會被存儲(Sharing)，
之後再次訪問該字段時，不會再重複執行計算。

在Haskell中，使用名爲`Thunk`的數據結構來存儲表達式，等到表達式在需要的時刻再執行。
Thunk包含一個布爾類型字段用於記錄包含的表達式是否已被計算過：

- 若表達式未被計算，則計算並存儲結果
- 若表達式已被計算，則直接獲取之前的結果，而非重複進行計算

## Lazy evaluation 的優劣
惰性求值的優勢：

- 程序僅在需要時進行求求值，避免了無意義的計算
- 能夠表示出一些無限大小的數據(如`[0..]`)，並進行操作

惰性求值的劣勢：

- 對於部分基礎數據類型，Haskell中全部使用thunk保存數據會有相比原始類型更大的內存開銷
- 一些不合理的操作會造成thunk堆積，引起內存泄漏(如`foldl`)
- 計算的執行時機不確定(取決於編譯器的實現)

## 惰性求值與內存泄漏
惰性求值的特性將計算推遲到了真正需要求值的時刻，Haskell中使用thunk存儲尚未計算的表達式。
對於某些遞歸計算邏輯而言，可能會造成大量的thunk堆積，進而導致內存泄漏。

以`foldl`函數爲例，常規遞歸實現版本：

```hs
foldl :: (b -> a -> b) -> b -> [a] -> b
foldl f z [] = z
foldl f z (n:l) = foldl f (f z n) l
```

對應計算邏輯展開爲：

```hs
foldl f z [x1, x2, ..., xn] = f (... (f (f z x1) x2) ...) xn
```

由於惰性求值的特性，遞歸中每一步的計算表達式`f z n`並未立即執行計算，而是以thunk的形式堆積，
當計算列表的長度較大時，函數遞歸展開會有巨大的內存開銷。
要避免thunk堆積，應對遞歸中的單步計算表達式進行強制求值，修改實現：

```hs
foldl' :: (b -> a -> b) -> b -> [a] -> b
foldl' f z [] = z
foldl' f z (n:l) = foldl' f (flip f n $! z) l -- 對傳入的上一步遞歸結果(參數z)進行強制求值，從而避免thunk堆積
```

由於foldl函數的實現是**尾遞歸**，在嚴格求值的求值策略下，可被編譯器優化成循環。

與foldl相對應，`foldr`函數的遞歸實現：

```hs
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f z [] = z
foldr f z (n:l) = f n $ foldr f z l
```

對應計算邏輯展開爲：

```hs
foldr f z [x1, x2, ..., xn] = f x1 (f x2 (... (f xn z)))
```

相對foldl方法，foldr計算邏輯並非非尾遞歸，因而不能被優化爲循環，計算邏輯中表達式會遞歸展開，進而消耗較大的內存。
由於foldr中遞歸邏輯中每一步計算邏輯均依賴於下一步，因而不存在惰性求值問題，相比惰性求值下foldl的thunk堆積更高效。

## 強制求值
標準庫中提供了`seq`、`$!`等函數可立即對指定字段求值。
seq函數對函數的首個參數強制求值；`$!`函數則對第二參數強制求值，之後傳入第一參數提供的函數中執行。
相關函數定義：

```hs
seq :: a -> b -> b 	-- Defined in ‘GHC.Prim’
infixr 0 `seq`

($!) :: (a -> b) -> a -> b 	-- Defined in ‘GHC.Base’
infixr 0 $!
```

示例：

```hs
Prelude> :{
Prelude| doSomething :: Int -> IO ()
Prelude| doSomething n = do
Prelude|   print "Before..."
Prelude|   print $ "After: " ++ show n ++ "..."
Prelude| :}

-- 普通調用
Prelude> doSomething 123
"Before..."
"After: 123..."

-- 使用包含異常的參數，參數真正被使用時拋出異常
Prelude> doSomething undefined
"Before..."
"After: "*** Exception: Prelude.undefined
CallStack (from HasCallStack):
  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
  undefined, called at <interactive>:199:13 in interactive:Ghci21

-- 使用"$!"函數，提前對參數強制求值，異常提前觸發
Prelude> doSomething $! undefined
*** Exception: Prelude.undefined
CallStack (from HasCallStack):
  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
  undefined, called at <interactive>:200:16 in interactive:Ghci21

-- 使用seq函數，作用類似
Prelude> seq undefined $ doSomething 123
*** Exception: Prelude.undefined
CallStack (from HasCallStack):
  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
  undefined, called at <interactive>:201:5 in interactive:Ghci21
```

需要注意，seq和`$!`函數雖然能對指定參數強制求值，但若函數表達式本身未被執行則不會生效。
修改前文中的代碼：

```hs
main :: IO ()
main = do
  let f = (1+) $! error "Error Arg!"
  print "Before..."
  let s = f - 1
  print "After..."
```

輸出結果：

```
"Before..."
"After..."
```

由結果可知，函數正常執行完畢，`$!`函數對異常參數的強制求值並未生效。
函數體中Monad的do語法糖實際近似如下代碼：

```hs
main :: IO ()
main =
  let f = (1+) $! error "Error Arg!" in print "Before..." >>
    let s = f - 1 in print "After..."
```

中間字段實際並未被使用，整個表達式沒有真正執行，對參數的強制求值也未生效。

## BangPatterns
直接使用`seq`、`$!`等函數對字段進行強制求值較爲繁瑣，當需要對多個字段強制求值時需要編寫大量的冗餘代碼。
對此GHC提供了`BangPatterns`擴展：

```hs
{-# LANGUAGE BangPatterns #-}
```

開啓擴展後，字段前添加`!`操作符即代表對該字段進行嚴格求值(Strict)。
`!`操作符可用在多數場景下：

- `let`綁定

	在let綁定時在字段前添加`!`操作符，則綁定時會立即求值：

	```hs
	-- 默認惰性求值，異常字段只要不使用就不會觸發異常
	Prelude> let n = undefined in print "Lazy"
	"Lazy"

	-- 使用BangPatterns，異常在字段綁定時觸發
	Prelude> let !n = undefined in print "Strict"
	*** Exception: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
	  undefined, called at <interactive>:206:10 in interactive:Ghci24

	-- 在do語法糖中同樣有效
	Prelude> :{
	Prelude| do
	Prelude|   let !n = undefined
	Prelude|   print "Strict"
	Prelude| :}
	*** Exception: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
	  undefined, called at <interactive>:209:12 in interactive:Ghci24
	```

- 類型構造器

	在類型構造器的參數前添加`!`操作符，則使用構造器時會對該參數強制求值：

	```hs
	-- 定義一個ADT，分別帶有惰性求值和嚴格求值的構造器
	Prelude> data Data = Lazy String | Strict !String deriving Show
	-- 處理該類數據
	Prelude> :{
	Prelude| dealData :: Data -> String
	Prelude| dealData (Lazy _) = "Lazy"
	Prelude| dealData (Strict _) = "Strict"
	Prelude| :}

	-- 惰性求值，使用異常字段構造數據，異常字段未被使用，正常輸出結果
	Prelude> dealData $ Lazy undefined
	"Lazy"

	-- 嚴格求值，使用異常字段構造數據，構造時立即觸發異常
	Prelude> dealData $ Strict undefined
	"*** Exception: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
	  undefined, called at <interactive>:247:19 in interactive:Ghci35
	```

- 模式匹配

	使用模式匹配特性時，可對整個表達式或解構的指定字段使用`!`操作符：

	```hs
	-- 不使用"!"操作符，未使用異常字段，不觸發異常
	Prelude> case (1, undefined) of { (a, b) -> print "Lazy" }
	"Lazy"

	-- 在模式匹配表達式外部使用"!"操作符，未使用異常字段，不觸發異常
	Prelude> case (1, undefined) of { !(a, b) -> print "Strict Out" }
	"Strict Out"

	-- 在模式匹配內部的異常字段前使用"!"操作符，能夠觸發異常
	Prelude> case (1, undefined) of { (a, !b) -> print "Strict Inner" }
	*** Exception: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries/base/GHC/Err.hs:79:14 in base:GHC.Err
	  undefined, called at <interactive>:38:10 in interactive:Ghci13
	```

	在let綁定的模式匹配中使用`!`操作符，規則類似，但let綁定中外層模式匹配也需要使用`!`操作符。
	示例：

	```hs
	{-# LANGUAGE BangPatterns #-}

	main :: IO ()
	main = do
	  let (a, b) = (1, undefined)
	  print "Lazy"
	  let !(a, b) = (1, undefined)
	  print "Strict Out"
	  let (a, !b) = (1, undefined) -- 整個let綁定由於惰性求值特性而未被求值，內部字段的"!"操作也未生效
	  print "Strict Inner"
	  let !(a, !b) = (1, undefined)
	  print "Strict Out and Inner"
	```

	輸出結果：

	```
	"Lazy"
	"Strict Out"
	"Strict Inner"
	lazy.exe: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
	  undefined, called at test\TestLazy.hs:35:22 in main:Main
	```

	需要注意，在目前版本的`GHCi`(`GHCi, version 8.2.2`)環境下，let綁定的模式匹配中使用`!`**無效**。
	示例：

	```hs
	Prelude> let (a, !b) = (1, undefined) in print "Lazy"
	"Lazy"
	Prelude> let !(a, !b) = (1, undefined) in print "Lazy"
	"Lazy"
	```



# Type Class
`Type Class`(類型類)是用於支持點對點多態(ad hoc polymorphism)的類型系統結構，
通過在參數化多態類型中添加類型參數約束來實現。

type class的實際作用近似於OOP語言中的接口，一個type class中通常包含一個類型參數和若干抽象方法，
通過提供type class在不同類型參數時的實例來爲抽象方法提供多種實現，
調用type class中方法時，會根據參數類型使用不同實例提供的實現，以此達到函數重載的目的(多態性)。

使用`class`關鍵字定義type class，`instance`關鍵字定義實例，
`=>`操作符用於要求類型參數必須實現某些type class(可以要求參數類型實現多個type classes)。
示例：

```hs
{-# LANGUAGE FlexibleInstances #-}

module Main where

-- 定義type class
class TypeClass t where
  doSomething :: t -> IO ()

-- 針對不同類型爲type class類的抽象方法"doSomething"提供不同的實現
instance TypeClass Int where
  doSomething t = print $ "Int Type Class: " ++ show t

-- 使用語言擴展"FlexibleInstances"開啓泛型參數特化
instance TypeClass String where
  doSomething t = print $ "String Type Class: " ++ t

-- 要求類型參數t必須實現type class類
testTypeClass :: TypeClass t => t -> IO ()
testTypeClass t = doSomething t

main :: IO ()
main = do
  testTypeClass (233 :: Int)
  testTypeClass "666"
```

輸出結果：

```
Int Type Class: 233
String Type Class: 666
```

由輸出結果可知，調用`testTypeClass`方法時，根據使用參數類型的不同，方法使用了不同的實現。

## 變長參數重載
type class的參數可以使用高階Kind，搭配`FlexibleInstances`擴展，
可以改變type class接口函數的實際簽名，實現變長參數重載：

```hs
{-# LANGUAGE FlexibleInstances #-}

class TypeClassWithDynamicArgs a where
  dynamicArgs :: a

instance TypeClassWithDynamicArgs (Int -> IO ()) where
  dynamicArgs = \a -> print $ "Int: " ++ show a

instance TypeClassWithDynamicArgs (String -> IO ()) where
  dynamicArgs = \b -> print $ "String: " ++ b

instance TypeClassWithDynamicArgs (Int -> String -> IO ()) where
  dynamicArgs = \a b -> print $ "Int: " ++ show a ++ ", String: " ++ b

-- overload method with different number of parameter in argument list (parametric polymorphism)
main = do
  dynamicArgs (666 :: Int) :: IO ()
  dynamicArgs "2333" :: IO ()
  dynamicArgs (666 :: Int) "2333" :: IO () -- allow two parameters
```

輸出結果：

```
"Int: 666"
"String: 2333"
"Int: 666, String: 2333"
```

## 使用TypeClass定義可無限遞歸的接口
type class的接口方法參數中可以返回自身類型，同時在開啟了`FlexibleInstances`擴展的情況下，
type class可以參數可以為函數簽名(`* -> ... -> *`)，將需要遞歸處理的參數作為輸入參數類型傳入。

假設需要定義一個支持變長參數表的的`recurse`函數，能夠打印輸出。

定義如下type class接口：

```hs
class TypeClassRecursion t where
  recurse :: [String] -> t
```

定義遞歸實例的實現：

```hs
instance (Show a, TypeClassRecursion t) => TypeClassRecursion (a -> t) where
  recurse v a = recurse $ v ++ [show a]
```

在遞歸實例中，使用`Show a -> TypeClassRecursion t`作為實現類型，
這使得type class接口函數的參數表實際變為：

```hs
recurse :: (Show a, TypeClassRecursion t) => [String] -> a -> t
```

展開之後的接口可以額外容納一個參數(在本例中是`Show a`)，
由於該接口的實際返回類型依舊是`TypeClassRecursion t`，該類型可繼續視為可被展開的目標，
實際上可以繼續遞歸展開類型：

```hs
recurse :: (Show a, TypeClassRecursion t) => [String] -> a -> t
  |
 \|/
recurse :: (Show a, TypeClassRecursion t) => [String] -> a -> a -> t
  |
 \|/
 ...
```

依此遞歸展開類型之後，即可實現接受變長參數，通常應再實現一個簡單類型實例作為遞歸的終止點。

完整實例：

```hs
{-# LANGUAGE FlexibleInstances #-}

class TypeClassRecursion t where
  recurse :: [String] -> t
  p :: t
  p = recurse ["print:"]

instance TypeClassRecursion (IO ()) where
  recurse = putStrLn . foldl1 ((++) . (++ " "))

instance (Show a, TypeClassRecursion t) => TypeClassRecursion (a -> t) where
  recurse v a = recurse $ v ++ [show a]

main :: IO ()
main = do
  p "FreeHK" "Fu*kCCP" :: IO ()
  p 1984 "1959-1961" 8964 7.09 :: IO ()
```

輸出結果：

```
print: "FreeHK" "Fu*kCCP"
print: 1984 "1959-1961" 8964 7.09
```

Haskell的標準庫中的`Text.Printf.PrintfType`使用了該技巧提供了變長參數表用以接收不定量的輸入參數。

## Multi-parameter Type Classes
type class允許多個類型參數，因而type class可被視爲多個類型之間的關聯。

與傳統的OOP語言類似，多參數type class支持在調用函數時根據多個參數的類型調用不同的函數實現。
多參數type class同樣不需要在運行時查找方法的實現，在編譯期間使用類型匹配的type class實例。

多參數type class特性並不是Haskell標準的一部分，在GHC中，開啓多參數type class特性需要使用語言擴展：

```hs
{-# LANGUAGE MultiParamTypeClasses #-}
```

示例：

```hs
{-# LANGUAGE FlexibleInstances, MultiParamTypeClasses #-}

class MultiParamTypeClasses a b where
  m :: a -> a -> b

instance MultiParamTypeClasses String String where
  m = (++)

instance MultiParamTypeClasses Int String where
  m = (flip $ (++) . show) . show

main :: IO ()
main = do
  print (m "123" "456" :: String) -- 需要顯式寫明無法被推導出的返回值類型
  print (m (123 :: Int) 456 :: String)
```

輸出結果：

```
"123456"
"456123"
```

## Functional Dependencies
functional dependencies特性用於限制多參數type class的類型參數，讓其中的某個類型參數可由其它類型參數決定。
例如，一個類型參數可以是方法的返回值類型，而不是方法的參數類型。

在GHC中，開啓type class的functional dependencies特性需要使用語言擴展：

```hs
{-# LANGUAGE FunctionalDependencies #-}
```

在type class聲明中的參數列表後使用`|`操作符追加參數依賴關係定義，參數依賴語法類似函數參數簽名：

```hs
class XxxTypeClass typeA typeB typeC ... | typeA typeB ... -> typeC where
  ...
```

Haskell中type class方法簽名可以僅重載返回值(即多個方法參數類型相同，僅有返回值類型不同)，
此類方法在調用時需要顯式標註表達式的返回值類型，參考上一節的示例。

使用functional dependencies特性能夠避免一些場景下無法直接推導出類型時的顯式類型標註，
如上述的類型參數在返回值的情形。上一節的例子中，使用functional dependencies特性的示例：

```hs
{-# LANGUAGE FlexibleInstances, MultiParamTypeClasses, FunctionalDependencies #-}

-- 指定類型參數依賴關係，聲明類型參數"b"由類型參數"a"決定
class MultiParamTypeClasses a b | a -> b where
  m :: a -> a -> b -- 方法參數類型與類型參數依賴關係相符

instance MultiParamTypeClasses String String where
  m = (++)

instance MultiParamTypeClasses Int String where
  m = (flip $ (++) . show) . show

main :: IO ()
main = do
  print $ m "123" "456" -- 不再需要返回值類型標註
  print $ m (123 :: Int) 456
```

在指定類型參數依賴關係時，需要保證類型依賴關係與方法簽名相匹配，否則依然需要指定返回類型標註：

```hs
{-# LANGUAGE FlexibleInstances, MultiParamTypeClasses, FunctionalDependencies #-}

class MultiParamTypeClasses a b | b -> a where
  m :: a -> a -> b -- 方法參數類型與類型依賴關係不符，依賴關係中定義類型"a"由類型"b"推導

instance MultiParamTypeClasses String String where
  m = (++)

main :: IO ()
main = print $ m "123" "456" -- 編譯報錯，類型依賴關係未生效
```

編譯時得到錯誤信息：

```hs
• Ambiguous type variable ‘a0’ arising from a use of ‘m’
  prevents the constraint ‘(MultiParamTypeClasses
                              [Char] a0)’ from being solved.
  Probable fix: use a type annotation to specify what ‘a0’ should be.
  These potential instance exist:
    instance MultiParamTypeClasses String String
      -- Defined at ...
• In the second argument of ‘($)’, namely ‘m "123" "456"’
  In the expression: print $ m "123" "456"
  In an equation for ‘main’: main = print $ m "123" "456"
```

對於使用了functional dependencies特性的type class而言，添加instance時，
類型依賴路徑相同的實例僅能存在一個，否則編譯報錯。
示例：

```hs
class MultiParamTypeClasses a b | a -> b where
  m :: a -> a -> b

-- 編譯報錯，存在兩個類型依賴路徑衝突的實例
instance MultiParamTypeClasses String String where m = (++)
instance MultiParamTypeClasses String Int where m = (flip $ (+) . read) . read
```

編譯時得到的錯誤信息：

```hs
Functional dependencies conflict between instance declarations:
  instance MultiParamTypeClasses String String
    -- Defined at ...
  instance MultiParamTypeClasses String Int
    -- Defined at ...
```

在該例子中，`instance MultiParamTypeClasses String String`的類型依賴`String -> String`與`instance MultiParamTypeClasses String Int`的類型依賴`String -> Int`存在衝突(都是`String -> ?`)，
兩個實例聲明的方法簽名`m :: String -> String -> String`與`m :: String -> String -> Int`存在調用歧義(需要依賴返回值確定實際調用者)，
不使用functional dependencies特性時正常通過編譯，啓用functional dependencies特性時則編譯報錯。



# Exception
與主流編程語言類似，Haskell中提供了`Exception`(異常)機制來表示程序運行中產生的意外狀態。

Haskell程序中默認的異常行爲是中斷程序，並將異常信息輸出到終端；可以使用異常處理相關API來自定義異常產生後的行爲。

## 異常類型
Haskell中異常接口由`Control.Exception`模塊中的type class Exception定義：

```hs
class (Data.Typeable.Internal.Typeable e, Show e) =>
      Exception e where
  toException :: e -> SomeException
  fromException :: SomeException -> Maybe e
  displayException :: e -> String
  	-- Defined in ‘GHC.Exception’
```

在GHC的實現中，type class Exception實際定義爲`GHC.Exception`。
Control.Exception模塊中定義了多個常見的異常類型，如`IOException`、`AsyncException`、`TypeError`等。

`SomeException`類型是所有異常的基類，當拋出一個任意類型的異常時，實際的異常會被封裝到SomeException中。
類型定義：

```hs
data SomeException where
  SomeException :: Exception e => e -> SomeException
  	-- Defined in ‘GHC.Exception’
instance Show SomeException -- Defined in ‘GHC.Exception’
instance Exception SomeException -- Defined in ‘GHC.Exception’
```

## 異常 API
`Prelude`模塊中默認已導入了`undefined`、`error`等函數，用於產生默認類型的異常：

```hs
undefined :: forall (r :: RuntimeRep). forall (a :: TYPE r). HasCallStack => a
error :: forall (r :: RuntimeRep). forall (a :: TYPE r). HasCallStack => [Char] -> a
```

`Control.Exception`模塊提供了通用的異常處理函數，主要API介紹：

- `try*`系列函數執行給定的邏輯，將結果存放在`IO Either`類型中。

	```hs
	try :: Exception e => IO a -> IO (Either e a)
	tryJust :: Exception e => (e -> Maybe b) -> IO a -> IO (Either b a)
	```

	示例：

	```hs
	{-# LANGUAGE LambdaCase #-}

	import Control.Exception

	main :: IO
	main = (try $ do
	  let n1 = 1
	  let n2 = error "Try Exception!"
	  print "Run..."
	  return $! n1 + n2) >>= \case
	    Left (SomeException e) -> print $ "Exception info: " ++ (displayException e)
	    Right a -> print $ "Success: " ++ show a
	```

- `catch*/handle*`系列函數執行給定的邏輯，在發生異常時執行給定的異常處理邏輯。

	```hs
	-- catch系列函數無論目標操作是否產生異常，都返回給定類型的值，操作異常時返回值由給定的異常處理邏輯產生
	catch :: Exception e => IO a -> (e -> IO a) -> IO a
	catches :: IO a -> [Handler a] -> IO a
	catchJust :: Exception e => (e -> Maybe b) -> IO a -> (b -> IO a) -> IO a

	-- handle系列函數作用與catch系列對應函數相同，僅參數位置不同
	handle :: Exception e => (e -> IO a) -> IO a -> IO a
	handleJust :: Exception e => (e -> Maybe b) -> (b -> IO a) -> IO a -> IO a
	```

	示例：

	```hs
	import Control.Exception

	main :: IO ()
	main = do
	  re1 <- catch (do
	    let n1 = 1
	    let n2 = error "Catch Exception!"
	    print "Run..."
	    return $! n1 + n2) $ \e -> do
	      print $ "Exception info: " ++ show (e :: SomeException)
	      return 233
	  re2 <- handle (\e -> do
	    print $ "Exception info: " ++ show (e :: SomeException)
	    return 666) $! do
	      let n1 = 1
	      let n2 = error "Handle Exception!"
	      print "Run..."
	      return $! n1 + n2
	  print $ "Result1: " ++ show re1
	  print $ "Result2: " ++ show re2
	```

## 異常捕獲與求值策略
在Haskell中，默認爲惰性求值，因此異常字段在其被求值前不會觸發異常，該特性會導致異常可能不被異常捕獲邏輯所捕獲。
示例：

```hs
{-# LANGUAGE LambdaCase #-}

import Control.Exception

main :: IO
main = (try $ do
  let n1 = 1
  let n2 = error "Try Exception!" -- 嚴格求值的語言在執行到此行代碼時，異常就會立即觸發
  print "Run..." -- Haskell中的惰性求值使得異常沒有立即觸發，後續邏輯繼續執行
  return $ n1 + n2) >>= \case -- 異常信息沒有被捕獲進入提供的Lambda邏輯
    Left (SomeException e) -> print $ "Exception info: " ++ displayException e
    Right a -> print $ "Success: " ++ show a
```

運行結果：

```
"Run..."
exception.exe: Try Exception!
CallStack (from HasCallStack):
  error, called at test\TestException.hs:9:12 in main:Main
```

在上述例子中，try函數沒有對首個參數中的IO邏輯求值，捕獲到異常信息，執行`>>=`操作時，開始真正對IO操作進行求值，
求值時觸發異常，但此時程序已脫離了異常捕獲邏輯，異常直接觸發導致程序崩潰。

要規避此類問題，需要在IO邏輯內部對返回結果進行強制求值(使用`$!`、`seq`函數)，提前觸發異常，
讓異常在受到捕獲函數控制時觸發，而非脫離了異常捕獲函數之後再觸發。

## 異常安全
在傳統編程語言中，C++使用`RAII`機制、Java使用`try ... catch ... finally ...`語法保證代碼塊中出現異常時，
已分配的資源能夠被正確釋放。
在Haskell中，則使用`Control.Exception`模塊中提供的工具函數保障異常安全，相關API：

```hs
-- 第一參數爲獲取資源操作，第二參數爲釋放資源操作，第三參數爲在資源分配與釋放之間真正需要執行的操作
-- 當第三參數中的操作出現異常時，函數會先執行資源釋放操作，之後再重新拋出異常
bracket :: IO a -> (a -> IO b) -> (a -> IO c) -> IO c
bracket_ :: IO a -> IO b -> IO c -> IO c

-- 與bracket函數類似，但僅在產生異常時執行資源釋放操作
bracketOnError :: IO a -> (a -> IO b) -> (a -> IO c) -> IO c

-- 執行第一參數中提供的操作，之後執行第二參數中提供的操作(無論第一操作是否發生異常)
finally :: IO a -> IO b -> IO a

-- 與finally函數類似，但第二操作僅在發生異常觸發後執行
onException :: IO a -> IO b -> IO a
```

示例：

```hs
main = do

  _ <- onException (doSomething 1) after
  _ <- onException (error "onException") after
  bracket_ before after (doSomething $ error "bracket_")

  where

    doSomething :: Int -> IO Int
    doSomething v = do
      let n1 = 1
      let n2 = v
      print $ "Run [" ++ show v ++ "]..."
      return $! n1 + n2

    before, after :: IO ()
    before = print "Before action..."
    after = print "After action..."
```

## 自定義異常
自定義異常需要讓做爲異常的類型實現`Control.Exception`模塊中提供的Exception類。
Exception類繼承於`Typeable`和`Show`類，Exception類**沒有**必須要實現的方法，可直接爲實現了Show類的類型創建實例。

使用`Control.Exception`模塊中提供的`throw*`系列方法拋出指定類型的異常，相關方法的API：

```hs
throw :: forall (r :: RuntimeRep). forall (a :: TYPE r). forall e. Exception e => e -> a
throwIO :: Exception e => e -> IO a
ioError :: IOError -> IO a
throwTo :: Exception e => ThreadId -> e -> IO ()
```

捕獲異常時，可指定異常類型，或使用`SomeException`類型捕獲所有種類的異常。
當捕獲異常的類型不匹配時，異常會繼續拋出。

示例：

```hs
import Control.Exception

-- 自定義異常類型
data MyException = MyException String deriving Show
instance Exception MyException -- 爲異常類實現Exception類

main :: IO ()
main = do

  re1 <- catch (doSomething e1) dealException
  print $ "Result1: " ++ show re1

  re2 <- handle dealMyException $ doSomething e2
  print $ "Result2: " ++ show re2

  re3 <- handle dealMyException $ doSomething e1 -- 不會捕獲與實際異常不相符的異常
  print $ "Result3: " ++ show re3

  where

    e1, e2 :: Int
    e1 = error "Error!"
    e2 = throw $ MyException "MyException!"

    doSomething :: Int -> IO Int
    doSomething e = do
      let n1 = 1
      let n2 = e
      print "Run..."
      return $! n1 + n2

    dealException :: SomeException -> IO Int -- 捕獲所有類型的異常
    dealException = showException

    dealMyException :: MyException -> IO Int -- 僅捕獲自定義類型的異常
    dealMyException = showException

    showException :: Exception e => e -> IO Int
    showException = (>> return 0) . putStrLn . ("Catch the exception: "++) . displayException
```

輸出結果：

```
"Run..."
Catch the exception: Error!
CallStack (from HasCallStack):
  error, called at test\TestException.hs:32:10 in main:Main
"Result1: 0"
"Run..."
Catch the exception: MyException "MyException!"
"Result2: 0"
"Run..."
exception.exe: Error!
CallStack (from HasCallStack):
  error, called at test\TestException.hs:32:10 in main:Main
```

由輸出結果可知，類型不匹配的異常並未被成功捕獲，而是觸發並中斷了程序。



# Monad
`Monad`是Haskell、Scala等函數式語言中用於構建複雜計算邏輯的抽象。

Monad類型的繼承關係：

```
Functor => Applicative => Monad
```

- `Functor`

	定義：

	```hs
	class Functor (f :: * -> *) where
	  fmap :: (a -> b) -> f a -> f b
	  (<$) :: a -> f b -> f a
	  {-# MINIMAL fmap #-}
	  	-- Defined in ‘GHC.Base’
	```

	Functor類型至少需要實現`fmap`函數，fmap需要提供參數類型之間的直接變換邏輯。

	Functor滿足如下規則：

	```hs
	fmap id = id
	fmap (f . g) = fmap f . fmap g
	```

	對於Functor類型，亦可使用`<$>`操作符，功能與fmap函數相同：

	```hs
	(<$>) :: Functor f => (a -> b) -> f a -> f b
	        -- Defined in ‘Data.Functor’
	infixl 4 <$>
	```

- `Applicative`

	定義：

	```hs
	class Functor f => Applicative (f :: * -> *) where
	  pure :: a -> f a
	  (<*>) :: f (a -> b) -> f a -> f b
	  (*>) :: f a -> f b -> f b
	  (<*) :: f a -> f b -> f a
	  {-# MINIMAL pure, (<*>) #-}
	  	-- Defined in ‘GHC.Base’
	```

	Applicative類型至少需要實現`pure`和`<*>`操作符：

	- pure函數定義參數類型到Applicative的構造邏輯。
	- `<*>`操作符作用與fmap類似，但參數類型的變換邏輯包裝在在Applicative類型中。

- `Monad`

	定義：

	```hs
	class Applicative m => Monad (m :: * -> *) where
	  (>>=) :: m a -> (a -> m b) -> m b
	  (>>) :: m a -> m b -> m b
	  return :: a -> m a
	  fail :: String -> m a
	  {-# MINIMAL (>>=) #-}
	  	-- Defined in ‘GHC.Base’
	```

	Monad類型至少需要實現`>>=`操作符。
	`>>=`操作符需要提供源參數類型生成包含目標參數類型的Monad的變換邏輯。
	`>>=`操作順序地組合兩個動作，將前一個動作的處理結果做爲參數傳遞給後一個。

	`>>`操作符用於將返回值無關的Monad操作相連。`>>`操作順序地組合兩個動作，但丟棄前一個動作的處理結果，
	類似於命令式語言(imperative languages)中的分隔符，比如C中的分號。

	`return`函數提供參數類型到Monad的構造邏輯，由於Monad是Applicative子類，return默認使用pure函數做爲實現。

Monad類型應遵循下列規則：

```hs
return a >>= k = k a
m >>= return = m
m >>= (\x -> k x >>= h) = (m >>= k) >>= h
```

Monad與Applicative實現函數/操作符時應遵循下列規則：

```hs
pure = return
(<*>) = ap
```

這些規則可推導出：

```hs
fmap f xs = xs >>= return . f
(>>) = (*>)
```

Haskell標準庫中Monad的實例類型如`[]`、`Maybe`、`IO`等均遵循以上規則。

## do 語法
Haskell中提供了Monad的語法糖，使用do關鍵字能夠以更接近命令式語言的語法操作Monad。

以常見的`IO Monad`爲例：

```hs
name :: IO ()
name =
  print "What is your first name? " >>
  getLine >>= \first ->
  print "And your last name? " >>
  getLine >>= \last ->
  let full = first ++ " " ++ last
  in print $ "Pleased to meet you, " ++ full ++ "!"
```

使用do語法糖可以改寫爲：

```hs
-- 使用do語法糖更類似C語言的命令式風格，邏輯更易理解
nameDo :: IO ()
nameDo = do
  print "What is your first name? "
  first <- getLine
  print "And your last name? "
  last <- getLine
  let full = first ++ " " ++ last
  print $ "Pleased to meet you, " ++ full ++ "!"
```

## ApplicativeDo
`GHC 8.0.1`開始提供了針對Applicative類型的do語法糖語言擴展：

```hs
{-# LANGUAGE ApplicativeDo #-}
```

實例：

```hs
data App a = App {
  app :: a
} deriving (Eq, Show)

instance Functor App where
  fmap = (App.) . (.app)

instance Applicative App where
  pure = App
  (<*>) = flip (flip (App.) . app) . app

-- 原始 Applicative 類型運算邏輯
app1 = (App.) . (flip $ (++) . show) <$> App "abc" <*> App 1

-- 使用 ApplicativeDo 擴展後的等價語法糖表示
app2 = do
  a <- App "abc"
  b <- App 2
  return $ a ++ show b -- 亦可使用 pure 函數
```

## Control.Monad
`Control.Monad`模塊中提供了Monad的常用變換操作。

- `mapM`/`forM`/`mapM_`/`forM_`

	mapM函數定義在Traversable類型中，函數對Foldable類型的每個元素執行參數給定的單子操作(monadic action)，
	從左向右收集結果，並將結果集包裝到單個Monad中。
	forM函數功能與mapM相同，僅參數位置不同。
	函數定義：

	```hs
	class (Functor t, Foldable t) => Traversable (t :: * -> *) where
	  ...
	  mapM :: Monad m => (a -> m b) -> t a -> m (t b)
	  ...
	        -- Defined in ‘Data.Traversable’

	forM :: (Traversable t, Monad m) => t a -> (a -> m b) -> m (t b)
	        -- Defined in ‘Data.Traversable’
	```

	示例：

	```hs
	Prelude Control.Monad> mapM Just [1, 2, 3]
	Just [1,2,3]
	Prelude Control.Monad> forM [1, 2, 3] $ \n -> Just $ n + 1
	Just [2,3,4]
	```

	mapM_/forM_是對應函數的無結果版本，做爲返回值的Monad參數類型固定爲空元組`()`。
	函數定義：

	```hs
	mapM_ :: (Foldable t, Monad m) => (a -> m b) -> t a -> m ()
	        -- Defined in ‘Data.Foldable’

	forM_ :: (Foldable t, Monad m) => t a -> (a -> m b) -> m ()
	        -- Defined in ‘Data.Foldable’
	```

	mapM_/forM_常用於處理不關注返回值副作用操作(IO Monad)。
	示例：

	```hs
	Prelude Control.Monad> mapM_ print [1, 2, 3]
	1
	2
	3
	Prelude Control.Monad> forM_ [1, 2, 3] $ print . (+1)
	2
	3
	4
	```

- `replicateM`/`replicateM_`/`forever`

	replicateM函數執行指定次數的單子操作，將結果以數組形式保存在單個Monad中；
	replicateM_函數是對應的無返回結果版本。
	forever函數則無限地執行給定的單子操作。
	函數定義：

	```hs
	replicateM :: Applicative m => Int -> m a -> m [a]
	  	-- Defined in ‘Control.Monad’

	replicateM_ :: Applicative m => Int -> m a -> m ()
	  	-- Defined in ‘Control.Monad’

	forever :: Applicative f => f a -> f b
	  	-- Defined in ‘Control.Monad’
	```

	示例：

	```hs
	Prelude Control.Monad> replicateM_ 3 $ return 233 >>= print . show
	"233"
	"233"
	"233"
	```

	forever、replicateM等循環函數可使用`fail`、`error`等函數通過拋出異常的方式提前結束循環。
	示例：

	```hs
	Prelude Control.Monad Control.Exception> replicateM_ 3 $ fail "2333"
	*** Exception: user error (2333)
	Prelude Control.Monad Control.Exception> forever $ fail "2333"
	*** Exception: user error (2333)
	Prelude Control.Monad> forever $ error "2333"
	*** Exception: 2333
	CallStack (from HasCallStack):
	  error, called at <interactive>:8:11 in interactive:Ghci1
	```

- `sequence`/`sequence_`

	sequence函數從左向右執行Traversable結構中的每個單子操作，收集結果幷包裝在Monad結構中做爲返回值。
	sequence_函數是sequence的無結果版本。
	函數定義：

	```hs
	class (Functor t, Foldable t) => Traversable (t :: * -> *) where
	  ...
	  sequence :: Monad m => t (m a) -> m (t a)
	        -- Defined in ‘Data.Traversable’

	sequence_ :: (Foldable t, Monad m) => t (m a) -> m ()
	        -- Defined in ‘Data.Foldable’
	```

	示例：

	```hs
	Prelude Control.Monad> actionA = print "Action A" >> return "A"
	Prelude Control.Monad> actionB = print "Action B" >> return "B"
	Prelude Control.Monad> actionC = print "Action C" >> return "C"
	Prelude Control.Monad> sequence [actionA, actionB, actionC] -- 執行後產生副作用，並生成結果
	"Action A"
	"Action B"
	"Action C"
	["A","B","C"]
	Prelude Control.Monad> sequence_ [actionA, actionB, actionC] -- 執行後僅產生副作用，結果爲空
	"Action A"
	"Action B"
	"Action C"
	```

- `=<<`/`>=>`/`<=<`

	`=<<`函數與`>>=`相同，僅參數位置不同。
	`>=>`函數用於從左向右組合Monad操作，`<=<`函數用於從右向左組合Monad操作。
	函數定義：

	```hs
	(=<<) :: Monad m => (a -> m b) -> m a -> m b
	        -- Defined in ‘GHC.Base’
	infixr 1 =<<

	(>=>) :: Monad m => (a -> m b) -> (b -> m c) -> a -> m c
	        -- Defined in ‘Control.Monad’
	infixr 1 >=>

	(<=<) :: Monad m => (b -> m c) -> (a -> m b) -> a -> m c
	        -- Defined in ‘Control.Monad’
	infixr 1 <=<
	```

	示例：

	```hs
	Prelude Control.Monad> print =<< return 2333
	2333
	Prelude Control.Monad> return >=> print $ 2333
	2333
	Prelude Control.Monad> print <=< return $ 2333
	2333
	```



# STM
`STM`全稱`Software Transactional Memory`(軟件事務內存)，是一種對併發通信的模塊化(modular)、可組合(composable)的抽象。
相對與鎖/MVars，STM能夠在不暴露抽象如何保證安全性細節的前提下，簡單地與其它使用STM的抽象相組合。

## STM 概念
在經典的併發編程模型中，對於共享變量進行跨線程的修改通常需要通過加鎖保證數據的讀寫一致性，
然而常規的基於鎖的併發模型對於開發者而言有較大的心智負擔，對鎖的不當操作會引起死鎖等問題。

在STM模型下，將具有邏輯依賴關係的多個共享變量讀寫操作組合成一個事務，
當一個線程內的事務操作開始時，操作的影響並不會立即對其它線程可見，直到該事務內部的所有操作完成；
當事務操作完成時，會產生以下兩種結果：

1. 沒有其它線程修改了相同的共享變量，當前線程的事務操作結果會對其它線程可見。
1. 否則當前線程的操作會被丟棄，然後該事務會被重新執行。

事務操作具有隔離性(isolated)，以此來規避鎖問題。

## STM API 介紹
`Control.Monad.STM`模塊提供了STM結構定義和Monad變換操作；
`Control.Concurrent.STM`模塊提供了STM相關容器的實現。

`Control.Monad.STM`內的`atomically`函數提供了對STM操作的原子執行，
`retry`函數用於重試STM操作，相關API定義：

```hs
-- 原子化地執行一系列STM操作
atomically :: STM a -> IO a

-- 重試STM操作
-- 在GHC的實現中，會阻塞STM操作線程，直至讀取的共享變量已被更新
retry :: STM a

-- 檢測給定的Bool條件，不滿足則重試STM操作(retry)
check :: Bool -> STM ()

-- 在STM操作中拋出和捕獲異常
throwSTM :: Exception e => e -> STM a
catchSTM :: Exception e => STM a -> (e -> STM a) -> STM a
```

STM實現了Monad，因而多個STM操作之間可簡單地相互組合。

`Control.Concurrent.STM`模塊中提供了常見的基於STM的共享變量容器：

| API | 簡介 |
| :- | :- |
| Control.Concurrent.STM.TVar | 最常用的STM共享變量容器，保存單個對象 |
| Control.Concurrent.STM.TMVar | MVar的對應STM版本，可用作條件變量 |
| Control.Concurrent.STM.TArray | MArray的對應STM版本 |
| Control.Concurrent.STM.TChan | FIFO形式的數據通道 |
| Control.Concurrent.STM.TQueue | 數據隊列，與TChan類似，具有更高的吞吐速率，但不支持複製 |
| Control.Concurrent.STM.TBQueue | 數據隊列，與TQueue類似，但具有固定數據數目上限 |

## TVar
`Control.Concurrent.STM.TVar`用於存儲單個共享變量，是最簡單、基礎的API，
支持對共享變量的讀、寫、修改操作。

核心API定義如下：

```hs
-- 使用參數中給定的值創建TVar
newTVar :: a -> STM (TVar a)
-- 創建TVar，保存在IO Monad中，通常用在外層IO方法中
newTVarIO :: a -> IO (TVar a)

-- 讀取TVar
readTVar :: TVar a -> STM a
-- readTVar的IO版本，等價於 atomically . readTVar
readTVarIO :: TVar a -> IO a

-- 寫入TVar，有多種修改方式
writeTVar :: TVar a -> a -> STM ()
modifyTVar :: TVar a -> (a -> a) -> STM ()
swapTVar :: TVar a -> a -> STM a
```

示例：

```hs
import Control.Monad (replicateM_)
import Control.Monad.STM (atomically)
import Control.Concurrent
import Control.Concurrent.Async
import Control.Concurrent.STM.TVar

varA, varB :: IO (TVar Int)
varA = newTVarIO 1000
varB = newTVarIO 0

changeTVar :: String -> TVar Int -> TVar Int -> IO (Async ())
changeTVar i varA varB = async $ replicateM_ 2 $ do
  (a, b) <- atomically $ do
    a <- readTVar varA
    b <- readTVar varB
    let (na, nb) = (a - 20, b + 20)
    writeTVar varA na
    writeTVar varB nb
    return (na, nb)
  threadId <- myThreadId
  printValue ("TVar " ++ i ++ " [" ++ show threadId ++ "]:") a b

printValue :: String -> Int -> Int -> IO ()
printValue prefix a b = print $ foldl1 (++)
  [prefix, " A: [", show a, "], B: [", show b, "]"]

main :: IO ()
main = do
  a <- varA
  b <- varB
  changeTVar "1" a b
  changeTVar "2" a b
  changeTVar "3" a b
  changeTVar "4" a b
  changeTVar "5" a b
  threadDelay 500000
```

輸出結果：

```
"TVar 2 [ThreadId 3]: A: [960], B: [40]"
"TVar 1 [ThreadId 2]: A: [980], B: [20]"
"TVar 3 [ThreadId 4]: A: [940], B: [60]"
"TVar 4 [ThreadId 5]: A: [920], B: [80]"
"TVar 5 [ThreadId 6]: A: [900], B: [100]"
"TVar 2 [ThreadId 3]: A: [880], B: [120]"
"TVar 1 [ThreadId 2]: A: [860], B: [140]"
"TVar 3 [ThreadId 4]: A: [840], B: [160]"
"TVar 4 [ThreadId 5]: A: [820], B: [180]"
"TVar 5 [ThreadId 6]: A: [800], B: [200]"
```

在STM操作下，數據的加減操作爲原子操作執行；
由輸出結果可知，多個線程之間的數據修改操作並未影響數據一致性。

## TChan
`Control.Concurrent.STM.TChan`是FIFO的數據管道，向管道中寫入數據，可從管道中按對應順序讀取。

核心API如下：

```hs
-- 創建數據管道
newTChan :: STM (TChan a)
newTChanIO :: IO (TChan a)

-- 從管道中取出一條數據，取出的數據在管道中會被移除
readTChan :: TChan a -> STM a
-- 從管道中讀取一條數據，讀取的數據不被管道移除
peekTChan :: TChan a -> STM a

-- 向管道中寫入數據，數據被加入管道末尾
writeTChan :: TChan a -> a -> STM ()
-- 向管道中寫入數據，數據被加入管道前端，該數據會立即被下次讀取操作獲取
unGetTChan :: TChan a -> a -> STM ()
```

數據管道簡單示例：

```hs
import Control.Monad
import Control.Monad.STM
import Control.Concurrent
import Control.Concurrent.Async
import Control.Concurrent.STM.TChan

main :: IO ()
main = do

  c <- chan
  a <- sendMessage c
  receiveMessage c
  receiveMessage c
  receiveMessage c
  wait a

  where

    chan :: IO (TChan String)
    chan = newTChanIO

    sendMessage :: TChan String -> IO (Async ())
    sendMessage chan = async $ forever $ do
      input <- getLine
      print $ "Input: " ++ input
      atomically $ writeTChan chan input

    receiveMessage :: TChan String -> IO (Async ())
    receiveMessage chan = async $ do
      threadId <- myThreadId
      forever $ do
        receive <- atomically $ readTChan chan
        print $ "Receive [" ++ show threadId ++ "]: " ++ receive
        threadDelay 500000
```

輸出結果：

```
test1
"Input: test1"
"Receive [ThreadId 3]: test1"
test2
"Input: test2"
"Receive [ThreadId 4]: test2"
test3
"Input: test3"
"Receive [ThreadId 5]: test3"
test4
"Input: test4"
"Receive [ThreadId 3]: test4"
^C⏎
```

TChan支持數據廣播，創建廣播管道並多次複製該管道，向廣播管道中寫入數據，每個複製出的管道都會收到相同數據，
以此實現數據的廣播發送，相關API如下：

```hs

-- 創建廣播管道，廣播管道只能寫入不能讀取(服務端)，僅能通過dupTChan/cloneTChan函數複製出新管道讀取數據
newBroadcastTChan :: STM (TChan a)
newBroadcastTChanIO :: IO (TChan a)

-- 複製數據管道，複製出的管道僅能讀取數據，不能寫入(客戶端)
dupTChan :: TChan a -> STM (TChan a)
cloneTChan :: TChan a -> STM (TChan a)
```

newTChan函數創建的普通管道會一直緩存寫入的數據直到數據從管道中被取出；
newBroadcastTChan函數創建的廣播管道寫入數據時在數據抵達客戶端後即可被垃圾收集。

廣播數據管道示例：

```hs
import Control.Monad
import Control.Monad.STM
import Control.Concurrent
import Control.Concurrent.Async
import Control.Concurrent.STM.TChan

main :: IO ()
main = do

  c <- chan
  a <- sendMessage c
  receiveMessage c
  receiveMessage c
  receiveMessage c
  wait a

  where

    chan :: IO (TChan String)
    chan = newBroadcastTChanIO

    sendMessage :: TChan String -> IO (Async ())
    sendMessage chan = async $ forever $ do
      input <- getLine
      print $ "Input: " ++ input
      atomically $ writeTChan chan input

    receiveMessage :: TChan String -> IO (Async ())
    receiveMessage chan = async $ do
      rChan <- atomically $ dupTChan chan
      threadId <- myThreadId
      forever $ do
        receive <- atomically $ readTChan rChan
        print $ "Receive [" ++ show threadId ++ "]: " ++ receive
```

輸出結果；

```
test1
"Input: test1"
"Receive [ThreadId 3]: test1"
"Receive [ThreadId 4]: test1"
"Receive [ThreadId 5]: test1"
test2
"Input: test2"
"Receive [ThreadId 3]: test2"
"Receive [ThreadId 4]: test2"
"Receive [ThreadId 5]: test2"
^C⏎
```



# GADTs
`GADTs`(Generalized Algebraic Datatypes，廣義代數數據類型)，是ADT的泛化版本，
允許顯式地指定ADT定義中每個構造器的類型。

## ADT 的限制
普通的ADT類型中，無法顯式指定每個構造器的返回值類型。
定義一個代表表達式的類型，如下所示：

```hs
data Expr a =
  Num a | Bool a |
  Add (Expr a) (Expr a) |
  Eq (Expr a) (Expr a) deriving (Show, Eq)
```

`Expr`類型擁有四個構造器，每個構造器返回類型均爲`Expr a`，由於構造器類型相同，在特定組合下會造成語義衝突：

```hs
-- Num構造器不應使用文本做爲參數
Num "Test"
-- Bool構造器應該僅接收Bool類型
Bool 666

-- Bool構造器不應做爲Add的參數，但ADT無法做到精確的類型限制
Add (Bool True) (Bool False)
```

## 使用 GADT
使用GADT需要開啓對應語言擴展：

```hs
{-# LANGUAGE GADTs #-}
```

GADT可以指定每個構造器的簽名：

```hs
data Expr a where
  Num :: Num a => a -> Expr a -- 限制參數類型必須實現 Type Class Num
  Bool :: Bool -> Expr Bool -- 指定參數類型爲Bool型
  Add :: Num a => Expr a -> Expr a -> Expr a
  Eq :: Eq a => Expr a -> Expr a -> Expr Bool
```

各個構造器都添加對應了類型約束，因此下列語句無法通過編譯：

```hs
-- 參數類型[Char]未實現type class
Num "Test"
-- Bool構造器應該僅接收Bool類型
Bool 666

-- 編譯器輸出錯誤信息：
-- ? No instance for (Num Bool) arising from a use of ‘Add’
-- ? In the expression: Add (Bool True) (Bool False)
Add (Bool True) (Bool False)
```



# Type Families
GHC提供了`Type Families`擴展，支持對數據類型的點對點重載(supporting ad-hoc overloading of data types)。

type families是參數化的類型，可根據實例化的類型參數分配特定的表示。
type families用途與type classes類似，type classes用於定義可重載的方法，type families則用於定義可重載的數據類型。

type families適用於以下場景：

- 泛型編程(for generic programming)
- 創建高度參數化的庫接口(for creating highly parameterised library interfaces)
- 創建帶有額外靜態信息的接口，如依賴類型(for creating interfaces with enhanced static information, much like dependent types)

type families擁有兩種形式：`data families`和`type synonym families`。

使用type families需要開啓對應語言擴展：

```hs
{-# LANGUAGE TypeFamilies #-}
```

## Data Families
data families是type families特性用在數據類(data types)的情形，包含以下用法：

- 在頂層代碼使用：

	在頂層代碼中使用時，使用`data family`關鍵字定義類型族，
	使用`data instance`/`newtype instance`關鍵字定義類型族的成員。

	data families用於頂層代碼時，作用一定程度上類似於GADT，能夠爲帶有泛型參數的數據類的每種構造器指定具體的類型。
	示例：

	```hs
	data family Family a
	newtype instance Family Int = FInt Int -- 構造器單參數時可使用newtype關鍵字
	data instance Family String = FString (Family Int) String -- 構造器中的參數可依賴具體的類型族中的其它實例
	data instance Family (Maybe a) = FJust a | FNothing deriving (Show, Eq) -- 每個instance可以deriving各自的type class
	```

	`TypeFamilies`與`GADTs`擴展同時使用時，可直接使用類似GADT的語法定義每個構造器的函數簽名。
	示例：

	```hs
	data family Expr a
	data instance Expr a where
	  Num :: Num a => a -> Expr a
	  Bool :: Bool -> Expr Bool
	  Add :: Num a => Expr a -> Expr a -> Expr a
	  Eq :: Eq a => Expr a -> Expr a -> Expr Bool
	```

	data families與GADT的比較：

	- data families與GADT均能定義每個構造器的參數表與返回類型，
	但GADT需要將所有構造器集中在一處(where子句中)，data families支持分離定義。
	- GADT的每個構造器均能用於通用的模式匹配，data families的構造器僅能針對對應實例類型匹配。

- 在type classes內部使用：

	在type classes內部使用時，用於定義未實現的抽象類型，語法上不必添加family關鍵字；
	在實現帶有data families的type classes時，instance必須定義抽象類型的構造器。
	示例：

	```hs
	class TypeClass a where
	  data Family a

	instance TypeClass Int where
	  data Family Int = FInt Int -- 爲抽象類型定義構造器

	instance TypeClass [a] where
	  data Family [a] = FList [a] | FNil

	...
	```

## Type Synonym Families
type synonym families擴展了type關鍵字定義類型別名的用法，包含以下用法：

- 在頂層代碼使用：

	頂層代碼中的type synonym families擴展了類型別名的功能。
	普通的類型別名僅能指代一種類型(無論別名是否帶有類型參數)；
	type synonym families則強制要求別名帶有類型參數，同時別名在搭配不同的類型參數時可指代不同的實際類型。

	使用`type family`關鍵字定義同義類型族，使用`type instance`定義類型族成員。
	示例：

	```hs
	type family Family a
	type instance Family String = String
	type instance Family Int = Int
	type instance Family (Maybe a) = Maybe a
	... -- 可任意追加其它instance，避免定義 Family a 這樣的類型，會與其它instance衝突
	```

	普通的type synonym families是開放式的，可以任意添加成員(追加新的type instance)，
	type synonym families亦支持類似GADT語法的封閉式(closed)定義，
	將所有的類型族成員定義在where子句內部，不再能從外部擴展。
	示例：

	```hs
	-- 類型族僅包含where子句中列出的成員，不能擴展
	type family Family a where
	  Family [a] = [a]
	  Family String = String
	  Family Int = Int
	  Family (Maybe a) = Maybe a
	```

- 在type classes內部使用：

	在type classes內部使用時，語法上同樣不需要使用`family`；
	功能上相當於添加了一個額外的類型參數，創建對應instance時，需要指定對應的實際類型。
	示例：

	```hs
	class TypeClass a where
	  type Family a

	instance TypeClass Int where
	  type Family Int = Int -- 實現instance時指定具體的類型

	instance TypeClass [a] where
	  type Family [a] = [a]

	...
	```

	在type classes內部使用type synonym families，能夠替代functional dependencies特性：

	```hs
	-- 使用 functional dependencies
	class Collects c e | c -> e where
	  empty  :: c
	  insert :: e -> c -> c
	  member :: e -> c -> Bool
	  toList :: c -> [e]

	-- 等價於使用 type synonym families
	class Collects c where
	  type Elem c
	  empty  :: c
	  insert :: Elem c -> c -> c
	  member :: Elem c -> c -> Bool
	  toList :: c -> [Elem c]
	```

## Type Families Kind
使用`data family`、`type family`關鍵字定義類型族時，可追加可選的Kind簽名。

未顯式指定Kind時，默認Kind爲`*`：

```hs
-- 常規 type families 定義
data family DataFamily a
type family TypeFamily a

-- 等價於以下定義：
data family DataFamily a :: *
type family TypeFamily a :: *

-- 在 type classes 中的定義類似
class TypeClass a where
  data DataFamily a
  type TypeFamily a

-- 等價於以下定義：
class TypeClass a where
  data DataFamily a :: *
  type TypeFamily a :: *
```

使用顯式Kind定義：

```hs
-- 接收單個類型參數
data family KindA1 a
-- 使用 Kind 聲明
data family Kind1 :: * -> *

-- 接收兩個類型參數
data family KindAB2 a b
-- 使用 Kind 聲明
data family Kind2 :: * -> * -> *
-- 同時使用類型參數和 Kind 聲明
data family KindA2 a :: * -> *

-- 依此類推
...
```

在同時使用顯式Kind定義和類型參數時，類型的實際Kind由二者共同決定(相加)：

```hs
-- 實際 Kind 爲 * -> * -> * -> * ，最大可接收三個類型參數
data family Kind3 a b :: * -> *

-- 實際 Kind 爲 * -> * -> * -> * -> * ，最大可接收四個類型參數
data family Kind4 a :: * -> * -> * -> *

-- 實際 Kind 爲 * -> * -> * -> * -> * -> * ，最大可接收五個類型參數
data family Kind5 a b c :: * -> * -> *

-- 依此類推
...
```

在使用類型時，顯式命名的類型參數不可省略，Kind聲明部分的Kind類型參數可選：

```hs
data family Kind a b :: * -> * -- 使用該類型時，a、b兩個顯式命名的類型參數不可省略

Kind Int Int -- 正確，Kind爲 * -> *
Kind Int Int Int -- 正確，Kind爲 *
Kind IO Int -- 錯誤，首個類型類型參數的Kind不匹配
Kind Int -- 錯誤，缺失第二類型參數
```



# Concurrent
`Control.Concurrent`中提供了Haskell的公用異步抽象。

## Async 包
`async`包提供跨多線程執行異步操作的功能。
async包底層使用base包中的`forkIO`函數(在`Control.Concurrent`模塊中)實現，提供了以下改進：

- 徹底、優雅地處理異常(graceful and thorough handling of exceptions)
- 從子線程中獲取返回值
- 提供`STM`接口用於訪問線程返回值，STM提供了方便的方式處理諸如阻塞操作等待結果等問題
- 使得取消線程變得簡單和可靠
- 對於某些通用的用例，`race`、`concurrently`函數和`Concurrently`類型可以大幅簡化代碼

`Async`是async包的主要數據類型，一個`Async a`類型的值表示一個分離的線程(represents a separate thread)，
該線程將最終生成一個`a`類型的值(which will ultimately generate a value of type `a`)。

async包相關API位於`Control.Concurrent.Async`模塊下，主要API介紹：

- `async*`系列函數fork一個線程並返回Async值，`wait*`系列函數等待Async類型返回結果。

	```hs
	-- 異步執行一個操作
	async :: IO a -> IO (Async a)

	-- 阻塞線程，等待一個異步操作執行結束並獲取結果
	wait :: Async a -> IO a
	-- 等待異步結果，並處理異常
	waitCatch :: Async a -> IO (Either SomeException a)

	-- 等待多個操作，任意一個異步操作完成時返回
	waitEither :: Async a -> Async b -> IO (Either a b)
	waitAny :: [Async a] -> IO (Async a, a)

	-- 等待兩個異步操作全部返回
	waitBoth :: Async a -> Async b -> IO (a, b)
	```

	基本的異步操作示例：

	```hs
	import Control.Concurrent
	import Control.Concurrent.Async

	actionN :: Int -> IO String
	actionN num = do
	  let n = show num
	  print $ "Action" ++ n ++ " start..."
	  threadDelay 1000000 -- 暫停線程 1s
	  print $ "Action" ++ n ++ " finished..."
	  return n

	main :: IO ()
	main = do
	  a1 <- async $ actionN 1
	  print "After action1"
	  a2 <- async $ actionN 2
	  print "After action2"
	  (r1, r2) <- waitBoth a1 a2
	  print $ "Finish: " ++ r1 ++ " " ++ r2
	```

	執行結果：

	```
	"Action1 start..."
	"After action1"
	"After action2"
	"Action2 start..."
	"Action1 finished..."
	"Action2 finished..."
	"Finish: 1 2"
	```

- `withAsync*`函數啓動一個獨立線程執行首個參數中傳入的操作，並提供Async值給匿名函數(第二參數)。

	```hs
	withAsync :: IO a -> (Async a -> IO b) -> IO b
	```

	withAsync函數是async函數的一類有用的變體，能夠確保異步操作不會意外地執行(啓動的線程在匿名函數執行結束後被殺死)。

	示例：

	```hs
	import Control.Concurrent
	import Control.Concurrent.Async

	actionN :: Int -> IO String
	actionN num = do
	  let n = show num
	  print $ "Action" ++ n ++ " start..."
	  threadDelay 1000000 -- 暫停線程 1s
	  print $ "Action" ++ n ++ " finished..."
	  return n

	main :: IO ()
	main = do
	  result <- withAsync (actionN 1) $ \a -> do
	    print "WithAsync start..."
	    result <- wait a
	    print $ "WithAsync finished: " ++ result
	    return "2333"
	  print $ "Main finished: " ++ result
	```

	輸出結果：

	```
	"WithAsync start..."
	"Action1 start..."
	"Action1 finished..."
	"WithAsync finished: 1"
	"Main finished: 2333"
	```

- `poll`函數用於檢查Async類型操作是否完成，`cancel`函數用於提前取消異步操作，`asyncThreadId`用於查看線程ID。

	```hs
	-- 檢查一個異步操作是否完成
	poll :: Async a -> IO (Maybe (Either SomeException a))

	-- 取消一個異步操作
	cancel :: Async a -> IO ()
	cancelWith :: Exception e => Async a -> e -> IO ()

	asyncThreadId :: Async a -> ThreadId
	```

- `*STM`系列函數是對應異步操作的STM接口版本。

	```hs
	pollSTM :: Async a -> STM (Maybe (Either SomeException a))

	-- wait系列API均有對應STM版本
	waitSTM :: Async a -> STM a
	waitAnySTM :: [Async a] -> STM (Async a, a)
	waitCatchSTM :: Async a -> STM (Either SomeException a)
	...
	```



# RankNTypes
GHC的類型系統支持任意等級(arbitrary-rank)的顯式類型量化(explicit universal quantification in types)。

使用RankNTypes需要開啓對應語言擴展：

```hs
{-# LANGUAGE RankNTypes #-}
```

使用RankNTypes擴展後可使用`forall`關鍵字定義函數參數表的多態層次。

Haskell標準語法中函數參數表默認即爲`rank-1 types`，如：

```hs
f1 :: a -> b -> a
g1 :: (Ord a, Eq  b) => a -> b -> a
```

等價於使用forall關鍵字描述的參數表：

```hs
f1 :: forall a b . a -> b -> a
g1 :: forall a b . (Ord a, Eq  b) => a -> b -> a
```

使用forall可以在參數表中定義更多多態層級：

```hs
f2 :: (forall a . a -> a) -> Int -> Int
g2 :: (forall a . Eq a => [a] -> a -> Bool) -> Int -> Int

f3 :: ((forall a . a -> a) -> Int) -> Bool -> Bool

f4 :: Int -> (forall a . a -> a)
```

函數`f2`、`g2`爲`rank-2 types`，f2/g2函數在函數箭頭左端擁有局部的forall參數表，參數表內部的多態類型能夠重載。
函數`f3`爲`rank-3 types`，f3函數在函數箭頭左端擁有一個`rank-2 types`的局部forall參數表。

## RankNTypes 示例
RankNTypes常用於函數的部分參數自身爲多態函數的情況下，考慮如下函數：

```hs
rankNTypes :: (Show a, Show b) =>
  (Show ? => ? -> String) -> a -> b -> IO ()
rankNTypes f a b = do
  let (fa, fb) = (f a, f b)
  print $ "a: " ++ fa ++ " b: " ++ fb
```

rankNTypes的參數`f`是一個函數，該函數應能接收`a`或`b`類型的參數(多態)並返回String類型，
滿足要求的f參數類型(使用`?`標識)在標準Haskell語法下沒有合適的表達方式。

使用RankNTypes擴展即可滿足需求：

```hs
{-# LANGUAGE RankNTypes, FlexibleInstances #-}

rankNTypes :: (Show a, Show b) =>
  (forall a . Show a => a -> String) -> a -> b -> IO ()
rankNTypes f a b = do
  let (fa, fb) = (f a, f b)
  print $ "a: " ++ fa ++ " b: " ++ fb

main :: IO ()
main = rankNTypes show 666 "23333"
```

使用了RankNTypes擴展，函數f擁有了獨立的多態層次(rank-2 types)，能夠接收多態參數。
