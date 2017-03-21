## 安装和配置 *Django*
使用`pip`包管理器安装`Django`包：

`# pip install Django`

`Django`包安装完成之后，会得到`django-admin`工具用于管理django项目。

### 创建项目
使用`django-admin`工具创建一个新的django项目：

`$ django-admin startproject [项目名称]`

一个空的django项目基本文件结构如下所示：

```
项目名称
├── 项目名称
│   ├── __init__.py
│   ├── settings.py			# 项目设置
│   ├── urls.py				# 路由设置
│   └── wsgi.py
└── manage.py				# 项目的管理脚本
```

项目的根目录下是项目的管理脚本`manage.py`，可以使用该脚本完成创建应用、运行项目等功能。

项目的根目录下还会有一个与项目名称**相同**的子目录，该目录下保存项目的一些配置。

### 创建应用
与传统的WEB开发框架不同，`Django`中使用`App`将网站划分为多个功能模块，一个项目由多个`App`组成，而一个`App`可以被多个项目所复用。

同样使用`django-admin`工具在项目目录中创建一个`App`：

`$ django-admin startapp [应用名称]`

也可以执行项目管理脚本`manage.py`来创建新的`App`：

`$ ./manage.py startapp [应用名称]`

一个新创建的django应用基本文件结构如下所示：

```
应用名称
├── admin.py
├── apps.py
├── __init__.py
├── migrations
│   └── __init__.py
├── models.py
├── tests.py
└── views.py
```

使用一个应用需要在项目配置文件`settings.py`中的`INSTALLED_APPS`列表中添加引用的项目名称，如下所示：

```py
# file: [项目名称]/settings.py

INSTALLED_APPS = [
	'django.contrib.admin',
	'django.contrib.auth',
	'django.contrib.contenttypes',
	'django.contrib.sessions',
	'django.contrib.messages',
	'django.contrib.staticfiles',
	'[应用名称]'
]
```

### 运行项目
执行项目管理脚本`manager.py`，使用`runserver`参数即可运行项目：

`$ ./manager.py runserver`

默认情况下，项目运行在`8000`端口，使用`127.0.0.1:8000`即可访问运行的项目，`runserver`参数后可添加端口号指定项目运行端口：

`$ ./manager.py runserver [端口号]`

默认情况下，使用django自带的应用服务器启动的项目只能供本机进行访问(与`Tomcat`、`Jetty`不同)。
若需要使项目能够被内网的其它机器访问，则在启动时使用`0.0.0.0`作为ip：

`$ ./manager.py runserver 0.0.0.0:[端口号]`

同时在项目配置文件`settings.py`中的`ALLOWED_HOSTS`列表内添加允许的主机IP，允许所有主机访问配置如下：

```py
# file: [项目名称]/settings.py

ALLOWED_HOSTS = [
	'*'
]
```

关于`Couldn't import Django...`错误
> 在执行`./manager.py runserver`指令时，输出`Couldn't import Django...`错误，若已经正确安装了`Django`模块依然得到错误提示，则需要检查系统默认的`Python`版本。
> 若系统默认使用的`Python`与安装`Django`的`Python`版本不同，则应显式使用指定版本的`Python`解释器来执行`manager.py`脚本。
>
> 以`Python 3.6`版本为例，执行命令如下所示：
>
>	```sh
>	python3.6 manager.py runserver
>	```

### 在 *IntelliJ IDEA* 中开发 *Django* 项目
`IntelliJ IDEA`中安装了`Python`插件即可进行`Django`项目的开发。

创建项目
> 在`IntelliJ IDEA`中支持直接创建`Django`项目，创建`Python`项目时勾选`Django`支持即可。

