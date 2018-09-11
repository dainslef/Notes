- [Haskell 开发环境](#haskell-开发环境)
	- [GHC 常用功能](#ghc-常用功能)
	- [REPL (GHCi)](#repl-ghci)
- [常用函数](#常用函数)
	- [$](#)
	- [.](#)
- [Monad](#monad)
	- [do 语法](#do-语法)
	- [ApplicativeDo](#applicativedo)



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



# 常用函数
Haskell中可以使用符号做为函数名。

## $
`$`常用于消除函数中的括号，函数定义：

```hs
($) ::
  forall (r :: GHC.Types.RuntimeRep) a (b :: TYPE r).
  (a -> b) -> a -> b
  	-- Defined in ‘GHC.Base’
infixr 0 $
```

`$`函数优先级为0，因而能代替括号操作符改变操作优先级。
示例：

```hs
Prelude> print ("abc" ++ "cde") -- 使用括号改变表达式优先级，与传统命令式语言类似
"abccde"
Prelude> print $ "abc" ++ "cde" -- 使用 $ 函数改变优先级更符合Haskell代码风格
"abccde"
```

## .
`.`用于组合两个函数，函数定义：

```hs
(.) :: (b -> c) -> (a -> b) -> a -> c 	-- Defined in ‘GHC.Base’
infixr 9 .
```



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

- `return a >>= k = k a`
- `m >>= return = m`
- `m >>= (\x -> k x >>= h) = (m >>= k) >>= h`

Monad与Applicative操作符应遵循：

- `pure = return`
- `(<*>) = ap`

这些规则意味着：

- `fmap f xs = xs >>= return . f`
- `(>>) = (*>)`

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
`GHC 8.0.1`后提供了针对Applicative类型的do语法糖语言扩展：

```hs
{-# LANGUAGE ApplicativeDo #-}
```

实例：

```hs
data App a = App {
  valueA :: a
} deriving (Eq, Show)

instance Functor App where
  fmap f fa = App $ f $ valueA fa

instance Applicative App where
  pure a = App a
  fab <*> fa = App $ valueA fab $ valueA fa

-- 原始 Applicative 类型运算逻辑
app1 = (\a b -> App $ a ++ (show b)) <$> App "abc" <*> App 1

-- 使用 ApplicativeDo 扩展后的等价语法糖表示
app2 = do
  a <- App "abc"
  b <- App 2
  return $ a ++ (show b) -- 亦可使用 pure 函数
```
