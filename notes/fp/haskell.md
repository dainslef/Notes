- [Haskell 开发环境](#haskell-开发环境)
	- [GHC 常用功能](#ghc-常用功能)
	- [REPL (GHCi)](#repl-ghci)
- [高阶函数](#高阶函数)
	- [$ 和 .](#-和-)
	- [<$>](#)
	- [<*>](#)
	- [foldl/foldr](#foldlfoldr)
- [Monad](#monad)



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



# 高阶函数
Haskell作为函数式语言，标准库中内置了常用的高阶函数。

## $ 和 .
`$`常用于消除函数中的括号，函数定义：

```hs
($) ::
  forall (r :: GHC.Types.RuntimeRep) a (b :: TYPE r).
  (a -> b) -> a -> b
  	-- Defined in ‘GHC.Base’
infixr 0 $
```

`.`用于组合两个函数，函数定义：

```hs
(.) :: (b -> c) -> (a -> b) -> a -> c 	-- Defined in ‘GHC.Base’
infixr 9 .
```

## <$>
`<$>`，对一个`Functor`执行提供的变换操作，将Functor中参数类型变换为另一种类型。
函数定义：

```hs
(<$>) :: Functor f => (a -> b) -> f a -> f b
  	-- Defined in ‘Data.Functor’
infixl 4 <$>
```

示例：

```hs
Prelude> (+1) <$> [1, 2, 3]
[2,3,4]
```

## <*>
`<*>`，函数定义：

```hs
class Functor f => Applicative (f :: * -> *) where
  ...
  (<*>) :: f (a -> b) -> f a -> f b
  ...
  	-- Defined in ‘GHC.Base’
infixl 4 <*>
```

示例：

```hs
Prelude> [(+1)] <*> [1, 2, 3]
[2,3,4]
Prelude> [(+1), (+2)] <*> [1, 2, 3]
[2,3,4,3,4,5]
```

## foldl/foldr
`foldl/foldr`用于叠加数据，函数定义：

```hs
class Foldable (t :: * -> *) where
  ...
  foldl :: (b -> a -> b) -> b -> t a -> b
  foldr :: (a -> b -> b) -> b -> t a -> b
  ...
  	-- Defined in ‘Data.Foldable’
```

示例：

```hs
Prelude> foldl (+) 0 [1, 2, 3]
6
Prelude> foldl (-) 0 [1, 2, 3]
-6
Prelude> foldr (-) 0 [1, 2, 3]
2
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
	`>>`操作符用于将返回值无关的Monad操作相连。
	`return`函数提供参数类型到Monad的构造逻辑，由于Monad是Applicative子类，return默认使用pure函数做为实现。