导入项目
> 选择`Project from Existing Sources...`选项，选择已创建的`Djangp`项目的根目录。
>
> 执行项目导入步骤后会将`Django`项目转化为标准的`IDEA`项目。
> 完成导入的`Django`项目并不能立即执行，需要在以下路径配置`Django`项目的信息：
>
> `File` => `Project Structure` => `Project Settings` => `Facets` => `Django`
>
>	- `Django project root` 项目根路径
>	- `Settings` 项目的配置文件(`项目名称\settings.py`)
>	- `Manage script` 管理脚本(`manage.py`)
>
> 之后创建项目的运行配置(`Django server`)，即可执行项目。



## ORM
`Django`框架中内置了`ORM`支持，不必像`Spring MVC`、`Struct2`等框架需要使用独立的ORM框架。

### 配置数据库连接
django框架中已经内置了对主流数据库的支持，将需要使用的数据库写入项目配置文件`settings.py`的`DATABASES`字典中。

默认情况下，django使用的是`sqlite`数据库。
在创建项目的同时已经在项目目录下创建了数据库文件`db.sqlite3`并生成了对应的默认数据库配置，默认配置如下所示：

```py
# file: [项目名称]/settings.py

DATABASES = {
	'default': {
		'ENGINE': 'django.db.backends.sqlite3',
		'NAME': os.path.join(BASE_DIR, 'db.sqlite3'),
	}
}
```

使用其它数据库需要修改`DATABASES`字典中的内容，不同数据库的配置字段不尽相同。

以`MySQL`为例，配置应当写成：

```py
# file: [项目名称]/settings.py

DATABASES = {
	'default': {
		'ENGINE': 'django.db.backends.mysql',
		'NAME': '连接的数据库名称',
		'USER': '数据库账户名称',
		'PASSWORD': '数据库账户对应密码',
		'host': '主机地址',
		'port': 3306	# mysql数据库默认端口为3306
	}
}
```

对于`MySQL`数据库而言，仅仅正确配置`DATABASES`列表中的参数并不能立即完成数据库连接，还需要安装mysql数据库驱动，否则在启动项目时会出现下列错误输出：

```py
ImportError: No module named 'MySQLdb'
```

缺少`MySQLdb`模块不能连接到`MySQL`数据库。

使用`Python2`可以安装`mysql-python`包。
`mysql-python`包没有移植到`Python3`，对于`Python3`，文档中建议安装`mysqlclient`包作为`MySQL`数据库驱动。

使用`pip`包管理器安装mysql数据库驱动：

```
$ pip install mysql-python			//for Python2
$ pip install mysqlclient			//for Python3
```

项目管理脚本`manager.py`中提供了一系列指令用于数据库操作：

- `flush` 清理来自数据库的数据
- `dumpdata` 以指定的格式输出数据库中的内容
- `dbshell` 登陆到配置中指定数据库的命令行界面上(如果该数据库支持)
- `inspectdb` 扫描配置的数据库，将数据库中的表导出为django模型代码
- `migrate` 执行迁移操作，真正将makemigrations指令提交的改动实施到数据库中
- `makemigrations` 提交模型改动，创建一个迁移操作，但不会同步到数据库中

对一个新创建的django项目，配置完数据库之后应该使用管理脚本`manager.py`的`migrate`指令来进行数据迁移。
首次执行`migrate`指令会在配置的数据库中创建一系列django项目需要的表，没有这些表则django的一些功能(`Session`、站点管理等)将无法正常运行。

### 定义模型
在`Django`中，模型定义一般写在App目录下的`models.py`文件中:

- **模型**应继承自`django.db.models.Model`类，一个模型类一般对应数据库中的一张表。
- **字段**为`django.db.models.Field`的子类，为模型类的**类成员**，对应数据库表中的字段(列)。

根据数据表的字段为模型类中的字段选择正确的字段类型，以`MySQL`为例，常见字段与django类型的对应关系为：

| MySQL | Django |
|:------|:-------|
| INT | IntegerField |
| CHAR | CharField |
| FLOAT、DOUBLE | FloatField |
| DECIMAL | DecimalField |
| DATE | DateField |
| DATETIME | DateTimeField |
| TIME | TimeField |
| BLOB | BinaryField |
| TEXT | TextField |

