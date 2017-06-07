[TOC]

## 概述
`POI`是`Apache`基金会下的项目之一，提供了对微软`Office`系列各类文档的读写支持。  
`POI`采用纯`Java`实现。

### 接口结构
`POI`对不同格式的文档支持拆分在不同的包中，如下所示：

| 包路径 | 支持文档类型 | Maven ArtifactId |
|:----:|:---------:|:----------------:|
| org.apache.poi.poifs | OLE2 Filesystem | poi |
| org.apache.poi.hpsf | OLE2 Property Sets | poi |
| org.apache.poi.hssf | Excel XLS | poi |
| org.apache.poi.hslf | PowerPoint PPT | poi-scratchpad |
| org.apache.poi.hwpf | Word DOC | poi-scratchpad |
| org.apache.poi.hdgf | Visio VSD | poi-scratchpad |
| org.apache.poi.hpbf | Publisher PUB | poi-scratchpad |
| org.apache.poi.hsmf | Outlook MSG | poi-scratchpad |
| org.apache.poi.ddf | Escher common drawings | poi |
| org.apache.poi.hwmf | WMF drawings | poi-scratchpad |
| org.apache.poi.openxml4j | OOXML | poi-ooxml |
| org.apache.poi.xssf | Excel XLSX | poi-ooxml |
| org.apache.poi.xslf | PowerPoint PPTX | poi-ooxml |
| org.apache.poi.xwpf | Word DOCX | poi-ooxml |
| org.apache.poi.xdgf | Visio VSDX | poi-ooxml |
| org.apache.poi.ss | Excel XLS/XLSX | poi-ooxml |
| org.apache.poi.sl | PowerPoint PPT/PPTX | poi-ooxml |

其中：

- `poi`包含了核心的组件。
- `poi-scratchpad`包含了传统的`Office 2003(OLE2)`文档的支持。
- `poi-ooxml`包含了新的`Office 2007(Office Open XML)`文档的支持。

`Excel/PPT`文档的新旧格式之间有通用接口，提供了通用的功能子集(新旧格式共同支持的功能)：

- `xls/xlsx`文档的通用接口为`org.apache.poi.ss`。
- `ppt/pptx`文档的通用接口为`org.apache.poi.sl`。

`Word/Visio`文档之间无通用接口。

`POI`的用户`API`一般位于`org.apache.poi.文档类型.usermodel`路径下。



## *XWPF*
`XWPF`提供了对`Word 2007`(*docx*)格式的文档读写功能。

主要包含以下类型，位于`org.apache.poi.xwpf.usermodel`包路径下：

- `XWPFDocument` 代表整个`Word`文档
- `XWPFParagraph` 代表段落
- `XWPFRun` 代表文本
- `XWPFTable` 代表文档表格
	1. `XWPFTableRow` 代表表格行
	1. `XWPFTableCell` 代表表格内的单元格

### *XWPFDocument*
`XWPFDocument`是对整个`Word`文档的抽象。

使用默认的空参构造方法即可创建新的空白文档。  
使用其父类`POIXMLDocument`提供的`write()`方法可将文档写入输出流中。  
相关方法定义如下所示：

```java
package org.apache.poi;

public class XWPFDocument extends POIXMLDocument implements Document, IBody {
	...
	public XWPFDocument();
	...
}

public abstract class POIXMLDocument extends POIXMLDocumentPart implements Closeable {
	...
	public final void write(OutputStream stream) throws IOException;
	...
}
```

创建文档并保存，如下所示：

```scala
import org.apache.poi.xwpf.usermodel._
import scala.reflect.io.File

object Main extends App {

  val doc = new XWPFDocument
  val out = File("xxx").outputStream()
  doc.write(out)
  out.close()

}
```

### *XWPFParagraph* / *XWPFRun*
`XWPFParagraph`是对文档中**段落**的抽象。  
`XWPFRun`是对文档中**文本**的抽象。

`XWPFParagraph`可由`XWPFDocument`创建。  
`XWPFRun`可由`XWPFParagraph`创建。  
相关方法定义如下所示：

```java
public class XWPFDocument extends POIXMLDocument implements Document, IBody {
	...
	public XWPFParagraph createParagraph();
	...
}

public class XWPFParagraph implements IBodyElement, IRunBody, ISDTContents, Paragraph {
	...
	public XWPFRun createRun();
	...
}
```

`XWPFParagraph`提供了设置段落样式的方法：

```java
public class XWPFParagraph implements IBodyElement, IRunBody, ISDTContents, Paragraph {
	...
	public void setAlignment(ParagraphAlignment align); //设置段落对齐方式
	public void setIndentationLeft(int indentation); //段落左间距
	public void setSpacingBetween(double spacing); //设置段落内行间距
	public void setSpacingBefore(int spaces); //设置段落前空行数
	public void setSpacingAfter(int spaces); //设置段落后空行数
	...
}
```

`XWPFRun`提供了多种方法用于设置文本：

```java
public class XWPFRun implements ISDTContents, IRunElement, CharacterRun {
	...
	public void setText(String value); //文本内容
	public void setColor(String rgbStr); //文本色彩，RGB形式16进制数值格式
	public void setBold(boolean value); //文本加粗
	public void setFontFamily(String fontFamily); //文本字体
	public void setFontSize(int size); //文本字体大小
	public void setCapitalized(boolean value); //文本大写
	...
}
```

### *XWPFTable* / *XWPFTableRow* / *XWPFTableCell*
`XWPFTable`是对文档中**表格**的抽象。  
`XWPFTableRow`是对表格中**行**的抽象。  
`XWPFTableCell`是对表格中**单元格**的抽象。

`XWPFTable`可由`XWPFDocument`创建。  
相关方法定义如下所示：

```java
public class XWPFDocument extends POIXMLDocument implements Document, IBody {
	...
	public XWPFTable createTable(); //创建空表格
	public XWPFTable createTable(int rows, int cols); //创建指定行列大小的表格
	...
}
```

使用空参数的`createTable()`方法创建的表格具有`1`行`1`列的默认大小。

`XWPFTable`类型的常用方法如下所示：

```java
public class XWPFTable implements IBodyElement, ISDTContents {
	...
	public void addNewCol(); //添加一列
	public XWPFTableRow createRow(); //添加一行
	public XWPFTableRow getRow(int pos); //获取指定行
	public void setCellMargins(int top, int left, int bottom, int right); //设置单元格内间距
	...
}
```

`XWPFTableRow`可由`XWPFTable`的`createRow()/getRow()`等方法创建/获取。  
`XWPFTableRow`类型的常用方法如下所示：

```java
public class XWPFTableRow {
	...
	public XWPFTableCell createCell(); //创建新的单元格
	public XWPFTableCell getCell(int pos); //获取指定单元格
	public void removeCell(int pos); //移除指定单元格
	...
}
```

`XWPFTableCell`可由``XWPFTableRow`的`createCell()/getCell()`等方法获取。  
`XWPFTableCell`类型的常用方法如下所示：

```java
public class XWPFTableCell implements IBody, ICell {
	...
	public void setColor(String rgbStr); //设置单元格文本色彩
	public void setVerticalAlignment(XWPFVertAlign vAlign); //设置单元格对齐方式
	public void setText(String text); //设置单元格文本
	public String getText(); //获取单元格文本
	...
}
```
