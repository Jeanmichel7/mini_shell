# Minishell: Your Own Little Bash

## Overview

This project is an implementation of a simple shell program that mimics some functionalities of a typical Unix shell, like Bash. In addition to the basic features such as command execution and built-ins like `echo`, `cd`, and `pwd`, the shell also supports advanced features like logical operators (`&&` and `||`) and wildcards (`*`).

---

## Table of Contents

1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Built-ins](#built-ins)
5. [Advanced Features](#advanced-features)

---

### Features

- Basic Command Execution
- Command History
- Environment Variable Expansion
- Input and Output Redirection
- Pipes
- Logical Operators (`&&`, `||`)
- Wildcards (`*`)

---

### Installation

To install Minishell, clone the repository and run `make`:

```bash
git clone https://github.com/yourusername/Minishell.git
cd Minishell
make
```

---

### Usage

To start the shell, simply run:

```bash
./minishell
```

---

### Built-ins

- `echo`: Display a message or variable
- `cd`: Change directories
- `pwd`: Print the working directory
- `export`: Export variables
- `unset`: Unset variables
- `env`: Display environment variables
- `exit`: Exit the shell

---

### Advanced Features

#### Logical Operators

You can combine commands using `&&` and `||`:

```bash
echo "This will print" && echo "This will also print"
echo "This will print" || echo "This won't print"
```

#### Wildcards

You can use the `*` wildcard to perform operations on multiple files:

```bash
ls *.txt
```