假设有以下结构的MySQL表：

```sql
CREATE TABLE `TestTable` (
	`Index` int(4) NOT NULL DEFAULT '0',
	`Name` varchar(48) NOT NULL DEFAULT '',
	PRIMARY KEY (`Index`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

在django框架中，该表对应的模型类可以写成：

```py
# file: [应用名称]/models.py

from django.db import models

class TestTable(models.Model):

	index = models.IntegerField(primary_key = True, db_column = "Index")	# primary_key用于标识主键
	name = models.CharField(max_length = 48, db_column = 'Name')	# max_length用于设定最大字串长度

	class Meta:
		db_table = "TestTable"
		managed = False		# managed成员设为False则该模型不由django管理(django不会为其自动生成数据库表)
```

默认情况下，模型类中的类名、成员名与数据库表中的表名、字段名的关系为`数据库表名/字段名 = App名 + 下划线 + 模型类名/成员名`。
很多时候，django默认生成的表名/字段名并不符合项目的命名规范，如`TestTable`表默认生成的表名为`[AppName]_TestTable`，此时可以手动指定模型类和类成员的对应表/字段：

- 对于**表名**，通过自定义`Meta`类，指定`Meta`类成员`db_table`来设定模型类关联的数据库表名。
- 对于**字段名**，通过在创建字段时指定`db_column`参数内容来指定类成员关联的数据库字段名。

### 数据库操作
每一个模型都至少有一个管理器，通过管理器来访问、操作数据。
默认管理器名称为`objects`，需要通过模型类访问，并且**不能**通过模型类实例访问。

查询
> 对于模型中的数据，可以通过模型中的**管理器**来获取**查询集**，从查询集中获取数据库中的数据。
>
> 查询的基本语法如下：
>
>	```py
>	模型类名.objects.all()					# 获取包含所有对象的查询集
>	模型类名.objects.filter(**kwargs)		# 获取一个满足参数的查询集
>	模型类名.objects.exclude(**kwargs)		# 获取一个不满足参数的查询集
>	模型类名.objects.order_by(*field_names)	# 获取以指定字段为参数排序的结果集
>	模型类名.objects.get(**kwargs)			# 获取一个单一的查询对象(单行记录)
>	```
>
> 查询集的类型为`QuerySet`，支持索引访问，并可以对其执行**切片**操作。
>
> django中的模型查询操作(`filter()、exclude()`等)具有以下特性：
>
>	- 查询函数返回的结果依然是查询集，因此可以连续调用查询函数，进行**链式过滤**。
>	- 每次调用查询函数得到的查询集都是**独立**的，与之前的查询集**无关**。
>	- 查询集是**惰性执行**的，只有在需要求值时，查询才会被真正的执行。
>
> 对于查询集，可以进行遍历操作，以前面的`TestTable`表为例，打印出表中的所有数据：
>
>	```py
>	for object in TestTable.objects.all():
>		print("Index: " + object.index + " Name: " + object.name)
>	```

插入
> 向数据库中插入数据，主要有两种方式：
>
>	- 使用管理器/查询集中的`create()`成员方法。
>	- 构建带有新数据的模型类实例，之后调用`save()`成员方法。
>
> 以前面的`TestTable`表为例，添加记录：
>
>	```py
>	# 使用create()方法
>	# 添加一行字段index为100，字段name为"TestInsert1"的记录
>	TestTable.objects.create(index = 100, name = 'TestInsert1')
>
>	# 使用save()方法
>	# 添加一行字段index为200，字段name为"TestInsert2"的记录
>	insertItem = TestTable(index = 200, name = 'TestInsert2')
>	insertItem.save()
>	```

修改
> 修改已有的字段需要以下步骤：
>
>	1. 通过管理器的`get()`成员方法获取一行记录。
>	1. 再访问成员字段修改为需要的内容。
>	1. 执行`save()`方法保存修改。
>
> 以前面的`TestTable`表为例，修改已有记录：
>
>	```py
>	# 修改index为100的记录，将其name字段修改为"TestAlter"
>	alterItem = TestTable.objects.get(index = 0)
>	alterItem.name = 'TestAlter'
>	alterItem.save()
>	```



## 视图层
`Django`的视图层，用于封装负责处理用户请求及返回响应的逻辑。

### 编写视图
视图写在应用目录的`views.py`文件中，视图在`Django`中实际上是一个接受`HttpRequest`作为参数，并返回`HttpResponse`或其子类作为结果的函数。

一个简单的视图如下所示：

```py
# file: [应用名称]/views.py

