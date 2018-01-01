<!-- TOC -->

- [概述](#概述)
	- [接口结构](#接口结构)
- [*XWPF*](#xwpf)
	- [*XWPFDocument*](#xwpfdocument)
	- [*XWPFParagraph* / *XWPFRun*](#xwpfparagraph--xwpfrun)
	- [*XWPFTable* / *XWPFTableRow* / *XWPFTableCell*](#xwpftable--xwpftablerow--xwpftablecell)
	- [向文档中插入图片](#向文档中插入图片)
	- [设置表格宽度](#设置表格宽度)
	- [设置表格单元格的对齐方式](#设置表格单元格的对齐方式)
- [*XSSF*](#xssf)
	- [*XSSFWorkbook*](#xssfworkbook)
	- [*XSSFSheet* / *XSSFTable*](#xssfsheet--xssftable)
- [*XSSFRow* / *XSSFCell*](#xssfrow--xssfcell)
- [常见问题](#常见问题)
	- [*Schemas* 类型缺失](#schemas-类型缺失)

<!-- /TOC -->



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
	public List<XWPFTableCell> getTableCells(); //获取所有单元格
	...
}
```

`XWPFTableCell`可由`XWPFTableRow`的`createCell()/getCell()`等方法获取。  
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

从`XWPFTable`中通过索引获取行列时需要注意，行列序号均为从`0`开始(类似**数组下标**)。

### 向文档中插入图片
到目前版本为止(`POI 3.16`)，向`Word 2007`文档中插入图片的功能实现存在`BUG`。  
使用`XWPFRun`提供的`addPicture()`方法插入图片时，并未在文档中正确地生成图片的相关`XML`。

要使图片插入功能正常使用，需要自行实现图片插入相关逻辑。
以`Implicit Class`形式扩展`XWPFDocument`类，添加图片插入功能，如下所示：

```scala
import org.apache.xmlbeans.XmlToken
import org.apache.poi.xwpf.usermodel.{ParagraphAlignment, XWPFDocument}

/**
  * 为 XWPFDocument 类提供额外的功能：向文档中添加图片
  *
  * @param doc 需要被隐式转换的 XWPFDocument 实例
  */
implicit class XwpfDocumentUtils(doc: XWPFDocument) {

  private[this] val Emu = 9525

  /**
    * 向文档中添加图片
    *
    * @param pictureId  资源Id
    * @param pictureNum 图片编号
    * @param width      图片宽
    * @param height     图片高
    */
  def addPicture(pictureId: String, pictureNum: Int, width: Int, height: Int) {

    val (w, h) = (width * Emu, height * Emu)
    val paragraph = doc.createParagraph()
    paragraph.setAlignment(ParagraphAlignment.CENTER)

    val inline = paragraph.createRun().getCTR.addNewDrawing().addNewInline()
    val pictureXml =
      s"""|<a:graphic xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main">
          |  <a:graphicData uri="http://schemas.openxmlformats.org/drawingml/2006/picture">
          |    <pic:pic xmlns:pic="http://schemas.openxmlformats.org/drawingml/2006/picture">
          |       <pic:nvPicPr>
          |         <pic:cNvPr id="$pictureNum" name="Generated"/><pic:cNvPicPr/>
          |       </pic:nvPicPr>
          |       <pic:blipFill>
          |         <a:blip r:embed="$pictureId" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"/>
          |         <a:stretch><a:fillRect/></a:stretch>
          |       </pic:blipFill>
          |       <pic:spPr>
          |         <a:xfrm>
          |           <a:off x="0" y="0"/>
          |           <a:ext cx="$w" cy="$h"/>
          |         </a:xfrm>
          |         <a:prstGeom prst="rect"><a:avLst/></a:prstGeom>
          |       </pic:spPr>
          |     </pic:pic>
          |  </a:graphicData>
          |</a:graphic>
          |""".stripMargin

    inline.set(XmlToken.Factory.parse(pictureXml))
    inline.setDistT(0)
    inline.setDistB(0)
    inline.setDistL(0)
    inline.setDistR(0)

    val extent = inline.addNewExtent()
    extent.setCx(w)
    extent.setCy(h)

    val docPr = inline.addNewDocPr()
    docPr.setId(pictureNum)
    docPr.setName(s"Picture $pictureNum")
    docPr.setDescr("Generated")

  }

}
```

调用图片插入功能的完整示例代码，如下所示：

```scala
import org.apache.poi.sl.usermodel.PictureData.PictureType
import org.apache.poi.xwpf.usermodel.XWPFDocument

import javax.imageio.ImageIO
import scala.reflect.io.File

object Main extends App {

  val doc = new XWPFDocument
  val picture = File("测试图片.png")

  // 调用隐式方法，添加图片数据，获取图片资源id
  val id = doc.addPictureData(picture.inputStream, PictureType.PNG.nativeId) 
  // 获取图片信息
  val imageIO = ImageIO.read(picture.inputStream)

  // 生成图片XML
  doc.addPicture(id,
    doc.getNextPicNameNumber(PictureType.PNG.nativeId),
    imageIO.getWidth, imageIO.getHeight) //通过ImageIO类型获取图片大小

  // 文档写入硬盘
  val out = File("测试输出文档.docx").outputStream()
  doc.write(out)
  out.close()

}
```

### 设置表格宽度
`XWPFTable`类型提供了用于设置表格宽度的`setWidth()`方法，但该方法无效。  
`POI 3.16`中`XWPFTable`类型的`setWidth()`方法源码如下所示：

```java
public class XWPFTable implements IBodyElement, ISDTContents {
	...
	public void setWidth(int width) {
		CTTblPr tblPr = getTrPr();
		CTTblWidth tblWidth = tblPr.isSetTblW() ? tblPr.getTblW() : tblPr.addNewTblW();
		tblWidth.setW(new BigInteger("" + width));
	}
	...
}
```

原因是`CTTblWidth`实例需要使用`setType()`将宽度样式设置为`STTblWidth.DXA`才能使设置的宽度值生效。

以`Implicit Class`形式扩展`XWPFTable`类，自行实现设置表格宽度功能，如下所示：

```scala
import java.math.BigInteger

import org.apache.poi.xwpf.usermodel.XWPFTable
import org.openxmlformats.schemas.wordprocessingml.x2006.main.STTblWidth

/**
  * 为 XWPFTable 类提供额外的功能： 设置表格宽度
  *
  * @param table 需要被隐式转换的 XWPFTable 实例
  */
implicit class XWPFTableUtils(table: XWPFTable) {

  /**
    * 设置表格宽度
    *
    * @param width 宽度
    */
  def setTableWidth(width: Int) {
    val cTTblWidth = table.getCTTbl.getTblPr.addNewTblW()
    cTTblWidth.setW(BigInteger.valueOf(width))
    cTTblWidth.setType(STTblWidth.DXA) //宽度类型
  }

}
```

### 设置表格单元格的对齐方式
`POI`没有提供设置`XWPFTableCell`内部对齐方式的用户层接口。  
实现单元格居中功能需要使用`Schemas`相关底层接口。  
涉及的`Schemas`相关类型包路径为`org.openxmlformats.schemas.wordprocessingml.x2006.main`。

以`Implicit Class`形式扩展`XWPFTable`类，自行实现单元格对齐功能，如下所示：

```scala
import org.apache.poi.xwpf.usermodel.XWPFTable
import org.openxmlformats.schemas.wordprocessingml.x2006.main._

/**
  * 为 XWPFTable 类提供额外的功能：
  * 1. 设置单元格水平对齐方式
  * 2. 设置单元格垂直对齐方式
  *
  * @param table 需要被隐式转换的 XWPFTable 实例
  */
implicit class XWPFTableUtils(table: XWPFTable) {

  /**
    * 设置所有单元格内部文本的水平方向对齐方式
    *
    * @param align 对齐方式
    */
  def setCellsHorizontalAlign(align: STJc.Enum) = for {
    row <- 0 until table.getRows.size
    cell <- 0 until table.getRow(row).getTableCells.size
  } table.getRow(row).getCell(cell).getCTTc.getPList.forEach {
    _.addNewPPr().addNewJc().setVal(align)
  }

  /**
    * 设置所有单元格内部的垂直方向对齐方式
    *
    * @param align 对齐方式
    */
  def setCellsVerticalAlign(align: STVerticalJc.Enum) = for {
    row <- 0 until table.getRows.size
    cell <- 0 until table.getRow(row).getTableCells.size
  } table.getRow(row).getCell(cell).getCTTc.addNewTcPr().addNewVAlign().setVal(align)

}
```

默认情况下，`CTTc`实例调用`getPList()`方法会可能会抛出异常：

```
java.lang.NoClassDefFoundError: org/openxmlformats/schemas/wordprocessingml/x2006/main/impl/CTTcImpl$1PList
```

需要添加`ooxml-schemas`依赖。



## *XSSF*
`XSSF`提供了对`Excel 2007`(*xlsx*)格式的文档读写功能。

主要包含以下类型，位于`org.apache.poi.xssf.usermodel`包路径下：

- `XSSFWorkbook` 代表整个`Excel`文档
- `XSSFSheet` 代表一个工作表
- `XSSFRow` 代表表格内的行
- `XSSFCell` 代表表格内的单元格
- `XSSFCellStyle` 代表单元格的样式

与`XWPF`相比，`Excel`相关的`HSSF/XSSF`是`POI`的主打功能，接口完善、功能强大。

### *XSSFWorkbook*
`XSSFWorkbook`是对整个`Excel`文档的抽象，与`XWPF`中的`XWPFDocument`类似。

使用默认的空参构造方法即可创建新的空白文档。  
使用其父类`POIXMLDocument`提供的`write()`方法可将文档写入输出流中。  
相关方法定义如下所示：

```java
public class XSSFWorkbook extends POIXMLDocument implements Workbook {
	...
	public XSSFWorkbook();
	...
}

public abstract class POIXMLDocument extends POIXMLDocumentPart implements Closeable {
	...
	public final void write(OutputStream stream) throws IOException;
	...
}
```

### *XSSFSheet* / *XSSFTable*
`XSSFSheet`代表`Excel`文档中的**工作表**，一个`Excel`文档中可以包含多张工作表。  
使用`XSSFWorkbook`的`createSheet()/getSheet()/getSheetAt()`等方法可以创建/获取文档中的工作表(`XSSFSheet`实例)。  
相关方法定义如下所示：

```java
public class XSSFWorkbook extends POIXMLDocument implements Workbook {
	...
	public XSSFSheet createSheet(String sheetname); //创建指定名称的工作表
	public XSSFSheet getSheet(String name); //获取指定名称的工作表
	public XSSFSheet getSheetAt(int index); //获取指定索引的工作表
	...
}
```

工作表本身可以包含子表格，使用`XSSFWorkbook`的`createTable()/getTables()`方法创建/获取表格。  
相关方法定义如下所示：

```java
public class XSSFSheet extends POIXMLDocumentPart implements Sheet {
	...
	public XSSFTable createTable();
	public List<XSSFTable> getTables();
	...
}
```

## *XSSFRow* / *XSSFCell*
`XSSFRow/XSSFCell`代表表格中的行、列。

通过`XSSFSheet`的`createRow()`方法向工作表中添加行。  
通过`XSSFCell`的`createCell()`方法向行中添加单元格。



## 常见问题
包含`POI`使用中的一些问题的解决方案。

### *Schemas* 类型缺失
在使用部分`Schemas`相关类型、方法时出现异常：

```
java.lang.NoClassDefFoundError: org/openxmlformats/schemas/...
```

该异常是由于缺少`Schemas`相关类型的`JAR`包造成的，需要在`build.sbt`中添加：

```scala
"org.apache.poi" % "ooxml-schemas" % "版本号"
```

对于多数此类型的异常，都是由于`Schemas`相关类型缺失造成的。  
默认依赖的`poi-ooxml-schemas`体积较小，并不包含完整的`Schemas`类型，
需要使用完整的`Schemas`相关类型时，需要依赖体积较大的`ooxml-schemas`包。
