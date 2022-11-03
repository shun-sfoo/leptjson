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

## Unicode

| 码点范围           | 码点位数 | 字节 1   | 字节 2   | 字节 3   | 字节 4   |
| ------------------ | -------- | -------- | -------- | -------- | -------- |
| U+0000 ~ U+007F    | 7        | 0xxxxxxx |          |          |          |
| U+0080 ~ U+07FF    | 11       | 110xxxxx | 10xxxxxx |          |          |
| U+0800 ~ U+FFFF    | 16       | 110xxxxx | 10xxxxxx | 10xxxxxx |          |
| U+10000 ~ U+10FFFF | 21       | 110xxxxx | 10xxxxxx | 10xxxxxx | 10xxxxxx |

一个例子解析多字节的情况，欧元符号 € → U+20AC：

1.  U+20AC 在 U+0800 ~ U+FFFF 的范围内，应编码成 3 个字节。
2.  U+20AC 的二进位为 10000010101100
3.  3 个字节的情况我们要 16 位的码点，所以在前面补两个 0，成为 0010000010101100
4.  按上表把二进位分成 3 组：0010, 000010, 101100
5.  加上每个字节的前缀：11100010, 10000010, 10101100
6.  用十六进位表示即：0xE2, 0x82, 0xAC

对于这例子的范围，对应的 C 代码是这样的：

```c
if (u >= 0x0800 && u <= 0xFFFF) {
  OutputByte(0xE0 | ((u >> 12) & 0xFF)); /* 0xE0 = 11100000 */
  OutputByte(0x80 | ((u >> 6) & 0x3F)); /* 0x80 = 10000000 */
  OutputByte(0x80 | ( u & 0x3F)); /* 0x3F = 00111111 */
}
```

高音谱号字符 𝄞 → U+1D11E 不是 BMP 之内的字符。在 JSON 中可写成转义序列 \uD834\uDD1E，
解析第一个 \uD834 得到码点 U+D834，我们发现它是 U+D800 至 U+DBFF 内的码点，所以它是高代理项。
然后解析下一个转义序列 \uDD1E 得到码点 U+DD1E，它在 U+DC00 至 U+DFFF 之内，是合法的低代理项。计算其码点：

```
H = 0xD834, L = 0xDD1E
codepoint = 0x10000 + (H − 0xD800) × 0x400 + (L − 0xDC00)
          = 0x10000 + (0xD834 - 0xD800) × 0x400 + (0xDD1E − 0xDC00)
          = 0x10000 + 0x34 × 0x400 + 0x11E
          = 0x10000 + 0xD000 + 0x11E
          = 0x1D11E
```

## JSON 数组

`array = %x5B ws [ value *( ws %x2C ws value ) ] ws %x5D`

当中，`%x5B` 是左中括号 `[`，`%x2C` 是逗号 `,`，`%x5D` 是右中括号 `]` ，`ws` 是空白字符。

## JSON 对象

```
member = string ws %x3A ws value
object = %x7B ws [ member *( ws %x2C ws member ) ] ws %x7D
```

## termdict usage

```bash
# find mouse event
cat /proc/bus/input/devices
# test eventN is mouse
sudo cat /dev/input/event2 |hexdump

# running
sudo ./termdict event2 xxxxxxxxxxx
```
