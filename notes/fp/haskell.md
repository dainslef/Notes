- [Haskell 开发环境](#haskell-开发环境)
	- [GHC 常用功能](#ghc-常用功能)
	- [REPL (GHCi)](#repl-ghci)
- [常用函数](#常用函数)
	- [`$` 函数](#-函数)
	- [`.` 函数](#-函数)
- [Monad](#monad)
	- [do 语法](#do-语法)
	- [ApplicativeDo](#applicativedo)
	- [Control.Monad](#controlmonad)
- [GADTs](#gadts)
	- [ADT 的限制](#adt-的限制)
	- [使用 GADT](#使用-gadt)



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

## `$` 函数
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

## `.` 函数
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

## Control.Monad
`Control.Monad`包中提供了Monad的常用变换操作。

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



# GADTs
`GADTs`(Generalized Algebraic Datatypes，广义代数数据类型)，是ADT的泛化版本，
允许显式地指定ADT定义中每个构造器的类型。

## ADT 的限制
普通的ADT类型中，每个构造器的返回值类型不可指定。
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
