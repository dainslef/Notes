<!-- TOC -->

- [概述](#概述)
	- [接口結構](#接口結構)
- [XWPF](#xwpf)
	- [XWPFDocument](#xwpfdocument)
	- [XWPFParagraph / XWPFRun](#xwpfparagraph--xwpfrun)
	- [XWPFTable / XWPFTableRow / XWPFTableCell](#xwpftable--xwpftablerow--xwpftablecell)
	- [向文檔中插入圖片](#向文檔中插入圖片)
	- [設置表格寬度](#設置表格寬度)
	- [設置表格單元格的對齊方式](#設置表格單元格的對齊方式)
- [XSSF](#xssf)
	- [XSSFWorkbook](#xssfworkbook)
	- [XSSFSheet / XSSFTable](#xssfsheet--xssftable)
	- [XSSFRow / XSSFCell](#xssfrow--xssfcell)
- [常見問題](#常見問題)
	- [Schemas 類型缺失](#schemas-類型缺失)

<!-- /TOC -->



# 概述
`POI`是`Apache`基金會下的項目之一，提供了對`Microsoft Office`系列各類文檔的讀寫支持。
POI採用純Java實現。

## 接口結構
POI對不同格式的文檔支持拆分在不同的包中，如下所示：

| 包路徑 | 支持文檔類型 | Maven ArtifactId |
|:-----:|:----------:|:----------------:|
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

- `poi`包含了核心的組件。
- `poi-scratchpad`包含了傳統的`Office 2003(OLE2)`文檔的支持。
- `poi-ooxml`包含了新的`Office 2007(Office Open XML)`文檔的支持。

`Excel/PPT`文檔的新舊格式之間有通用接口，提供了通用的功能子集(新舊格式共同支持的功能)：

- `xls/xlsx`文檔的通用接口爲`org.apache.poi.ss`。
- `ppt/pptx`文檔的通用接口爲`org.apache.poi.sl`。

`Word/Visio`文檔之間無通用接口。

POI的用戶API一般位於`org.apache.poi.文檔類型.usermodel`路徑下。



# XWPF
`XWPF`提供了對`Word 2007`(*docx*)格式的文檔讀寫功能。

主要包含以下類型，位於`org.apache.poi.xwpf.usermodel`包路徑下：

- `XWPFDocument` 代表整個Word文檔
- `XWPFParagraph` 代表段落
- `XWPFRun` 代表文本
- `XWPFTable` 代表文檔表格
	1. `XWPFTableRow` 代表表格行
	1. `XWPFTableCell` 代表表格內的單元格

## XWPFDocument
`XWPFDocument`是對整個Word文檔的抽象。

使用默認的空參構造方法即可創建新的空白文檔。
使用其父類`POIXMLDocument`提供的`write()`方法可將文檔寫入輸出流中。
相關方法定義如下所示：

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

創建文檔並保存，如下所示：

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

## XWPFParagraph / XWPFRun
`XWPFParagraph`是對文檔中**段落**的抽象。
`XWPFRun`是對文檔中**文本**的抽象。

`XWPFParagraph`可由`XWPFDocument`創建。
`XWPFRun`可由`XWPFParagraph`創建。
相關方法定義如下所示：

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

`XWPFParagraph`提供了設置段落樣式的方法：

```java
public class XWPFParagraph implements IBodyElement, IRunBody, ISDTContents, Paragraph {
	...
	public void setAlignment(ParagraphAlignment align); //設置段落對齊方式
	public void setIndentationLeft(int indentation); //段落左間距
	public void setSpacingBetween(double spacing); //設置段落內行間距
	public void setSpacingBefore(int spaces); //設置段落前空行數
	public void setSpacingAfter(int spaces); //設置段落後空行數
	...
}
```

`XWPFRun`提供了多種方法用於設置文本：

```java
public class XWPFRun implements ISDTContents, IRunElement, CharacterRun {
	...
	public void setText(String value); //文本內容
	public void setColor(String rgbStr); //文本色彩，RGB形式16進制數值格式
	public void setBold(boolean value); //文本加粗
	public void setFontFamily(String fontFamily); //文本字體
	public void setFontSize(int size); //文本字體大小
	public void setCapitalized(boolean value); //文本大寫
	...
}
```

## XWPFTable / XWPFTableRow / XWPFTableCell
`XWPFTable`是對文檔中**表格**的抽象。
`XWPFTableRow`是對錶格中**行**的抽象。
`XWPFTableCell`是對錶格中**單元格**的抽象。

`XWPFTable`可由`XWPFDocument`創建。
相關方法定義如下所示：

```java
public class XWPFDocument extends POIXMLDocument implements Document, IBody {
	...
	public XWPFTable createTable(); //創建空表格
	public XWPFTable createTable(int rows, int cols); //創建指定行列大小的表格
	...
}
```

使用空參數的`createTable()`方法創建的表格具有`1`行`1`列的默認大小。

`XWPFTable`類型的常用方法如下所示：

```java
public class XWPFTable implements IBodyElement, ISDTContents {
	...
	public void addNewCol(); //添加一列
	public XWPFTableRow createRow(); //添加一行
	public XWPFTableRow getRow(int pos); //獲取指定行
	public void setCellMargins(int top, int left, int bottom, int right); //設置單元格內間距
	...
}
```

`XWPFTableRow`可由`XWPFTable`的`createRow()/getRow()`等方法創建/獲取。
`XWPFTableRow`類型的常用方法如下所示：

```java
public class XWPFTableRow {
	...
	public XWPFTableCell createCell(); //創建新的單元格
	public XWPFTableCell getCell(int pos); //獲取指定單元格
	public void removeCell(int pos); //移除指定單元格
	public List<XWPFTableCell> getTableCells(); //獲取所有單元格
	...
}
```

`XWPFTableCell`可由`XWPFTableRow`的`createCell()/getCell()`等方法獲取。
`XWPFTableCell`類型的常用方法如下所示：

```java
public class XWPFTableCell implements IBody, ICell {
	...
	public void setColor(String rgbStr); //設置單元格文本色彩
	public void setVerticalAlignment(XWPFVertAlign vAlign); //設置單元格對齊方式
	public void setText(String text); //設置單元格文本
	public String getText(); //獲取單元格文本
	...
}
```

從`XWPFTable`中通過索引獲取行列時需要注意，行列序號均爲從`0`開始(類似**數組下標**)。

## 向文檔中插入圖片
到目前版本爲止(`POI 3.16`)，向`Word 2007`文檔中插入圖片的功能實現存在BUG。
使用`XWPFRun`提供的`addPicture()`方法插入圖片時，並未在文檔中正確地生成圖片的相關XML。

要使圖片插入功能正常使用，需要自行實現圖片插入相關邏輯。
以`Implicit Class`形式擴展`XWPFDocument`類，添加圖片插入功能，如下所示：

```scala
import org.apache.xmlbeans.XmlToken
import org.apache.poi.xwpf.usermodel.{ParagraphAlignment, XWPFDocument}

/**
  * 爲 XWPFDocument 類提供額外的功能：向文檔中添加圖片
  *
  * @param doc 需要被隱式轉換的 XWPFDocument 實例
  */
implicit class XwpfDocumentUtils(doc: XWPFDocument) {

  private[this] val Emu = 9525

  /**
    * 向文檔中添加圖片
    *
    * @param pictureId  資源Id
    * @param pictureNum 圖片編號
    * @param width      圖片寬
    * @param height     圖片高
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

調用圖片插入功能的完整示例代碼，如下所示：

```scala
import org.apache.poi.sl.usermodel.PictureData.PictureType
import org.apache.poi.xwpf.usermodel.XWPFDocument

import javax.imageio.ImageIO
import scala.reflect.io.File

object Main extends App {

  val doc = new XWPFDocument
  val picture = File("測試圖片.png")

  // 調用隱式方法，添加圖片數據，獲取圖片資源id
  val id = doc.addPictureData(picture.inputStream, PictureType.PNG.nativeId)
  // 獲取圖片信息
  val imageIO = ImageIO.read(picture.inputStream)

  // 生成圖片XML
  doc.addPicture(id,
    doc.getNextPicNameNumber(PictureType.PNG.nativeId),
    imageIO.getWidth, imageIO.getHeight) //通過ImageIO類型獲取圖片大小

  // 文檔寫入硬盤
  val out = File("測試輸出文檔.docx").outputStream()
  doc.write(out)
  out.close()

}
```

## 設置表格寬度
`XWPFTable`類型提供了用於設置表格寬度的`setWidth()`方法，但該方法無效。
`POI 3.16`中`XWPFTable`類型的`setWidth()`方法源碼如下所示：

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

原因是`CTTblWidth`實例需要使用`setType()`將寬度樣式設置爲`STTblWidth.DXA`才能使設置的寬度值生效。

以`Implicit Class`形式擴展`XWPFTable`類，自行實現設置表格寬度功能，如下所示：

```scala
import java.math.BigInteger

import org.apache.poi.xwpf.usermodel.XWPFTable
import org.openxmlformats.schemas.wordprocessingml.x2006.main.STTblWidth

/**
  * 爲 XWPFTable 類提供額外的功能： 設置表格寬度
  *
  * @param table 需要被隱式轉換的 XWPFTable 實例
  */
implicit class XWPFTableUtils(table: XWPFTable) {

  /**
    * 設置表格寬度
    *
    * @param width 寬度
    */
  def setTableWidth(width: Int) {
    val cTTblWidth = table.getCTTbl.getTblPr.addNewTblW()
    cTTblWidth.setW(BigInteger.valueOf(width))
    cTTblWidth.setType(STTblWidth.DXA) //寬度類型
  }

}
```

## 設置表格單元格的對齊方式
POI沒有提供設置`XWPFTableCell`內部對齊方式的用戶層接口。
實現單元格居中功能需要使用`Schemas`相關底層接口。
涉及的Schemas相關類型包路徑爲`org.openxmlformats.schemas.wordprocessingml.x2006.main`。

以`Implicit Class`形式擴展XWPFTable類，自行實現單元格對齊功能，如下所示：

```scala
import org.apache.poi.xwpf.usermodel.XWPFTable
import org.openxmlformats.schemas.wordprocessingml.x2006.main._

/**
  * 爲 XWPFTable 類提供額外的功能：
  * 1. 設置單元格水平對齊方式
  * 2. 設置單元格垂直對齊方式
  *
  * @param table 需要被隱式轉換的 XWPFTable 實例
  */
implicit class XWPFTableUtils(table: XWPFTable) {

  /**
    * 設置所有單元格內部文本的水平方向對齊方式
    *
    * @param align 對齊方式
    */
  def setCellsHorizontalAlign(align: STJc.Enum) = for {
    row <- 0 until table.getRows.size
    cell <- 0 until table.getRow(row).getTableCells.size
  } table.getRow(row).getCell(cell).getCTTc.getPList.forEach {
    _.addNewPPr().addNewJc().setVal(align)
  }

  /**
    * 設置所有單元格內部的垂直方向對齊方式
    *
    * @param align 對齊方式
    */
  def setCellsVerticalAlign(align: STVerticalJc.Enum) = for {
    row <- 0 until table.getRows.size
    cell <- 0 until table.getRow(row).getTableCells.size
  } table.getRow(row).getCell(cell).getCTTc.addNewTcPr().addNewVAlign().setVal(align)

}
```

默認情況下，`CTTc`實例調用`getPList()`方法會可能會拋出異常：

```
java.lang.NoClassDefFoundError: org/openxmlformats/schemas/wordprocessingml/x2006/main/impl/CTTcImpl$1PList
```

需要添加`ooxml-schemas`依賴。



# XSSF
`XSSF`提供了對`Excel 2007`(*xlsx*)格式的文檔讀寫功能。

主要包含以下類型，位於`org.apache.poi.xssf.usermodel`包路徑下：

- `XSSFWorkbook` 代表整個`Excel`文檔
- `XSSFSheet` 代表一個工作表
- `XSSFRow` 代表表格內的行
- `XSSFCell` 代表表格內的單元格
- `XSSFCellStyle` 代表單元格的樣式

與`XWPF`相比，`Excel`相關的`HSSF/XSSF`是`POI`的主打功能，接口完善、功能強大。

## XSSFWorkbook
`XSSFWorkbook`是對整個`Excel`文檔的抽象，與`XWPF`中的`XWPFDocument`類似。

使用默認的空參構造方法即可創建新的空白文檔。
使用其父類`POIXMLDocument`提供的`write()`方法可將文檔寫入輸出流中。
相關方法定義如下所示：

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

## XSSFSheet / XSSFTable
`XSSFSheet`代表Excel文檔中的**工作表**，一個Excel文檔中可以包含多張工作表。
使用`XSSFWorkbook`的`createSheet()/getSheet()/getSheetAt()`等方法可以創建/獲取文檔中的工作表(`XSSFSheet`實例)。
相關方法定義如下所示：

```java
public class XSSFWorkbook extends POIXMLDocument implements Workbook {
	...
	public XSSFSheet createSheet(String sheetname); //創建指定名稱的工作表
	public XSSFSheet getSheet(String name); //獲取指定名稱的工作表
	public XSSFSheet getSheetAt(int index); //獲取指定索引的工作表
	...
}
```

工作表本身可以包含子表格，使用`XSSFWorkbook`的`createTable()/getTables()`方法創建/獲取表格。
相關方法定義如下所示：

```java
public class XSSFSheet extends POIXMLDocumentPart implements Sheet {
	...
	public XSSFTable createTable();
	public List<XSSFTable> getTables();
	...
}
```

## XSSFRow / XSSFCell
`XSSFRow/XSSFCell`代表表格中的行、列。

通過`XSSFSheet`的`createRow()`方法向工作表中添加行。
通過`XSSFCell`的`createCell()`方法向行中添加單元格。



# 常見問題
包含POI使用中的一些問題的解決方案。

## Schemas 類型缺失
在使用部分`Schemas`相關類型、方法時出現異常：

```
java.lang.NoClassDefFoundError: org/openxmlformats/schemas/...
```

該異常是由於缺少Schemas相關類型的JAR包造成的，需要在`build.sbt`中添加：

```scala
"org.apache.poi" % "ooxml-schemas" % "版本號"
```

對於多數此類型的異常，都是由於Schemas相關類型缺失造成的。
默認依賴的`poi-ooxml-schemas`體積較小，並不包含完整的Schemas類型，
需要使用完整的Schemas相關類型時，需要依賴體積較大的`ooxml-schemas`包。
