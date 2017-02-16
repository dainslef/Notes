[TOC]

## *Go* 安装与配置
从`Go`官网`https://golang.org/dl/`下载对应版本的`Go`编译器。

- 对于`Windows`平台，推荐直接下载免安装的`zip`版本。
- 对于`Linux`以及`macOS`平台，推荐直接使用对应平台的包管理器直接安装。

### 环境变量
完成编译器安装后，需要配置`Go`开发环境。
设置以下环境变量：

- `GOROOT` `Go`编译器所在目录
- `GOPATH` `Go`项目工作目录，可以添加多个路径

`Go`编译器会根据平台类型自动设置以下环境变量：

- `GOOS` 操作系统
- `GOARCH` CPU架构

### 目录结构
`Go`项目需要建立在工作区`GOPATH`内，工作区通常会有下列文件夹：

- `$GOPATH/src` 存放项目源码
- `$GOPATH/pkg` 存放编译后的库文件
- `$GOPATH/bin` 存放编译后的可执行文件

其中，`$GOPATH/pkg`、`$GOPATH/bin`会在执行工程构建操作时自动创建，而`$GOPATH/src`需要手动创建。

路径表示
> 在`Windows`系统中，路径使用`\`(正斜杠)连接；在`Unix`中，路径使用`/`(反斜杠)连接。
> 但在`Go`语言中，不论在`Windows`还是`Unix`平台，都应使用`/`(反斜杠)连接路径。

### 编译器工具
相比其它编程语言，`Go`提供了完善的工具链，常见工具如下：

- `gofmt` 代码格式化工具，将`Go`代码格式化为标准风格
- `golint` 代码风格检查工具，会给出一些最佳实践指引(如命名风格，代码逻辑等)
- `go vet` 代码质量检查工具，相比`golint`能够检测代码中的潜在问题，如无用的赋值、错误的`Printf`格式化参数等
- `goimports` 检查包引用错误



## 项目构建
`Go`语言构建相关工具：

- `go build` 编译源码，构建项目，生成二进制文件
- `go install` 编译源码，构建项目，生成二进制文件并安装到`$GOPATH`下的对应标准目录
- `go run` 直接执行源码文件并输出结果(源码需要包含`main()`方法)

假设存在以下目录结构：

```
???
└── testgo
	├── main
	│	└── test_main.go
	└── lib
		└── test_lib.go
```

路径`testgo/main`下存在包含`main()`方法的源码文件`test_main.go`：

```go
package main

import "fmt"

func main() {
	fmt.Println("Hello World!")
}
```

路径`testgo/lib`下存在普通源码文件`test_lib.go`：

```go
package lib

import "fmt"

