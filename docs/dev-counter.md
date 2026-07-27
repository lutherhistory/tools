# C File Counter Utility (`dev-counter`)

A lightweight, CLI-based C utility designed to parse text files and analyze basic textual metrics including character counts, specific white space elements, line counts, and letter frequencies.

---

## 🛠️ Features

* **Character Counting:** Tracks the total byte/character count.
* **Line Detection:** Accurately counts explicit newline characters (`\n`) and total lines.
* **Space Analysis:** Tracks explicit space characters (`' '`).
* **Letter Frequency:** Uses case-insensitive frequency indexing for standard English letters (`a-z`).

---

## 🚀 Getting Started

### Prerequisites
* A standard C compiler (e.g., `gcc`, `clang`, `msvc`).
* Standard C Library support.

### Building
Compile the source file using `gcc`:

```bash
gcc -o dev-counter main.c

./dev-counter sample.txt

name: 'your-text-file.txt'

char: 0
newl: 0
spac: 0
line: 0

a: 0
e: 0
h: 0
l: 0
o: 0
```