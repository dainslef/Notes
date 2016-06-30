## 安装和配置 *Django*
使用`pip`安装`Django`包：

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

一个空的django应用基本文件结构如下所示：

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
		'NAME': '[连接的数据库名称]',
		'USER': '[数据库账户名称]',
		'PASSWORD': '[数据库账户对应密码]',
		'host': '[主机地址]',
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
`mysql-python`包没有移植到`Python3`，对于`Python3`，文档中建议安装`mysqlclient`包作为mysql数据库驱动。

使用`pip`包管理器安装mysql数据库驱动：

```
$ pip install mysql-python			//for Python2
$ pip install mysqlclient			//for Python3
```

项目管理脚本`manager.py`中提供了一系列指令用于数据库操作：

- `syncdb` 同步模型与数据库，模型中定义的表若在数据库中不存在，则会自动创建
- `flush` 清理来自数据库的数据
- `dumpdata` 以指定的格式输出数据库中的内容
- `dbshell` 登陆到配置中指定数据库的命令行界面上(如果该数据库支持)
- `inspectdb` 扫描配置的数据库，将数据库中的表导出为django模型代码

### 定义模型
在`Django`中，模型定义一般写在App目录下的`models.py`文件中:

- **模型**应继承自`django.db.models.Model`类，一个模型类一般对应数据库中的一张表。
- **字段**为`django.db.models.Field`的子类，为模型类的**类成员**，对应数据库表中的字段(列)。

根据数据表的字段为模型类中的字段选择正确的字段类型，以`MySQL`为例，mysql中的常见字段与django中的字段对应关系为：

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

假设有以下结构的mysql表：

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

### 限制HTTP请求
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

### URL映射
URL映射写在项目目录中的`urls.py`文件中，通过编写`urlpatterns`列表的内容来指定URL与视图的映射关系。

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

`url()`函数首参数为匹配URL的**正则表达式**(如果只需要匹配一个字符串，则可**不使用**正则表达式，传入普通字符串即可)，第二参数可以是：

- 视图函数。
- 使用`include()`函数，以当前模块的其它URL配置列表为参数。
- 使用`include()`函数，以其它包含有`urlpatterns`列表的模块的**模块路径字符串**为参数。

如下所示：

假设应用的视图文件`views.py`中存在如下视图函数：

```py
# file: [应用名称]/views.py
from django.http.response import HttpResponse

# 页面normalUrl
def normalUrl(request):
	return HttpResponse(content = normalUrl")

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
	url('Url', 应用名称.views.otherUrl)
]
```

则应用中默认生成的**主URL配置**可以写成：

```py
# file: [项目名称]/urls.py

from django.conf.urls import url, include

import 应用名称.views

# Python为解释性语言，其它的映射列表应在urlpatterns列表之前，否则会出现变量未定义错误
extraUrl = [
	url('Url', 应用名称.views.extraUrl)
]

# URL映射的三种方式
urlpatterns = [
	url('normalUrl', 应用名称.views.normalUrl),						# 直接映射到视图函数
	url('extra', include(extraUrl)),								# 映射到当前包的其它URL映射列表
	url('other', include('项目名称.应用名称.URL配置包名.otherUrl'))		# 映射到其它的URL配置模块
]
```

需要注意的是，转发到其它URL配置时，URL字符串中已匹配的部分**不会**被发往下一个URL配置，且路径中的空格被忽略。
因此，上述例子中跳转到`normalUrl`页面的路径只能是`normalUrl`，但页面`extraUrl`和`otherUrl`的路径可以分别是`extraUrl`、`extra Url`、`extra/Url`和`otherUrl`、`other Url`、`other/Url`，路径中的空格和斜杠不会影响匹配。

### URL传参
视图函数中的首个参数为`request`对象，通过该对象可以访问传递的字段。

`request`对象内定义了属性`GET`、`POST`，保存了通过http协议的GET、POST方法传递的字段的字典。
可通过如下方式获取传递的参数：

```py
get_data = request.GET['参数名称']
post_data = request.POST['参数名称']
```

在django模版中，通过`POST`方式提交数据时需要在`<form></form>`标签之间添加`{% csrf_token %}`。
该操作用于产生`token`数据，并内置到表单中成为提交的一个字段，后段在接受`POST`提交时会对`token`数据进行校验，避免`CSRF(Cross-site request forgery)`攻击(跨站请求伪造攻击)。

django对于没有`token`数据的POST请求都视为跨站请求攻击，会在页面中输出错误信息。