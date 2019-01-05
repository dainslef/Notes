<!-- TOC -->

- [Haskell 开发环境](#haskell-开发环境)
	- [GHC 常用功能](#ghc-常用功能)
	- [REPL (GHCi)](#repl-ghci)
- [常用函数](#常用函数)
	- [`$` 函数](#-函数)
	- [`.` 函数](#-函数)
- [Currying (柯里化)](#currying-柯里化)
- [Pointfree Style](#pointfree-style)
- [求值策略](#求值策略)
	- [Lazy evaluation 的实现](#lazy-evaluation-的实现)
	- [Lazy evaluation 的优劣](#lazy-evaluation-的优劣)
	- [惰性求值与内存泄漏](#惰性求值与内存泄漏)
	- [强制求值](#强制求值)
	- [BangPatterns](#bangpatterns)
- [Type Class](#type-class)
	- [Multi-parameter Type Classes](#multi-parameter-type-classes)
	- [Functional Dependencies](#functional-dependencies)
- [Monad](#monad)
	- [do 语法](#do-语法)
	- [ApplicativeDo](#applicativedo)
	- [Control.Monad](#controlmonad)
- [STM](#stm)
	- [STM 概念](#stm-概念)
	- [STM API 介绍](#stm-api-介绍)
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
	- [示例](#示例)

<!-- /TOC -->



# Haskell 开发环境
`Haskell`的主流编译器是`GHC`，即`Glasgow Haskell Compiler`。

- **Linux/Unix**系统：

	使用发行版自带的包管理器安装`GHC`。

	`Debian`系发行版

	```
	# apt install ghc
	```

	`Arch`系发行版

	```
	# pacman -S ghc
	```

	`macOS`

	```
	$ brew install ghc
	```

- **Widnows**系统：

	在`https://www.haskell.org/platform/windows.html`下载`Haskell Platform`。
	`Haskell Platform`包含了`GHC`编译器、`Cabal`构建工具等。

推荐使用`Stack`来配置`GHC`编译器。

## GHC 常用功能
Haskell源码后缀为`*.hs`，使用`ghc`指令编译Haskell代码：

```
$ ghc *.hs
```

GHC编译器会直接将Haskell源码编译为对应平台的二进制文件。

## REPL (GHCi)
与Scala类似，GHC编译器同样提供了REPL环境，即GHCi。

使用`ghci`指令进入REPL，在REPL环境下直接输入代码可立即获得反馈。如下所示：

```hs
$ ghci
Configuring GHCi with the following packages:
GHCi, version 8.0.2: http://www.haskell.org/ghc/  :? for help
Prelude> print "Hello World"
"Hello World"
Prelude> :quit
Leaving GHCi.
```

REPL环境下的内部指令均以`:`为前缀，常用指令如下：

| 指令 | 功能 |
| :- | :- |
| :{\n ..lines.. \n:}\n | 多行指令/代码 |
| :help, :? | 查看REPL指令帮助信息 |
| :quit | 退出GHCi环境 |
| :!\<command\> | 在外部Shell中执行指令 |
| :info[!] [\<name\> ...] | 显示指定名称的信息 |
| :type \<expr\> | 显示给定表达式的Type |
| :kind[!] \<type\> | 显示指定类型的Kind |
| :set -X\<extensions\> | 开启指定语言扩展 |
| :unset -X\<extensions\> | 关闭指定语言扩展 |
| :show languages | 显示已开启的语言扩展 |
| :module [+/-] [*]<mod> ... | 导入/移除指定的模块路径 |



# 常用函数
Haskell中可以使用符号做为函数名。

## `$` 函数
`$`常用于消除函数中的括号，函数定义：

```hs
($) ::
  forall (r :: GHC.Types.RuntimeRep) a (b :: TYPE r).
  (a -> b) -> a -> b
  	-- Defined in ‘GHC.Base’
infixr 0 $
```

`$`函数优先级为0，低于几乎所有的常见函数/操作符，使用`$`运算符将函数与之后的参数分隔开，能代替括号操作符改变操作优先级。
示例：

```hs
Prelude> print ("abc" ++ "cde") -- 使用括号改变表达式优先级，与传统命令式语言类似
"abccde"
Prelude> print $ "abc" ++ "cde" -- 使用"$"函数改变优先级更符合Haskell代码风格
"abccde"
```

## `.` 函数
`.`用于组合两个函数，函数定义：

```hs
(.) :: (b -> c) -> (a -> b) -> a -> c 	-- Defined in ‘GHC.Base’
infixr 9 .
```

示例：

```hs
Prelude> print ("abc" ++ "cde" ++ "efg") -- 使用括号改变表达式优先级，与传统命令式语言类似
"abccdeefg"
Prelude> print $ "abc" ++ "cde" ++ "efg" -- 使用"$"函数改变优先级更符合Haskell代码风格
"abccdeefg"
Prelude> print . ("abc"++) . ("cde"++) $ "efg" --使用"."组合函数
```

`.`函数常用于`Pointfree`风格中，通过函数组合来代替多个连续的函数调用。



# Currying (柯里化)
`Currying`(柯里化)是一类函数的转换过程，将通过元组接收多个参数的函数转换为接收单一参数并返回接收另一个参数的函数，
以此逐级递推，通过不断返回接收其它参数的函数来逐渐接收元组中的所有参数。

以签名如下的函数为例：

```hs
f :: (Int, Int, Int, Int) -> Int
```

函数`f`为接收一个四元组作为参数，进行柯里化：

```hs
c1 :: (Int, Int, Int) -> (Int -> Int) -- 从元组中分离出一个参数，返回接收该参数的函数
c2 :: (Int, Int) -> (Int -> (Int -> Int)) -- 再分离出一个参数，返回接收该参数的函数
... -- 重复该操作，直至元组中的参数被完全解构

cN :: Int -> (Int -> (Int -> (Int -> Int))) -- 最终结果
cN :: Int -> Int -> Int -> Int -> Int -- 依据Haskell中的操作符优先级，该签名与上述签名等价
```

`Data.Tuple`模块中提供了`curry/uncurry`函数，用于将函数进行柯里化与逆柯里化：

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
Prelude> uc = uncurry c --逆柯里化
Prelude> :type uc
uc :: (Int, Int) -> Int
Prelude> c 1 2 == uc (1, 2)
True
```

在Haskell中，每个函数实际仅能接收一个参数，多参数函数应用单个参数后返回新函数，从而逐步应用多个参数。
示例：

```hs
Prelude> :{
Prelude| c :: Int -> Int -> Int -> Int -- 定义多参数函数，参数优先级"Int -> (Int -> (Int -> Int))"
Prelude| c x y z = x + y + z
Prelude| :}
Prelude> c 1 2 3
6
Prelude> ((c 1) 2) 3 -- 函数传入多个参数实际是逐步应用单个参数
6
```

对于多参数函数，Haskell允许仅应用部分参数，应用部分参数后生成新的函数，称为`Partial Application`(部分应用函数)。
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



# Pointfree Style
在函数式编程中，通常使用函数之间相互组合来实现新函数，而非显式地提及需要被应用的参数。

考虑如下函数：

```hs
f n = a (b (c n))
```

函数`f`的逻辑是将参数n按顺序依次调用函数`c`、`b`、`a`，使用pointfree风格可以写成：

```hs
f = a . b . c
```

pointfree的作用：

- 能更清晰地展示函数的调用逻辑
- 在某些逻辑中参数名称难以找到合适的名称描述，使用pointfree风格可避免为参数命名



# 求值策略
Haskell默认采用`Lazy evaluation`(懒执行/惰性求值/非严格求值)，字段、函数参数在真正被使用前，不会被求值，
即一个表达式绑定到字段时并没有立即，而是延迟到该表达式的结果被其它计算需要时再执行(进行求值)。

关于Lazy evaluation的详细概念，可参考[Haskell Wiki](https://wiki.haskell.org/Lazy)中的描述。

示例：

```hs
main :: IO ()
main = do
  let f = 1 + error "Error Arg!"
  print "Before..."
  print $ "After: " ++ (show f) -- 打印结果，此时会对f字段进行求值
```

输出结果：

```
"Before..."
Lazy: Error Arg!
CallStack (from HasCallStack):
  error, called at ... in main:Main
```

由输出结果可知，异常并未在表达式创建时就触发，而是真正使用字段时才对表达式求值，从而触发异常。

若一个字段自始自终没有被计算结果依赖，则该字段不会被求值。
包含异常的代码若没有被真正求值，则异常不会触发：

```hs
main :: IO ()
main = do
  let f = 1 + error "Error Arg!"
  print "Before..."
  let s = f - 1
  print $ "After..."
```

输出结果：

```
"Before..."
"After..."
```

由结果可知，包含异常的表达式没有被真正执行，程序正常退出。

## Lazy evaluation 的实现
在Haskell中，Lazy evaluation技术上是`Call by name`加上`Sharing`。
Call by name意味着在字段在需要时再被执行；
Sharing意味着被多次使用的临时数据会被存储，例如在如下表达式中：

```hs
let x = 1 + 1 in x * x
```

字段`x`在之后的表达式中被使用了两次，但字段x不会被多次计算，而是在首次计算后被存储并用于之后的使用。

Lazy evaluation也被称为`Call by need`，Call by need是Call by name的带有记忆性的变体，
Call by need的字段在需要时被求值(Call by name)，字段绑定的表达式执行后结果会被存储(Sharing)，
之后再次访问该字段时，不会再重复执行计算。

在Haskell中，使用名为`Thunk`的数据结构来存储表达式，等到表达式在需要的时刻再执行。
Thunk包含一个布尔类型字段用于记录包含的表达式是否已被计算过：

- 若表达式未被计算，则计算并存储结果
- 若表达式已被计算，则直接获取之前的结果，而非重复进行计算

## Lazy evaluation 的优劣
惰性求值的优势：

- 程序仅在需要时进行求求值，避免了无意义的计算
- 能够表示出一些无限大小的数据(如`[0..]`)，并进行操作

惰性求值的劣势：

- 对于部分基础数据类型，Haskell中全部使用thunk保存数据会有相比原始类型更大的内存开销
- 一些不合理的操作会造成thunk堆积，引起内存泄漏(如`foldl`)
- 计算的执行时机不确定(取决于编译器的实现)

## 惰性求值与内存泄漏
惰性求值的特性将计算推迟到了真正需要求值的时刻，Haskell中使用thunk存储尚未计算的表达式。
对于某些递归计算逻辑而言，可能会造成大量的thunk堆积，进而导致内存泄漏。

以`foldl`函数为例，常规递归实现版本：

```hs
foldl :: (b -> a -> b) -> b -> [a] -> b
foldl f z [] = z
foldl f z (n:l) = foldl f (f z n) l
```

对应计算逻辑展开为：

```hs
foldl f z [x1, x2, ..., xn] = f (... (f (f z x1) x2) ...) xn
```

由于惰性求值的特性，递归中每一步的计算表达式`f z n`并未立即执行计算，而是以thunk的形式堆积，
当计算列表的长度较大时，函数递归展开会有巨大的内存开销。
要避免thunk堆积，应对递归中的单步计算表达式进行强制求值，修改实现：

```hs
foldl' :: (b -> a -> b) -> b -> [a] -> b
foldl' f z [] = z
foldl' f z (n:l) = foldl' f (flip f n $! z) l -- 对传入的上一步递归结果(参数z)进行强制求值，从而避免thunk堆积
```

由于foldl函数的实现是**尾递归**，在严格求值的求值策略下，可被编译器优化成循环。

与foldl相对应，`foldr`函数的递归实现：

```hs
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f z [] = z
foldr f z (n:l) = f n $ foldr f z l
```

对应计算逻辑展开为：

```hs
foldr f z [x1, x2, ..., xn] = f x1 (f x2 (... (f xn z)))
```

相对foldl方法，foldr计算逻辑并非非尾递归，因而不能被优化为循环，计算逻辑中表达式会递归展开，进而消耗较大的内存。
由于foldr中递归逻辑中每一步计算逻辑均依赖于下一步，因而不存在惰性求值问题，相比惰性求值下foldl的thunk堆积更高效。

## 强制求值
标准库中提供了`seq`、`$!`等函数可立即对指定字段求值。
seq函数对函数的首个参数强制求值；`$!`函数则对第二参数强制求值，之后传入第一参数提供的函数中执行。
相关函数定义：

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
Prelude|   print $ "After: " ++ (show n) ++ "..."
Prelude| :}

-- 普通调用
Prelude> doSomething 123
"Before..."
"After: 123..."

-- 使用包含异常的参数，参数真正被使用时抛出异常
Prelude> doSomething undefined
"Before..."
"After: "*** Exception: Prelude.undefined
CallStack (from HasCallStack):
  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
  undefined, called at <interactive>:199:13 in interactive:Ghci21

-- 使用"$!"函数，提前对参数强制求值，异常提前触发
Prelude> doSomething $! undefined
*** Exception: Prelude.undefined
CallStack (from HasCallStack):
  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
  undefined, called at <interactive>:200:16 in interactive:Ghci21

-- 使用seq函数，作用类似
Prelude> seq undefined $ doSomething 123
*** Exception: Prelude.undefined
CallStack (from HasCallStack):
  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
  undefined, called at <interactive>:201:5 in interactive:Ghci21
```

需要注意，seq和`$!`函数虽然能对指定参数强制求值，但若函数表达式本身未被执行则不会生效。
修改前文中的代码：

```hs
main :: IO ()
main = do
  let f = (1+) $! error "Error Arg!"
  print "Before..."
  let s = f - 1
  print "After..."
```

输出结果：

```
"Before..."
"After..."
```

由结果可知，函数正常执行完毕，`$!`函数对异常参数的强制求值并未生效。
函数体中Monad的do语法糖实际近似如下代码：

```hs
main :: IO ()
main =
  let f = (1+) $! error "Error Arg!" in print "Before..." >>
    let s = f - 1 in print "After..."
```

中间字段实际并未被使用，整个表达式没有真正执行，对参数的强制求值也未生效。

## BangPatterns
直接使用`seq`、`$!`等函数对字段进行强制求值较为繁琐，当需要对多个字段强制求值时需要编写大量的冗余代码。
对此GHC提供了`BangPatterns`扩展：

```hs
{-# LANGUAGE BangPatterns #-}
```

开启扩展后，字段前添加`!`操作符即代表对该字段进行严格求值(Strict)。
`!`操作符可用在多数场景下：

- `let`绑定

	在let绑定时在字段前添加`!`操作符，则绑定时会立即求值：

	```hs
	-- 默认惰性求值，异常字段只要不使用就不会触发异常
	Prelude> let n = undefined in print "Lazy"
	"Lazy"

	-- 使用BangPatterns，异常在字段绑定时触发
	Prelude> let !n = undefined in print "Strict"
	*** Exception: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
	  undefined, called at <interactive>:206:10 in interactive:Ghci24

	-- 在do语法糖中同样有效
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

- 类型构造器

	在类型构造器的参数前添加`!`操作符，则使用构造器时会对该参数强制求值：

	```hs
	-- 定义一个ADT，分别带有惰性求值和严格求值的构造器
	Prelude> data Data = Lazy String | Strict !String deriving Show
	-- 处理该类数据
	Prelude> :{
	Prelude| dealData :: Data -> String
	Prelude| dealData (Lazy _) = "Lazy"
	Prelude| dealData (Strict _) = "Strict"
	Prelude| :}

	-- 惰性求值，使用异常字段构造数据，异常字段未被使用，正常输出结果
	Prelude> dealData $ Lazy undefined
	"Lazy"

	-- 严格求值，使用异常字段构造数据，构造时立即触发异常
	Prelude> dealData $ Strict undefined
	"*** Exception: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
	  undefined, called at <interactive>:247:19 in interactive:Ghci35
	```

- 模式匹配

	使用模式匹配特性时，可对整个表达式或解构的指定字段使用`!`操作符：

	```hs
	-- 不使用"!"操作符，未使用异常字段，不触发异常
	Prelude> case (1, undefined) of { (a, b) -> print "Lazy" }
	"Lazy"

	-- 在模式匹配表达式外部使用"!"操作符，未使用异常字段，不触发异常
	Prelude> case (1, undefined) of { !(a, b) -> print "Strict Out" }
	"Strict Out"

	-- 在模式匹配内部的异常字段前使用"!"操作符，能够触发异常
	Prelude> case (1, undefined) of { (a, !b) -> print "Strict Inner" }
	*** Exception: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries/base/GHC/Err.hs:79:14 in base:GHC.Err
	  undefined, called at <interactive>:38:10 in interactive:Ghci13
	```

	在let绑定的模式匹配中使用`!`操作符，规则类似，但let绑定中外层模式匹配也需要使用`!`操作符。
	示例：

	```hs
	{-# LANGUAGE BangPatterns #-}

	main :: IO ()
	main = do
	  let (a, b) = (1, undefined)
	  print "Lazy"
	  let !(a, b) = (1, undefined)
	  print "Strict Out"
	  let (a, !b) = (1, undefined) -- 整个let绑定由于惰性求值特性而未被求值，内部字段的"!"操作也未生效
	  print "Strict Inner"
	  let !(a, !b) = (1, undefined)
	  print "Strict Out and Inner"
	```

	输出结果：

	```
	"Lazy"
	"Strict Out"
	"Strict Inner"
	lazy.exe: Prelude.undefined
	CallStack (from HasCallStack):
	  error, called at libraries\base\GHC\Err.hs:79:14 in base:GHC.Err
	  undefined, called at test\TestLazy.hs:35:22 in main:Main
	```

	需要注意，在目前版本的`GHCi`(`GHCi, version 8.2.2`)环境下，let绑定的模式匹配中使用`!`**无效**。
	示例：

	```hs
	Prelude> let (a, !b) = (1, undefined) in print "Lazy"
	"Lazy"
	Prelude> let !(a, !b) = (1, undefined) in print "Lazy"
	"Lazy"
	```



# Type Class
`Type Class`(类型类)是用于支持点对点多态(ad hoc polymorphism)的类型系统结构，
通过在参数化多态类型中添加类型参数约束来实现。

type class的实际作用近似于OOP语言中的接口，一个type class中通常包含一个类型参数和若干抽象方法，
通过提供type class在不同类型参数时的实例来为抽象方法提供多种实现，
调用type class中方法时，会根据参数类型使用不同实例提供的实现，以此达到函数重载的目的(多态性)。

使用`class`关键字定义type class，`instance`关键字定义实例，`=>`操作符用于要求类型参数必须实现某些type class。
示例：

```hs
{-# LANGUAGE FlexibleInstances #-}

module Main where

-- 定义type class
class TypeClass t where
  doSomething :: t -> IO ()

-- 针对不同类型为TypeClass类的抽象方法"doSomething"提供不同的实现
instance TypeClass Int where
  doSomething t = print $ "Int Type Class: " ++ (show t)

-- 使用语言扩展"FlexibleInstances"开启泛型参数特化
instance TypeClass String where
  doSomething t = print $ "String Type Class: " ++ t

-- 要求类型参数t必须实现TypeClass类
testTypeClass :: TypeClass t => t -> IO ()
testTypeClass t = doSomething t

main :: IO ()
main = do
  testTypeClass (233 :: Int)
  testTypeClass "666"
```

输出结果：

```
Int Type Class: 233
String Type Class: 666
```

由输出结果可知，调用`testTypeClass`方法时，根据使用参数类型的不同，方法使用了不同的实现。

## Multi-parameter Type Classes
type class允许多个类型参数，因而type class可被视为多个类型之间的关联。

与传统的OOP语言类似，多参数type class支持在调用函数时根据多个参数的类型调用不同的函数实现。
多参数type class同样不需要在运行时查找方法的实现，在编译期间使用类型匹配的type class实例。

多参数type class特性并不是Haskell标准的一部分，在GHC中，开启多参数type class特性需要使用语言扩展：

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
  print (m "123" "456" :: String) -- 需要显式写明无法被推导出的返回值类型
  print (m (123 :: Int) 456 :: String)
```

输出结果：

```
"123456"
"456123"
```

## Functional Dependencies
functional dependencies特性用于限制多参数type class的类型参数，让其中的某个类型参数可由其它类型参数决定。
例如，一个类型参数可以是方法的返回值类型，而不是方法的参数类型。

在GHC中，开启type class的functional dependencies特性需要使用语言扩展：

```hs
{-# LANGUAGE FunctionalDependencies #-}
```

在type class声明中的参数列表后使用`|`操作符追加参数依赖关系定义，参数依赖语法类似函数参数签名：

```hs
class XxxTypeClass typeA typeB typeC ... | typeA typeB ... -> typeC where
  ...
```

使用functional dependencies特性能够避免一些场景下无法直接推导出类型时的显式类型标注，如类型参数在返回值的情形。
上一节的例子中，使用functional dependencies特性的示例：

```hs
{-# LANGUAGE FlexibleInstances, MultiParamTypeClasses, FunctionalDependencies #-}

-- 指定类型参数依赖关系，声明类型参数"b"由类型参数"a"决定
class MultiParamTypeClasses a b | a -> b where
  m :: a -> a -> b -- 方法参数类型与类型参数依赖关系相符

instance MultiParamTypeClasses String String where
  m = (++)

instance MultiParamTypeClasses Int String where
  m = (flip $ (++) . show) . show

main :: IO ()
main = do
  print $ m "123" "456" -- 不再需要返回值类型标注
  print $ m (123 :: Int) 456
```

在指定类型参数依赖关系时，需要保证类型依赖关系与方法签名相匹配，否则依然需要指定返回类型标注：

```hs
{-# LANGUAGE FlexibleInstances, MultiParamTypeClasses, FunctionalDependencies #-}

class MultiParamTypeClasses a b | b -> a where
  m :: a -> a -> b -- 方法参数类型与类型依赖关系不符，依赖关系中定义类型"a"由类型"b"推导

instance MultiParamTypeClasses String String where
  m = (++)

main :: IO ()
main = print $ m "123" "456" -- 编译报错，类型依赖关系未生效
```

编译时得到错误信息：

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

对于使用了functional dependencies特性的type class而言，添加instance时，
类型依赖路径相同的实例仅能存在一个，否则编译报错。
示例：

```hs
class MultiParamTypeClasses a b | a -> b where
  m :: a -> a -> b

-- 编译报错，存在两个类型依赖路径冲突的实例
instance MultiParamTypeClasses String String where m = (++)
instance MultiParamTypeClasses String Int where m = (flip $ (+) . read) . read
```

编译时得到的错误信息：

```hs
Functional dependencies conflict between instance declarations:
  instance MultiParamTypeClasses String String
    -- Defined at ...
  instance MultiParamTypeClasses String Int
    -- Defined at ...
```

在该例子中，`instance MultiParamTypeClasses String String`的类型依赖`String -> String`与`instance MultiParamTypeClasses String Int`的类型依赖`String -> Int`存在冲突(都是`String -> ?`)，
两个实例声明的方法签名`m :: String -> String -> String`与`m :: String -> String -> Int`存在调用歧义(需要依赖返回值确定实际调用者)，
不使用functional dependencies特性时正常通过编译，启用functional dependencies特性时则编译报错。



# Monad
`Monad`是Haskell、Scala等函数式语言中用于构建复杂计算逻辑的抽象。

Monad类型的继承关系：

```
Functor => Applicative => Monad
```

- `Functor`

	定义：

	```hs
	class Functor (f :: * -> *) where
	  fmap :: (a -> b) -> f a -> f b
	  (<$) :: a -> f b -> f a
	  {-# MINIMAL fmap #-}
	  	-- Defined in ‘GHC.Base’
	```

	Functor类型至少需要实现`fmap`函数，fmap需要提供参数类型之间的直接变换逻辑。

	Functor满足如下规则：

	```hs
	fmap id == id
	fmap (f . g) == fmap f . fmap g
	```

- `Applicative`

	定义：

	```hs
	class Functor f => Applicative (f :: * -> *) where
	  pure :: a -> f a
	  (<*>) :: f (a -> b) -> f a -> f b
	  (*>) :: f a -> f b -> f b
	  (<*) :: f a -> f b -> f a
	  {-# MINIMAL pure, (<*>) #-}
	  	-- Defined in ‘GHC.Base’
	```

	Applicative类型至少需要实现`pure`和`<*>`操作符。
	pure函数定义参数类型到Applicative的构造逻辑。
	<*>操作符作用与fmap类似，但参数类型的变换逻辑包装在在Applicative类型中。

- `Monad`

	定义：

	```hs
	class Applicative m => Monad (m :: * -> *) where
	  (>>=) :: m a -> (a -> m b) -> m b
	  (>>) :: m a -> m b -> m b
	  return :: a -> m a
	  fail :: String -> m a
	  {-# MINIMAL (>>=) #-}
	  	-- Defined in ‘GHC.Base’
	```

	Monad类型至少需要实现`>>=`操作符。
	`>>=`操作符需要提供源参数类型生成包含目标参数类型的Monad的变换逻辑。
	`>>=`操作顺序地组合两个动作，将前一个动作的处理结果做为参数传递给后一个。

	`>>`操作符用于将返回值无关的Monad操作相连。
	`>>`操作顺序地组合两个动作，但丢弃前一个动作的处理结果，类似于命令式语言(imperative languages)中的分隔符，比如C中的分号。

	`return`函数提供参数类型到Monad的构造逻辑，由于Monad是Applicative子类，return默认使用pure函数做为实现。

Monad实例应遵循下列规则：

```hs
return a >>= k = k a
m >>= return = m
m >>= (\x -> k x >>= h) = (m >>= k) >>= h
```

Monad与Applicative操作符应遵循下列规则：

```hs
pure = return
(<*>) = ap
```

这些规则可推导出：

```hs
fmap f xs = xs >>= return . f
(>>) = (*>)
```

Haskell标准库中Monad的实例类型如`[]`、`Maybe`、`IO`等均遵循以上规则。

## do 语法
Haskell中提供了Monad的语法糖，使用do关键字能够以更接近命令式语言的语法操作Monad。

以常见的`IO Monad`为例：

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

使用do语法糖可以改写为：

```hs
-- 使用do语法糖更类似C语言的命令式风格，逻辑更易理解
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
`GHC 8.0.1`开始提供了针对Applicative类型的do语法糖语言扩展：

```hs
{-# LANGUAGE ApplicativeDo #-}
```

实例：

```hs
data App a = App {
  app :: a
} deriving (Eq, Show)

instance Functor App where
  fmap = (App.) . (.app)

instance Applicative App where
  pure = App
  (<*>) = flip (flip (App.) . app) . app

-- 原始 Applicative 类型运算逻辑
app1 = (App.) . (flip $ (++) . show) <$> App "abc" <*> App 1

-- 使用 ApplicativeDo 扩展后的等价语法糖表示
app2 = do
  a <- App "abc"
  b <- App 2
  return $ a ++ (show b) -- 亦可使用 pure 函数
```

## Control.Monad
`Control.Monad`模块中提供了Monad的常用变换操作。

- `mapM`/`forM`/`mapM_`/`forM_`

	mapM函数定义在Traversable类型中，函数对Foldable类型的每个元素执行参数给定的单子操作(monadic action)，
	从左向右收集结果，并将结果集包装到单个Monad中。
	forM函数功能与mapM相同，仅参数位置不同。
	函数定义：

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

	mapM_/forM_是对应函数的无结果版本，做为返回值的Monad参数类型固定为空元组`()`。
	函数定义：

	```hs
	mapM_ :: (Foldable t, Monad m) => (a -> m b) -> t a -> m ()
	        -- Defined in ‘Data.Foldable’

	forM_ :: (Foldable t, Monad m) => t a -> (a -> m b) -> m ()
	        -- Defined in ‘Data.Foldable’
	```

	mapM_/forM_常用于处理不关注返回值副作用操作(IO Monad)。
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

	replicateM函数执行指定次数的单子操作，将结果以数组形式保存在单个Monad中；
	replicateM_函数是对应的无返回结果版本。
	forever函数则无限地执行给定的单子操作。
	函数定义：

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

	forever、replicateM等循环函数可使用`fail`、`error`等函数通过抛出异常的方式提前结束循环。
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

	sequence函数从左向右执行Traversable结构中的每个单子操作，收集结果并包装在Monad结构中做为返回值。
	sequence_函数是sequence的无结果版本。
	函数定义：

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
	Prelude Control.Monad> sequence [actionA, actionB, actionC] -- 执行后产生副作用，并生成结果
	"Action A"
	"Action B"
	"Action C"
	["A","B","C"]
	Prelude Control.Monad> sequence_ [actionA, actionB, actionC] -- 执行后仅产生副作用，结果为空
	"Action A"
	"Action B"
	"Action C"
	```

- `=<<`/`>=>`/`<=<`

	`=<<`函数与`>>=`相同，仅参数位置不同。
	`>=>`函数用于从左向右组合Monad操作，`<=<`函数用于从右向左组合Monad操作。
	函数定义：

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
`STM`全称`Software Transactional Memory`(软件事务内存)，是一种对并发通信的模块化(modular)、可组合(composable)的抽象。
相对与锁/MVars，STM能够在不暴露抽象如何保证安全性细节的前提下，简单地与其它使用STM的抽象相组合。

## STM 概念
在经典的并发编程模型中，对于共享变量进行跨线程的修改通常需要通过加锁保证数据的读写一致性，
然而常规的基于锁的并发模型对于开发者而言有较大的心智负担，对锁的不当操作会引起死锁等问题。

在STM模型下，将具有逻辑依赖关系的多个共享变量读写操作组合成一个事务，
当一个线程内的事务操作开始时，操作的影响并不会立即对其它线程可见，直到该事务内部的所有操作完成；
当事务操作完成时，会产生以下两种结果：

1. 没有其它线程修改了相同的共享变量，当前线程的事务操作结果会对其它线程可见。
1. 否则当前线程的操作会被丢弃，然后该事务会被重新执行。

事务操作具有隔离性(isolated)，以此来规避锁问题。

## STM API 介绍
`Control.Monad.STM`模块提供了STM结构定义和Monad变换操作；
`Control.Concurrent.STM`模块提供了STM相关容器的实现。

`Control.Monad.STM`内的`atomically`函数提供了对STM操作的原子执行，
`retry`函数用于重试STM操作，相关API定义：

```hs
-- 原子化地执行一系列STM操作
atomically :: STM a -> IO a

-- 重试STM操作
-- 在GHC的实现中，会阻塞STM操作线程，直至读取的共享变量已被更新
retry :: STM a

-- 检测给定的Bool条件，不满足则重试STM操作(retry)
check :: Bool -> STM ()

-- 在STM操作中抛出和捕获异常
throwSTM :: Exception e => e -> STM a
catchSTM :: Exception e => STM a -> (e -> STM a) -> STM a
```

STM实现了Monad，因而多个STM操作之间可简单地相互组合。

`Control.Concurrent.STM`模块中提供了常见的基于STM的共享变量容器：

| API | 简介 |
| :- | :- |
| Control.Concurrent.STM.TVar | 最常用的STM共享变量容器，保存单个对象 |
| Control.Concurrent.STM.TMVar | MVar的对应STM版本，可用作条件变量 |
| Control.Concurrent.STM.TArray | MArray的对应STM版本 |
| Control.Concurrent.STM.TChan | FIFO形式的数据通道 |
| Control.Concurrent.STM.TQueue | 数据队列，与TChan类似，具有更高的吞吐速率，但不支持复制 |
| Control.Concurrent.STM.TBQueue | 数据队列，与TQueue类似，但具有固定数据数目上限 |

## TVar
`Control.Concurrent.STM.TVar`用于存储单个共享变量，是最简单、基础的API，
支持对共享变量的读、写、修改操作。

核心API定义如下：

```hs
-- 使用参数中给定的值创建TVar
newTVar :: a -> STM (TVar a)
-- 创建TVar，保存在IO Monad中，通常用在外层IO方法中
newTVarIO :: a -> IO (TVar a)

-- 读取TVar
readTVar :: TVar a -> STM a
-- readTVar的IO版本，等价于 atomically . readTVar
readTVarIO :: TVar a -> IO a

-- 写入TVar，有多种修改方式
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
  printValue ("TVar " ++ i ++ " [" ++ (show threadId) ++ "]:") a b

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

输出结果：

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

在STM操作下，数据的加减操作为原子操作执行；
由输出结果可知，多个线程之间的数据修改操作并未影响数据一致性。

## TChan
`Control.Concurrent.STM.TChan`是FIFO的数据管道，向管道中写入数据，可从管道中按对应顺序读取。

核心API如下：

```hs
-- 创建数据管道
newTChan :: STM (TChan a)
newTChanIO :: IO (TChan a)

-- 从管道中取出一条数据，取出的数据在管道中会被移除
readTChan :: TChan a -> STM a
-- 从管道中读取一条数据，读取的数据不被管道移除
peekTChan :: TChan a -> STM a

-- 向管道中写入数据，数据被加入管道末尾
writeTChan :: TChan a -> a -> STM ()
-- 向管道中写入数据，数据被加入管道前端，该数据会立即被下次读取操作获取
unGetTChan :: TChan a -> a -> STM ()
```

数据管道简单示例：

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
        print $ "Receive [" ++ (show threadId) ++ "]: " ++ receive
        threadDelay 500000
```

输出结果：

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

TChan支持数据广播，创建广播管道并多次复制该管道，向广播管道中写入数据，每个复制出的管道都会收到相同数据，
以此实现数据的广播发送，相关API如下：

```hs

-- 创建广播管道，广播管道只能写入不能读取(服务端)，仅能通过dupTChan/cloneTChan函数复制出新管道读取数据
newBroadcastTChan :: STM (TChan a)
newBroadcastTChanIO :: IO (TChan a)

-- 复制数据管道，复制出的管道仅能读取数据，不能写入(客户端)
dupTChan :: TChan a -> STM (TChan a)
cloneTChan :: TChan a -> STM (TChan a)
```

newTChan函数创建的普通管道会一直缓存写入的数据直到数据从管道中被取出；
newBroadcastTChan函数创建的广播管道写入数据时在数据抵达客户端后即可被垃圾收集。

广播数据管道示例：

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
        print $ "Receive [" ++ (show threadId) ++ "]: " ++ receive
```

输出结果；

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
`GADTs`(Generalized Algebraic Datatypes，广义代数数据类型)，是ADT的泛化版本，
允许显式地指定ADT定义中每个构造器的类型。

## ADT 的限制
普通的ADT类型中，无法显式指定每个构造器的返回值类型。
定义一个代表表达式的类型，如下所示：

```hs
data Expr a =
  Num a | Bool a |
  Add (Expr a) (Expr a) |
  Eq (Expr a) (Expr a) deriving (Show, Eq)
```

`Expr`类型拥有四个构造器，每个构造器返回类型均为`Expr a`，由于构造器类型相同，在特定组合下会造成语义冲突：

```hs
-- Num构造器不应使用文本做为参数
Num "Test"
-- Bool构造器应该仅接收Bool类型
Bool 666

-- Bool构造器不应做为Add的参数，但ADT无法做到精确的类型限制
Add (Bool True) (Bool False)
```

## 使用 GADT
使用GADT需要开启对应语言扩展：

```hs
{-# LANGUAGE GADTs #-}
```

GADT可以指定每个构造器的签名：

```hs
data Expr a where
  Num :: Num a => a -> Expr a -- 限制参数类型必须实现 Type Class Num
  Bool :: Bool -> Expr Bool -- 指定参数类型为Bool型
  Add :: Num a => Expr a -> Expr a -> Expr a
  Eq :: Eq a => Expr a -> Expr a -> Expr Bool
```

各个构造器都添加对应了类型约束，因此下列语句无法通过编译：

```hs
-- 参数类型[Char]未实现TypeClass
Num "Test"
-- Bool构造器应该仅接收Bool类型
Bool 666

-- 编译器输出错误信息：
-- ? No instance for (Num Bool) arising from a use of ‘Add’
-- ? In the expression: Add (Bool True) (Bool False)
Add (Bool True) (Bool False)
```



# Type Families
GHC提供了`Type Families`扩展，支持对数据类型的点对点重载(supporting ad-hoc overloading of data types)。

type families是参数化的类型，可根据实例化的类型参数分配特定的表示。
type families用途与type classes类似，type classes用于定义可重载的方法，type families则用于定义可重载的数据类型。

type families适用于以下场景：

- 泛型编程(for generic programming)
- 创建高度参数化的库接口(for creating highly parameterised library interfaces)
- 创建带有额外静态信息的接口，如依赖类型(for creating interfaces with enhanced static information, much like dependent types)

type families拥有两种形式：`data families`和`type synonym families`。

使用type families需要开启对应语言扩展：

```hs
{-# LANGUAGE TypeFamilies #-}
```

## Data Families
data families是type families特性用在数据类(data types)的情形，包含以下用法：

- 在顶层代码使用：

	在顶层代码中使用时，使用`data family`关键字定义类型族，
	使用`data instance`/`newtype instance`关键字定义类型族的成员。

	data families用于顶层代码时，作用一定程度上类似于GADT，能够为带有泛型参数的数据类的每种构造器指定具体的类型。
	示例：

	```hs
	data family Family a
	newtype instance Family Int = FInt Int  -- 构造器单参数时可使用newtype关键字
	data instance Family String = FString (Family Int) String -- 构造器中的参数可依赖具体的类型族中的其它实例
	data instance Family (Maybe a) = FJust a | FNothing deriving (Show, Eq) -- 每个instance可以deriving各自的TypeClass
	```

	`TypeFamilies`与`GADTs`扩展同时使用时，可直接使用类似GADT的语法定义每个构造器的函数签名。
	示例：

	```hs
	data family Expr a
	data instance Expr a where
	  Num :: Num a => a -> Expr a
	  Bool :: Bool -> Expr Bool
	  Add :: Num a => Expr a -> Expr a -> Expr a
	  Eq :: Eq a => Expr a -> Expr a -> Expr Bool
	```

	data families与GADT的比较：

	- data families与GADT均能定义每个构造器的参数表与返回类型，
	但GADT需要将所有构造器集中在一处(where子句中)，data families支持分离定义。
	- GADT的每个构造器均能用于通用的模式匹配，data families的构造器仅能针对对应实例类型匹配。

- 在type classes内部使用：

	在type classes内部使用时，用于定义未实现的抽象类型，语法上不必添加family关键字；
	在实现带有data families的type classes时，instance必须定义抽象类型的构造器。
	示例：

	```hs
	class TypeClass a where
	  data Family a

	instance TypeClass Int where
	  data Family Int = FInt Int -- 为抽象类型定义构造器

	instance TypeClass [a] where
	  data Family [a] = FList [a] | FNil

	...
	```

## Type Synonym Families
type synonym families扩展了type关键字定义类型别名的用法，包含以下用法：

- 在顶层代码使用：

	顶层代码中的type synonym families扩展了类型别名的功能。
	普通的类型别名仅能指代一种类型(无论别名是否带有类型参数)；
	type synonym families则强制要求别名带有类型参数，同时别名在搭配不同的类型参数时可指代不同的实际类型。

	使用`type family`关键字定义同义类型族，使用`type instance`定义类型族成员。
	示例：

	```hs
	type family Family a
	type instance Family String = String
	type instance Family Int = Int
	type instance Family (Maybe a) = Maybe a
	... -- 可任意追加其它instance，避免定义 Family a 这样的类型，会与其它instance冲突
	```

	普通的type synonym families是开放式的，可以任意添加成员(追加新的type instance)，
	type synonym families亦支持类似GADT语法的封闭式(closed)定义，
	将所有的类型族成员定义在where子句内部，不再能从外部扩展。
	示例：

	```hs
	-- 类型族仅包含where子句中列出的成员，不能扩展
	type family Family a where
	  Family [a] = [a]
	  Family String = String
	  Family Int = Int
	  Family (Maybe a) = Maybe a
	```

- 在type classes内部使用：

	在type classes内部使用时，语法上同样不需要使用`family`；
	功能上相当于添加了一个额外的类型参数，创建对应instance时，需要指定对应的实际类型。
	示例：

	```hs
	class TypeClass a where
	  type Family a

	instance TypeClass Int where
	  type Family Int = Int -- 实现instance时指定具体的类型

	instance TypeClass [a] where
	  type Family [a] = [a]

	...
	```

	在type classes内部使用type synonym families，能够替代functional dependencies特性：

	```hs
	-- 使用 functional dependencies
	class Collects c e | c -> e where
	  empty  :: c
	  insert :: e -> c -> c
	  member :: e -> c -> Bool
	  toList :: c -> [e]

	-- 等价于使用 type synonym families
	class Collects c where
	  type Elem c
	  empty  :: c
	  insert :: Elem c -> c -> c
	  member :: Elem c -> c -> Bool
	  toList :: c -> [Elem c]
	```

## Type Families Kind
使用`data family`、`type family`关键字定义类型族时，可追加可选的Kind签名。

未显式指定Kind时，默认Kind为`*`：

```hs
-- 常规 type families 定义
data family DataFamily a
type family TypeFamily a

-- 等价于以下定义：
data family DataFamily a :: *
type family TypeFamily a :: *

-- 在 type classes 中的定义类似
class TypeClass a where
  data DataFamily a
  type TypeFamily a

-- 等价于以下定义：
class TypeClass a where
  data DataFamily a :: *
  type TypeFamily a :: *
```

使用显式Kind定义：

```hs
-- 接收单个类型参数
data family KindA1 a
-- 使用 Kind 声明
data family Kind1 :: * -> *

-- 接收两个类型参数
data family KindAB2 a b
-- 使用 Kind 声明
data family Kind2 :: * -> * -> *
-- 同时使用类型参数和 Kind 声明
data family KindA2 a :: * -> *

-- 依此类推
...
```

在同时使用显式Kind定义和类型参数时，类型的实际Kind由二者共同决定(相加)：

```hs
-- 实际 Kind 为 * -> * -> * -> * ，最大可接收三个类型参数
data family Kind3 a b :: * -> *

-- 实际 Kind 为 * -> * -> * -> * -> * ，最大可接收四个类型参数
data family Kind4 a :: * -> * -> * -> *

-- 实际 Kind 为 * -> * -> * -> * -> * -> * ，最大可接收五个类型参数
data family Kind5 a b c :: * -> * -> *

-- 依此类推
...
```

在使用类型时，显式命名的类型参数不可省略，Kind声明部分的Kind类型参数可选：

```hs
data family Kind a b :: * -> * -- 使用该类型时，a、b两个显式命名的类型参数不可省略

Kind Int Int -- 正确，Kind为 * -> *
Kind Int Int Int -- 正确，Kind为 *
Kind IO Int -- 错误，首个类型类型参数的Kind不匹配
Kind Int -- 错误，缺失第二类型参数
```



# Concurrent
`Control.Concurrent`中提供了Haskell的公用异步抽象。

## Async 包
`async`包提供跨多线程执行异步操作的功能。
async包底层使用base包中的`forkIO`函数(在`Control.Concurrent`模块中)实现，提供了以下改进：

- 彻底、优雅地处理异常(graceful and thorough handling of exceptions)
- 从子线程中获取返回值
- 提供`STM`接口用于访问线程返回值，STM提供了方便的方式处理诸如阻塞操作等待结果等问题
- 使得取消线程变得简单和可靠
- 对于某些通用的用例，`race`、`concurrently`函数和`Concurrently`类型可以大幅简化代码

`Async`是async包的主要数据类型，一个`Async a`类型的值表示一个分离的线程(represents a separate thread)，
该线程将最终生成一个`a`类型的值(which will ultimately generate a value of type `a`)。

async包相关API位于`Control.Concurrent.Async`模块下，主要API介绍：

- `async*`系列函数fork一个线程并返回Async值，`wait*`系列函数等待Async类型返回结果。

	```hs
	-- 异步执行一个操作
	async :: IO a -> IO (Async a)

	-- 阻塞线程，等待一个异步操作执行结束并获取结果
	wait :: Async a -> IO a
	-- 等待异步结果，并处理异常
	waitCatch :: Async a -> IO (Either SomeException a)

	-- 等待多个操作，任意一个异步操作完成时返回
	waitEither :: Async a -> Async b -> IO (Either a b)
	waitAny :: [Async a] -> IO (Async a, a)

	-- 等待两个异步操作全部返回
	waitBoth :: Async a -> Async b -> IO (a, b)
	```

	基本的异步操作示例：

	```hs
	import Control.Concurrent
	import Control.Concurrent.Async

	actionN :: Int -> IO String
	actionN num = do
	  let n = show num
	  print $ "Action" ++ n ++ " start..."
	  threadDelay 1000000 -- 暂停线程 1s
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

	执行结果：

	```
	"Action1 start..."
	"After action1"
	"After action2"
	"Action2 start..."
	"Action1 finished..."
	"Action2 finished..."
	"Finish: 1 2"
	```

- `withAsync*`函数启动一个独立线程执行首个参数中传入的操作，并提供Async值给匿名函数(第二参数)。

	```hs
	withAsync :: IO a -> (Async a -> IO b) -> IO b
	```

	withAsync函数是async函数的一类有用的变体，能够确保异步操作不会意外地执行(启动的线程在匿名函数执行结束后被杀死)。

	示例：

	```hs
	import Control.Concurrent
	import Control.Concurrent.Async

	actionN :: Int -> IO String
	actionN num = do
	  let n = show num
	  print $ "Action" ++ n ++ " start..."
	  threadDelay 1000000 -- 暂停线程 1s
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

	输出结果：

	```
	"WithAsync start..."
	"Action1 start..."
	"Action1 finished..."
	"WithAsync finished: 1"
	"Main finished: 2333"
	```

- `poll`函数用于检查Async类型操作是否完成，`cancel`函数用于提前取消异步操作，`asyncThreadId`用于查看线程ID。

	```hs
	-- 检查一个异步操作是否完成
	poll :: Async a -> IO (Maybe (Either SomeException a))

	-- 取消一个异步操作
	cancel :: Async a -> IO ()
	cancelWith :: Exception e => Async a -> e -> IO ()

	asyncThreadId :: Async a -> ThreadId
	```

- `*STM`系列函数是对应异步操作的STM接口版本。

	```hs
	pollSTM :: Async a -> STM (Maybe (Either SomeException a))

	-- wait系列API均有对应STM版本
	waitSTM :: Async a -> STM a
	waitAnySTM :: [Async a] -> STM (Async a, a)
	waitCatchSTM :: Async a -> STM (Either SomeException a)
	...
	```



# RankNTypes
GHC的类型系统支持任意等级(arbitrary-rank)的显式类型量化(explicit universal quantification in types)。

使用RankNTypes需要开启对应语言扩展：

```hs
{-# LANGUAGE RankNTypes #-}
```

使用RankNTypes扩展后可使用`forall`关键字定义函数参数表的多态层次。

Haskell标准语法中函数参数表默认即为`rank-1 types`，如：

```hs
f1 :: a -> b -> a
g1 :: (Ord a, Eq  b) => a -> b -> a
```

等价于使用forall关键字描述的参数表：

```hs
f1 :: forall a b . a -> b -> a
g1 :: forall a b . (Ord a, Eq  b) => a -> b -> a
```

使用forall可以在参数表中定义更多多态层级：

```hs
f2 :: (forall a . a -> a) -> Int -> Int
g2 :: (forall a . Eq a => [a] -> a -> Bool) -> Int -> Int

f3 :: ((forall a . a -> a) -> Int) -> Bool -> Bool

f4 :: Int -> (forall a . a -> a)
```

函数`f2`、`g2`为`rank-2 types`，f2/g2函数在函数箭头左端拥有局部的forall参数表，参数表内部的多态类型能够重载。
函数`f3`为`rank-3 types`，f3函数在函数箭头左端拥有一个`rank-2 types`的局部forall参数表。

## 示例
RankNTypes常用于函数的部分参数自身为多态函数的情况下，考虑如下函数：

```hs
rankNTypes :: (Show a, Show b) =>
  (Show ? => ? -> String) -> a -> b -> IO ()
rankNTypes f a b = do
  let (fa, fb) = (f a, f b)
  print $ "a: " ++ fa ++ " b: " ++ fb
```

rankNTypes的参数`f`是一个函数，该函数应能接收`a`或`b`类型的参数(多态)并返回String类型，
满足要求的f参数类型(使用`?`标识)在标准Haskell语法下没有合适的表达方式。

使用RankNTypes扩展即可满足需求：

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

使用了RankNTypes扩展，函数f拥有了独立的多态层次(rank-2 types)，能够接收多态参数。