func ShowHello() {
	fmt.Println("Hello World!")
}
```

### 构建当前路径中的工程
默认情况下，`go build`会将当前目录视为工程目录。

编译存在`main()`方法的工程
> 若当前目录中存在定义了`main()`方法的`Go`源码文件，则会在当前目录生成与目录名称相同可执行文件。
>
> 在`Windows`系统下，可执行文件会以`exe`做为后缀，在`Linux`/`macOS`/`BSD`中，生成的二进制文件无后缀。
>
> 举例：
>> 若当前目录为`testgo/main`，则：
>>
>>	- 执行`go build`指令，在当前路径下会生成`main.exe`文件(以`Windows`环境为例，下同)。
>>	- 执行`go install`指令，在`$GOPATH\bin`下生成`main.exe`文件。

编译无`main()`方法的工程
> 若当前目录中仅包含无`main()`方法的普通`Go`源码文件，则该，则执行`go build`文件不会直接生成内容。
>
> 举例：
>> 若当前目录为`testgo/lib`，则：
>>
>>	- 执行`go build`指令，无文件生成。
>>	- 执行`go install`指令，在`$GOPATH/pkg/[平台类型]/testgo`下生成`lib.a`文件。

### 构建指定路径工程
若当前目录位于`$GOPATH/src`或其某个子目录中，则可直接使用路径名称在任意当前路径构建该工程，并在当前路径下生成以**最后一级**目录为名称的可执行文件。
指令格式如下所示：

```sh
go build [路径名称]
go install [路径名称]
```

举例：
> 若`testgo`处于`$GOPATH/src`中，如下所示：
>
>	```
>	$GOPATH\src
>	└── testgo
>		├── main
>		│	└── test_main.go
>		└── lib
>			└── test_lib.go
>	```
>
> 则在任意工作目录皆可直接构建工程：
>
>	- 执行`go build testgo/main`指令，在当前目录生成`main.exe`文件。
>	- 执行`go install testgo/main`指令，在`$GOPATH/bin`下生成`main.exe`文件。
>	- 执行`go build testgo/lib`指令，无文件生成。
>	- 执行`go install testgo/lib`指令，在`$GOPATH/pkg/[平台类型]/testgo`下生成`lib.a`文件。



## 包结构
`Go`语言使用`package`做为命名空间隔离：

- 引用`package`时，包路径对应从`$GOPATH/src`为起始位置的磁盘物理存储路径。
- 声明`package`时，只需要使用自身所处**当前一级**路径的名称，不必且不能使用完整路径。
- 除了`main`包外，按照`Go`语言约定，所有的包声明应与其源码文件当前目录名称相同。

例如，包路径为`testgo.test`，则源码在磁盘中的物理存储路径则应为`$GOPATH/src/testgo/test/*.go`，源码的包声明应为`package test`。

包路径内的源码文件的文件名**没有**特殊限制，只需要后缀为`*.go`即可。
一个包路径下可以存放**多个**源码文件，只要这些源码文件都正确地声明了自身的包路径即可。

### 引用包
`Go`语言使用`import`关键字引用其它包。

### 引用路径
引用的包路径为从`$GOPATH/src`为起始位置的磁盘物理存储路径。

如下所示：

```go
import "testgo/test"
```

引用了磁盘路径为`$GOPATH/src/testgo/test`下的源码文件。

### 引用多个包
引用多个包时可以使用简化语法：

```go
import (
	"fmt"
	"testgo/test"
)
```

### 使用引用的包
引用了包路径下的源码后，可以使用源码中声明的包名来访问包内的内容。

如下所示，假设存在以下目录结构：

```
$GOPATH
└── src
	└── testgo
		├── main.go
		└── test
			└── xxx.go
```

源码文件`xxx.go`内容：

```go
package test

import "fmt"

func ShowXXX() {
	fmt.Println("XXX")
}
```

`main.go`文件内容：

```go
package main

import "testgo/test"

func main() {
	test.ShowXXX()		//使用"包名.*"的格式引用包内的内容
}
```

### 指定包名
在引用多个包时，可能会有不同路径的包声明了相同的包名，此时引用包内容会存在歧义，项目构建时会得到编译错误：

`xxx(包名) redeclared as imported package name previous declaration at xxx.go(源码文件名):n(行号)`

在导入包时可以显式指定包名，如下所示：

```go
import (
	std "fmt"			//将 fmt 包命名为 std
	t "testgo/test"		//将 testgo/test 包命名为 t
)
```

当一个包取别名为`.`时，可以直接使用包内的内容：

```go
package main

import . "fmt"

func main() {
	Println("xxx")		//直接使用fmt包内的函数
}
```

`Go`编码规范中**不建议**这样做(可能会造成歧义)，使用`.`做为包名时会得到以下提示：

`should not use dot imports`

### 包名与路径
在`Go`语言约定中，声明包名时，包名应与源码文件所处当前路径的名称**相同**，但实际上，包名与源码当前路径名称可以**不同**。

如下所示，假设存在以下目录结构：

```
$GOPATH
└── src
	└── testgo
		├── main.go
		└── test
			└── kkk.go
```

源码文件`kkk.go`：

```go
// 没有使用 test 做为包名
package xxx

import "fmt"

func ShowXXX() {
	fmt.Println("XXX")
}
```

`main.go`文件内容：

```go
package main

import "testgo/test"	//引用 $GOPATH/src/testgo/test 路径下的源码

func main() {
	test.ShowXXX()		//报错，不存在包"test"
	xxx.ShowXXX()		//正确
}
```

`import`关键字的作用是包含指定目录下的源码，无论包名是否与路径相同。
在访问包内的内容时，使用源码文件声明的包名即可。

需要注意的时，尽管包名可以与当前路径不同，单一个包路径下的所有源码文件声明的包名必须相同。
若一个包路径下存在多个包声明不同的源码文件，则编译时会得到以下错误：

`found packages xx包名1 (xx.go) and xxx包名 (xxx.go) in XXX(路径)`