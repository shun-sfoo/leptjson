# Project Configuration

```bash
mkdir leptjson
meson init --name leptjson --build
```

## Meson command

```bash
cd build
meson compile
```

## Code Style

base on google

`clang-format --dump-config --style=google`

fix

```
AlignConsecutiveMacros: AcrossEmptyLines
AllowShortBlocksOnASingleLine: true
AllowShortCaseLabelsOnASingleLine: true
ColumnLimit:     120
```

## Json

```json
{
  "title": "Design Patterns",
  "subtitle": "Elements of Reusable Object-Oriented Software",
  "author": ["Erich Gamma", "Richard Helm", "Ralph Johnson", "John Vlissides"],
  "year": 2009,
  "weight": 1.8,
  "hardcover": true,
  "publisher": {
    "Company": "Pearson Education",
    "Country": "India"
  },
  "website": null
}
```

从此例子可看出，JSON 是树状结构，而 JSON 只包含 6 种数据类型：

- null: 表示为 null
- boolean: 表示为 true 或 false
- number: 一般的浮点数表示方式
- string: 表示为 "..."
- array: 表示为 [ ... ]
- object: 表示为 { ... }

要实现的 JSON 库，主要是完成 3 个需求：

1. 把 JSON 文本解析为一个树状数据结构（parse）。
2. 提供接口访问该数据结构（access）。
3. 把数据结构转换成 JSON 文本（stringify）。

## JSON 语法子集

```
JSON-text = ws value ws
ws = *(%x20 / %x09 / %x0A / %x0D)
value = null / false / true
null  = "null"
false = "false"
true  = "true"
```

## JSON 数字语法

```
number = [ "-" ] int [ frac ] [ exp ]
int = "0" / digit1-9 *digit
frac = "." 1*digit
exp = ("e" / "E") ["-" / "+"] 1*digit
```

## JSON 字符串语法

```
string = quotation-mark *char quotation-mark
char = unescaped /
   escape (
       %x22 /          ; "    quotation mark  U+0022
       %x5C /          ; \    reverse solidus U+005C
       %x2F /          ; /    solidus         U+002F
       %x62 /          ; b    backspace       U+0008
       %x66 /          ; f    form feed       U+000C
       %x6E /          ; n    line feed       U+000A
       %x72 /          ; r    carriage return U+000D
       %x74 /          ; t    tab             U+0009
       %x75 4HEXDIG )  ; uXXXX                U+XXXX
escape = %x5C          ; \
quotation-mark = %x22  ; "
unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
```
