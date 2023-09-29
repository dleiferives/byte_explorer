# ByteExplorer

**ByteExplorer** ByteExplorer is a small **linux only** cli tool that I banged together over a weekend. It has a small text user interface (using my library [tui.h](https://github.com/dleiferives/tui).

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
   - [Example](#example)
- [Features](#features)
- [Scripting Language](#scripting-language)
- [Contributing](#contributing)
- [License](#license)

## Installation

ByteExplorer is easy to set up and run. Follow these steps to get started:

1. Clone the ByteExplorer repository to your local machine:

   ```bash
   git clone https://github.com/dleiferives/byte_explorer.git
   ```

2. Compile the code, ensuring that you have the necessary dependencies, including `terminfo` and possibly 'ncurses':

   ```bash
   gcc -o byteexplorer main.c script_manager.c -ltinfo
   ```

3. Run ByteExplorer:

   ```bash
   ./byteexplorer
   ```
   *you can optionally pass in a file as a paramater, and it will set it as the file automatically*

## Usage

ByteExplorer provides an interactive command-line interface for exploring binary files. Once you have opened a binary file, you can navigate through it, view hex data, and execute various commands to look at the data.

To get started, run ByteExplorer with a binary file as an argument:

```bash
./byteexplorer
```

The ByteExplorer tui will appear, allowing you to enter commands and perform actions on the binary file

### Example
If you have a file "data_dump"
You would run ByteExplorer
```bash
./a.out
```
Then when the tui pops up you would enter the following commands:
```
f data_dump
o
r 512
c 0
phl 512 16
```

That would display the first 512 bytes of the file. If the file is shorter than 512 bytes, it will print 0s.

### Visual Example

![ByteExplorer Demo](https://raw.githubusercontent.com/dleiferives/byte_explorer/master/output.gif)
## Features

- **Hexadecimal View:** View binary data in a hexadecimal format, making it easy to inspect the content of the file.
- **ASCII Output:** Display the ASCII representation of the binary data, allowing you to see text and characters in the file.
- **File Navigation:** Navigate through the binary file using commands to move the cursor.
- **Scripting Support:** Execute custom commands and scripts to automate tasks and perform specific actions on the file.

## Scripting Language

ByteExplorer includes a simple scripting language that allows you to create custom commands and automate repetitive tasks. The scripting language is designed for ease of use, with each command starting with a unique letter. Here are some of the available commands:

- `f s`: Set the current file to `s`.
- `o`: Open the current file for reading and navigation.
- `r #`: Read the next `#` bytes from the file.
- `ph #`: Print the next `#` bytes in hexadecimal format.
- `phl # #`: Print the next `#` bytes in groups of `#` characters.
- `pa`: Print the entire file as raw ASCII text.
- `c #`: Set the cursor to position `#`.
- `w s`: Write `s` to the screen until a newline or `'\0'` character is encountered.

You can create custom scripts by combining these commands to perform various operations on binary files.

## Contributing

Contributions to ByteExplorer are welcome! If you have suggestions, bug reports, or would like to contribute code or features, please feel free to open an issue or create a pull request. Your input is valuable in improving this tool.

## License

ByteExplorer is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

**Happy exploring!**