def view_example(request):
	return HttpResponse("""
		<html>
			<head><title>hello</title></head>
			<body>
				<h2>Hello World!</h2>
			</body>
		</html>
	""")
```

默认情况下，`HttpResponse`对应的HTTP状态码为`200`，可以在构造`HttpResponse`对象时显式指定`status`参数来指明状态码：

```py
HttpResponse(status=404)
```

`HttpResponse`拥有一些定义了返回状态码的子类，可以直接使用这些子类作为视图函数返回结果，常用如下所示：

- `HttpResponseRedirect` 状态码`302`
- `HttpResponseNotFound` 状态码`404`
- `HttpResponseBadRequest` 状态码`400`
- `HttpResponseForbidden` 状态码`403`
- `HttpResponseServerError` 状态码`500`

在实际的开发中，展示复杂的页面并不直接调用`HttpResponse()`函数返回请求，而是在视图函数中调用`render()`函数引用模版进行渲染。

在django中，视图函数也承担了逻辑控制的作用，判断条件，在视图函数内调用`redirect()`进行路径跳转。

### 限制 *HTTP* 请求
视图函数前可以使用`django.views.decorators.http`包中的装饰器`require_http_methods`来限制视图响应的HTTP请求类型。

定义一个仅接受`GET`、`POST`请求的视图，如下所示：

```py
from django.views.decorators.http import require_http_methods

@require_http_methods(["GET", "POST"])
def my_view(request):
	pass
```

`django.views.decorators.http`包中还预定义了几种限制HTTP请求的装饰器：

- `require_GET` 仅接受`GET`请求
- `require_POST` 仅接受`POST`请求
- `require_safe` 仅接受`GET`、`HEAD`请求

### 使用 *Http404* 异常
`django.http.response`包中定义了`Http404`异常，抛出`Http404`异常能够进入预置的错误输出页面。

如下所示：

```py
from django.http.response import Http404

def my_view(request):
	raise Http404("Error!")
```

### 路由映射
路由映射写在项目目录中的`urls.py`文件中，通过编写`urlpatterns`列表的内容来指定URL与视图的映射关系。

默认的`urls.py`文件如下：

```py
# file: [项目名称]/urls.py

from django.conf.urls import url
from django.contrib import admin

urlpatterns = [
	url(r'^admin/', admin.site.urls)
]
```

`urlpatterns`列表中的值类型是`url()`实例类型的**列表**。
URL匹配时，位于`urlpatterns`列表前面的正则表达式具有**更高**的优先级。

`url()`函数首参数为匹配URL的**正则表达式**，第二参数可以是：

- 视图函数。
- 使用`include()`函数，以当前模块的其它URL配置列表为参数。
- 使用`include()`函数，以其它包含有`urlpatterns`列表的模块的**模块路径字符串**为参数。

需要注意的是，即使`url()`函数的第一个参数没有使用`r`来标记，也同样会被当作正则表达式对待。
直接传入普通字符串也**同样会**被当作正则表达式对待，在正则表达式语义中，只要传入的URL中带有这些字符串就会被匹配，而无需完全匹配。
完全匹配URL以正则表达式语法应写成`^xxxx/$`(假设`xxxx`是要精确匹配的路径)。

如下所示：

假设应用的视图文件`views.py`中存在如下视图函数：

```py
# file: [应用名称]/views.py
from django.http.response import HttpResponse

