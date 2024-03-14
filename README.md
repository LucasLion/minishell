Minishell

Introduction

This repository contains the Minishell project, a requirement for the 42 cursus. It is a simplified version of the Unix shell, providing basic functionalities such as command execution, navigation, and history management.

Features:

- Command Parsing: Parses and executes basic Unix commands.
- Built-in Commands: Supports a set of built-in commands like cd, pwd, echo, env, export, unset, and exit.
- Redirection: Supports input/output redirection using <, >, and >>.
- Piping: Allows chaining of commands using the pipe (|) operator.
- History Management: Stores and retrieves command history for user convenience.
- Signal Handling: Handles common signals like SIGINT and SIGQUIT.

Getting Started

    git clone https://github.com/lucaslion/minishell.git
    cd minishell
    make
    ./minishell

Usage:

The Minishell provides a prompt where you can enter commands. To execute a command, simply type it in and press Enter. You can also use the ; character to separate multiple commands on the same line.

Contributing:

Feel free to contribute to this project by reporting bugs, suggesting improvements, or submitting pull requests.

License:

This project is licensed under the GPLv3 license.

Contact:

For any questions or feedback, please reach out to the project contributors.
