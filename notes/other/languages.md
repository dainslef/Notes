<!-- TOC -->

- [類型系統](#類型系統)
    - [子結構類型系統](#子結構類型系統)
- [Type Class vs Interface](#type-class-vs-interface)

<!-- /TOC -->



# 類型系統
在編程語言中，[`Type System`](https://en.wikipedia.org/wiki/Type_system)（類型系統）是一組規則，
將名為**類型**的屬性應用到各類程序結構中，如**變量**、**表達式**、**函數**、**模塊**等。

編程語言根據其類型系統的特徵，可按多個緯度進行劃分、歸類。
主要的類型系統類別：

- `Static Typing`（靜態類型） & `Dynamic Typing`（動態類型）

	靜態類型語言中，類型在**編譯期間**確定。
	靜態類型語言的類型結構**不能**在運行期間修改（例如向實例中動態添加/刪除類型的字段/方法），
	類型結構一經定義就已確定。
	靜態類型語言多數需要使用**編譯器**將源碼編譯爲特定的目標代碼後執行，
	在編譯期間，編譯器能夠檢查出類型相關的錯誤。
	部分靜態類型語言擁有`Reflect`（反射）特性（如`Java`、`C#`、`Go`等），
	具有一定的動態特性，能夠在運行期間獲取類型信息，修改成員內容。

	動態類型語言中，類型在**運行時**確定。
	動態類型語言的類型結構**可以**在運行時修改，類型系統更加靈活。
	動態語言多數採用解釋執行的方式，僅在運行期間才能發現類型錯誤。

	常見的靜態類型語言：

	```
	C/C++、Java、Go、Rust、Scala、Haskell
	```

	常見的動態類型語言：

	```
	Python、Ruby、JavaScript
	```

- `Strong Typing`（強類型） & `Weak Typing`（弱類型）

	強類型語言中，運行時**不會**將實例自動轉化爲與實際內容不符的類型。
	弱類型語言中，運行時會將實例自動轉化爲與實際內容不符的類型，自動轉化實際改變了實例的實際內容。

	常見的強類型語言：

	```
	Java、Scala、Haskell、Python
	```

	常見的弱類型語言：

	```
	C、Assembly、JavaScript
	```

- `Latent (Implicit) Typing`（隱式類型） & `Manifest (Explicit) Typing`（顯式類型）

	顯式類型語言需要在源碼中爲顯式地爲字段、方法標註類型信息。
	隱式類型語言不需要顯式標註類型信息，編譯器、解釋器可從上下文中推斷出字段、方法的類型。

	部分隱式類型語言可選則手動添加類型標註，用於在類型推斷不準確或無法進行的情況下的顯式添加類型信息。
	部分顯式類型語言在新版本中也添加了自動類型推導機制，如`C++ 11`、`C# 3.0`等。

	常見的隱式類型語言：

	```
	Python、Ruby、JavaScript、Haskell
	```

	常見的顯式類型語言：

	```
	C、C++、C#、Java
	```

- `Nominal Typing`（名義類型） & `Structural Typing`（結構類型）

	名義類型語言在判定類型時根據類型的標稱（類型名稱）。
	結構類型語言在判定類型時根據類型的實際結構。

	對於名義類型的語言而言，兩個結構完全相同的類型只要名稱不同，便不是同一個類型；
	而結構類型語言僅需要實際結構相同即可。

	動態語言中常見的`Duck Type`（鴨子類型）特性即是結構類型的特徵。
	部分名義類型語言也會帶有結構類型的特性，
	如Go中的`Interface`、C++中的`Template`、Scala中的`Structural Type`等。

	常見的名義類型語言：

	```
	C、C++、C#、Java、Scala
	```

	常見的結構類型語言：

	```
	Python、Ruby、Haskell
	```

## 子結構類型系統
[`Substructural type system`](https://en.wikipedia.org/wiki/Substructural_type_system)
（子結構類型系統）是類型系統中的一個類別，可根據子邏輯減少或僅允許受控的行為。
該類型系統在訪問**系統資源**如**文件**、**鎖**、**內存**時，
可用於能夠保持追蹤狀態的變化，並阻止無效的狀態。

子結構類型系統主要分為以下幾類：

- Ordered type systems (discard exchange, weakening and contraction): Every variable is used exactly once in the order it was introduced.
- Linear type systems (allow exchange, but neither weakening nor contraction): Every variable is used exactly once.
- Affine type systems (allow exchange and weakening, but not contraction): Every variable is used at most once.
- Relevant type systems (allow exchange and contraction, but not weakening): Every variable is used at least once.
- Normal type systems (allow exchange, weakening and contraction): Every variable may be used arbitrarily.

主要特性區別見下列表格：

| Type | Exchange | Weakening | Contraction | Use |
| :- | :- | :- | :- | :- |
| Ordered | / | / | / | Exactly once in order |
| Linear | Allowed | / | / | Exactly once |
| Affine | Allowed | Allowed | / | At most once |
| Relevant | Allowed | / | Allowed | At least once |
| Normal | Allowed | Allowed | Allowed | Arbitrarily |



# Type Class vs Interface
type class（類型類）是Haskell系列的函數式語言提供的抽象方式，
部分函數式語言也提供了類似type class的機制，
如Rust的trait、Scala的implicit conversion；
在OOP語言中，與之類似的概念是OOP語言中的interface（接口）。

type class於interface之間的對比可參考StackOverflow、Reddit上的相關討論：

- [Traits vs Interfaces](https://www.reddit.com/r/rust/comments/cn20vu/traits_vs_interfaces/)
- [Difference between OOP interfaces and FP type classes](https://stackoverflow.com/questions/8122109/difference-between-oop-interfaces-and-fp-type-classes/8123973#8123973)
- [Java's Interface and Haskell's type class: differences and similarities?](https://stackoverflow.com/questions/6948166/javas-interface-and-haskells-type-class-differences-and-similarities)

以及Haskell Wiki上的論述[OOP vs type classes]((https://wiki.haskell.org/OOP_vs_type_classes))。

interface與type class的一些特性對比：

- interface自身為類型層次的一部分；type class在類型系統中位於獨立的層次。
- 採用interface機制的語言（Java、C#等）中，通常在類型定義時就需要指明類型實現的接口，
外部開發者通常不具備修改既定類型實現接口的能力；
採用type class機制的語言，如Haskell、Rust均具備直接為外部類型添加type class實現的能力
（Rust存在部分限制，僅能為外部類型實現自身定義trait的實現）。