# 页面normalUrl
def normalUrl(request):
	return HttpResponse(content = "normalUrl")

# 页面extraUrl
def extraUrl(request):
	return HttpResponse(content = "extraUrl")

# 页面otherUrl
def otherUrl(request):
	return HttpResponse(content = "otherUrl")
```

假设项目的**补充URL配置**存放在**独立的包**中：

```py
# file: [应用名称]/[URL配置包名]/otherUrl.py

from django.conf.urls import url

import 应用名称.views

# URL配置文件必须包含名称为urlpatterns的列表，否则会得到警告
urlpatterns = [
	url(r'^Url/$', 应用名称.views.otherUrl)
]
```

则应用中默认生成的**主URL配置**可以写成：

```py
# file: [项目名称]/urls.py

from django.conf.urls import url, include

import 应用名称.views

# Python为解释性语言，其它的映射列表应在urlpatterns列表之前，否则会出现变量未定义错误
extraUrl = [
	url(r'^Url/$', 应用名称.views.extraUrl)
]

# URL映射的三种方式
urlpatterns = [
	url(r'^normalUrl/$', 应用名称.views.normalUrl),						# 直接映射到视图函数
	url(r'^extra', include(extraUrl)),									# 映射到当前包的其它URL映射列表
	url(r'^other', include('项目名称.应用名称.URL配置包名.otherUrl'))		# 映射到其它的URL配置模块
]
```

上述例子中跳转到`normalUrl`、`extraUrl`和`otherUrl`页面的路径即分别为`normalUrl`、`extraUrl`和`otherUrl`。

### 字段传递
视图函数中的首个参数为`request`对象，通过该对象可以访问传递的字段。

`request`对象内定义了属性`GET`、`POST`，保存了通过`HTTP`协议的`GET`、`POST`方法传递的字段的字典。
可通过如下方式获取传递的字段：

```py
get_data = request.GET['字段名称']
post_data = request.POST['字段名称']
```

获取的字段均为`str`类型。

`CSRF`
> 在django模版中，通过`POST`方式提交数据时需要在`<form></form>`标签之间添加标签`{% csrf_token %}`。
>
> 该操作用于产生`token`数据，并内置到表单中成为提交的一个字段，后端在接受`POST`提交时会对`token`数据进行校验，避免`CSRF(Cross-site request forgery)`攻击(跨站请求伪造攻击)。
>
> django对于没有`token`数据的POST请求都视为跨站请求攻击，会在页面中输出错误信息。

在`url()`函数中传递字段
> `url()`函数中可以添加**可选**的额外参数，类型为**列表**，将需要传递的字段添加入列表中。
>
>	- `url()`函数中若添加了列表参数，则映射到的视图函数需要带有与列表内字段名称相同的参数。
>	- `url()`函数中传递的参数并不属于`GET`、`POST`这样的传递方式，而是直接传递到视图函数的参数中。
>
> 如下所示：
>
> 假设URL配置如下：
>
>	```py
>	# file: [项目名称]/urls.py
>
>	from django.conf.urls import url
>
>	import 应用名称.views
>
>	urlpatterns = [
>		# url()函数中传递了两个字段：name和sex
>		url(r'^normalUrl/$', 应用名称.views.normalUrl, { "name": "Dainslef", "sex": "Male" })
>	]
>	```
>
> 则对应的视图函数应该写成：
>
>	```py
>	# file: [应用名称]/views.py
>	from django.http.response import HttpResponse
>
>	# 视图函数的参数中应该带有与url()函数中传入字段名称相同的参数：name和sex
>	# 字段参数的位置可以交换，但需要保证首参数为request参数
>	def normalUrl(request, name, sex):
>		return HttpResponse("Name: %s, Sex: %s" % (name, sex))
>	```

使用**正则表达式**匹配字段
> 在django中，同样支持在`url()`函数支持正则表达式的捕获语法，捕获的字段会以额外参数的形式传入视图函数中。
>
> 如下所示：
>
> 假设URL配置如下：
>
>	```py
>	# file: [项目名称]/urls.py
>
>	from django.conf.urls import url
>
>	import 应用名称.views
>
>	urlpatterns = [
>		# url()函数的正则表达式捕获两个字段，对应的视图函数也应接收额外的两个参数
>		# 此正则表达式接受的URL格式为：normalUrl/name=XXXX&sex=XXXX/
>		url(r'^normalUrl/name=(\w+)&sex=(\w+)/$', 应用名称.views.normalUrl)
>	]
>	```
>
> 对应的视图函数写成：
>
>	```py
>	# file: [应用名称]/views.py
>	from django.http.response import HttpResponse
>
>	# 与通过列表参数传递字段的方式不同，正则表达式捕获的字段是没有名字的，视图函数只需要参数数量匹配即可
>	def normalUrl(request, name, sex):
>		return HttpResponse("Name: %s, Sex: %s" % (name, sex))
>	```



## 模版层
`Django`框架内置完善的模版引擎(`DTL`)。

### 模版配置
在`Django 1.8`之后，开始支持自定义模版引擎，在配置文件`settings.py`中修改`TEMPLATES`列表中的内容进行模版引擎配置。

默认配置项如下所示：

```py
TEMPLATES = [
	{
		'BACKEND': 'django.template.backends.django.DjangoTemplates',
		'DIRS': [os.path.join(BASE_DIR), '应用名称1/模版文件夹', '应用名称2/模版文件夹', ...],
		'APP_DIRS': True,
		'OPTIONS': {
			'context_processors': [
				'django.template.context_processors.debug',
				'django.template.context_processors.request',
				'django.contrib.auth.context_processors.auth',
				'django.contrib.messages.context_processors.messages',
			],
		},
	},
]
```

- `BACKEND` 模版引擎路径，django自带的模版引擎有：
	1. `django.template.backends.django.DjangoTemplates` 默认模版引擎(`DTL`)
	1. `django.template.backends.jinja2.Jinja2` Jinja模版引擎
- `DIRS` 模版文件路径，django默认情况下会在这些路径下查找模版文件
- `APP_DIRS` 是否查找应用内模版，每种模版引擎都有一个惯用名称，应用内模版应存放在这些路径下(django默认模版引擎路径名为`templates`，Jinja模版引擎为`jinja2`)
- `OPTIONS` 包含引擎相关的具体配置

### 模版语法
与多数模版引擎类似，django中的模版文件也是纯文本，由`HTML`中嵌入模版语法构成。  
在运行时，模版文件和元数据一起由模版引擎渲染生成最终的显示页面。

变量
> 变量的语法是`{{ 变量名 }}`，在模版引擎渲染页面时，会被变量的值替换。  
> 变量使用符号`.`访问成员。

过滤器
> 过滤器是一类特定格式的函数，可以多个串联，多个过滤器的结果作为下个过滤器的输入数据。
>
> 过滤器语法是`{{ 变量名 | 过滤器1 | 过滤器2 | ... }}`，在django默认模版引擎中内置了几十种过滤器，常见的有：
>
>	1. `default` 判断变量是否为空，为空则使用默认值替代，语法`{{ value | defalut: "XXX" }}`
>	1. `length` 获取变量的长度，变量可以是**字符串**或**列表**

标签
> 标签用于在模版中提供特定的功能，如逻辑控制、输出内容等。
> 常见的标签有：
>
> `for` 循环逻辑
>
>	```py
>	# 遍历容器
>	{% for var in vars %}
>		xxxx
>	{% endfor %}
>	# 遍历字典
>	{% for key, value in item %}
>		{{ key }}: {{ value }}
>	{% endfor %}
>	# 遍历容器，同时处理容器为空时的情况
>	{% for var in vars %}
>		xxxx
>	{% empty %}
>		xxxx
>	{% endfor %}
>	```
>
> `if` 判断逻辑
>
>	```py
>	{% if var0 %}
>		xxxx
>	{% elif var1 %}
>		xxxx
>	{% else %}
>		xxxx
>	{% endif %}
>	```
>
> `comment` 注释
>
>	```py
>	{% comment "注释原因。。。" %}
>		XXXX
>		XXXX
>		...
>	{% endcomment %}
>	```
>
> `cycle` 迭代输出
>
>	```py
>	# cycle标签通常用在循环中
>	# 首次访问返回第一个元素，之后返回第二个，以此类推，全部元素都被访问之后从头开始
>	{% for var in vars %}
>		<tr class="{% cycle 'xxx1' 'xxx2' 'xxx3' '...' %}">
>			...
>		</tr>
>	{% endfor %}
>	```
>
> `firstof` 输出不为`False`的参数
>
>	```py
>	# 全为False无输出
>	{% firstof var1 var2 var3 %}
>	# 等价于
>	{% if var1 %}
>		{{ var1 }}
>	{% elif var2 %}
>		{{ var2 }}
>	{% elif var3 %}
>		{{ var3 }}
>	{% endif %}
>	```
>
> `ifchanged` 用在循环中，检测迭代值是否改变
>
>	```py
>	{% for var in vars %}
>		{% ifchanged var %}
>			xxxx
>		{% else %}
>			xxxx
>		{% endifchanged %}
>	{% endfor %}
>	```

### 模板传值
模板中访问的变量应存放在`dict`类型中，通过模板渲染函数`django.shortcuts.render()`传入模板。

模板渲染函数`render()`的定义为：

```py
def render(request, template_name, context = None, content_type = None, status = None, using = None):
	...
