<!-- TOC -->

- [Haskell 开发环境](#haskell-开发环境)
	- [GHC 常用功能](#ghc-常用功能)
- [高阶函数](#高阶函数)
	- [$ 和 .](#-和-)
	- [<$>](#)
	- [<*>](#)
	- [foldl/foldr](#foldlfoldr)
- [Monad](#monad)

<!-- /TOC -->



## Haskell 开发环境
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

### GHC 常用功能
`Haskell`源码后缀为`*.hs`，使用`ghc`指令编译`Haskell`代码：

```
$ ghc *.hs
```

`GHC`编译器会直接将`Haskell`源码编译为对应平台的二进制文件。

使用`ghci`会进入交互式`REPL`。  
`ghci`提供了交互式的`GHC`环境，可以直接输入代码并立即获得反馈。  
如下所示：

```hs
$ ghci
Configuring GHCi with the following packages:
GHCi, version 8.0.2: http://www.haskell.org/ghc/  :? for help
Prelude> print "Hello World"
"Hello World"
Prelude> :quit
Leaving GHCi.
```



## 高阶函数
`Haskell`作为函数式语言，标准库中内置了常用的高阶函数。

### $ 和 .
`$`，常用于消除函数中的括号，函数定义：

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

### <$>
`<$>`，对一个`Functor`执行提供的操作，函数定义：

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

### <*>
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

### foldl/foldr
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



## Monad
`Monad`是Haskell、Scala等函数式语言中用于构建复杂计算逻辑的抽象。  
Monad定义：

```hs
class Applicative m => Monad (m :: * -> *) where
  (>>=) :: m a -> (a -> m b) -> m b
  (>>) :: m a -> m b -> m b
  return :: a -> m a
  fail :: String -> m a
  {-# MINIMAL (>>=) #-}
  	-- Defined in ‘GHC.Base’
```

`Applicative`定义：

```hs
class Functor f => Applicative (f :: * -> *) where
  pure :: a -> f a
  (<*>) :: f (a -> b) -> f a -> f b
  (*>) :: f a -> f b -> f b
  (<*) :: f a -> f b -> f a
  {-# MINIMAL pure, (<*>) #-}
  	-- Defined in ‘GHC.Base’
```

`Functor`定义：

```hs
class Functor (f :: * -> *) where
  fmap :: (a -> b) -> f a -> f b
  (<$) :: a -> f b -> f a
  {-# MINIMAL fmap #-}
  	-- Defined in ‘GHC.Base’
```

Monad类型的继承关系：

```
Functor => Applicative => Monad
```