```

第三参数`content`即为传入模板的参数(可以为空)，用于向模板传值的`dict`应以`str`类型为**Key**，**Key**的值即为模板中要访问的变量的名称。



## *Session*
`Session`用于保存会话中的信息，使得用户在同一站点的多个页面间的信息能够得到共享。

一般情况下，`Session`会话的生命周期从用户打开站点开始，到关闭浏览器结束。
根据应用服务器的配置，也可能清除长时间无活动页面的`Session`数据。
开启新的浏览器实例会产生新的`Session`，但在支持多标签的现代浏览器中，在新标签中打开页面依然使用原先存在的`Session`。

`Session`实现上基于`Cookie`，需要浏览器支持并开启了`Cookie`功能。

### 配置 *Session*
`Django`框架内置了对`Session`的支持，使用`Session`之前需要保证在项目配置文件`settings.py`中正确写入了以下配置：

- `MIDDLEWARE_CLASSES`中包含了`django.contrib.sessions.middleware.SessionMiddleware`。
- `INSTALLED_APPS`中包含了`django.contrib.sessions`。

默认生成的配置文件**已经**包含了这些配置。

使用`Session`功能之前除了正确设置配置参数，还需要在连接的数据库中正确生成了`django_session`表(使用管理脚本`manager.py`的`migrate`指令执行迁移操作)，django会将用户会话的`Session`数据保存在该表中。

数据库中缺失`django_session`表，会得到下列错误提示：

`1146, "Table '数据库名.django_session' doesn't exist"`

`settings.py`中还有一些重要的Session配置参数：

- `SESSION_SAVE_EVERY_REQUEST` 设定是否每次request都保存Session，默认为`False`
- `SESSION_EXPIRE_AT_BROWSER_CLOSE` 设定是否关闭浏览器立刻使Session过期，默认为`False`
- `SESSION_COOKIE_AGE` 设置Cookie过期时间，单位为秒，默认为两周

### 使用 *Session*
使用`Session`的语法与`POST`、`GET`类似，通过`request`对象的`session`属性来访问保存了Session数据的字典：

```py
# 获取指定字段名称的Session数据
xxx = request.session['字段名称']
# 设置指定字段名称的Session数据
request.session['字段名称'] = value
```

利用Python中的字典特性，可以多级嵌套字典来分类存储Session数据：

```py
request.session['命名空间'] = {}
request.session['命名空间']['字段名称'] = value
```
