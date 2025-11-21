# Задание 1 - Консольный инструмент системной утилиты

## Обзор

Это задание реализует консольную утилиту на bash, которая обрабатывает аргументы командной строки и отображает системную информацию.

## Требования

### 1. Аргументы командной строки

- Поддержка коротких (-u, -p, -h, -l, -e) и длинных (--users, --processes, --help, --log, --errors) форм аргументов
- Парсинг аргументов с использованием `getopts` или `getopt` механизмов

## 2. Функциональность

#### `-u / --users`
- Отображает список пользователей и их домашних директорий
- Сортирует вывод в алфавитном порядке по имени пользователя

#### `-p / --processes`
- Отображает список запущенных процессов
- Сортирует вывод по идентификатору процесса (PID)

#### `-h / --help`
- Отображает справку с доступными опциями и примерами использования
- Завершает программу после отображения справки

#### `-l PATH / --log PATH`
- Перенаправляет стандартный вывод в указанный файл
- Обрабатывает ошибки доступа и прав на директорию

#### `-e PATH / --errors PATH`
- Перенаправляет поток ошибок в указанный файл
- Обрабатывает ошибки доступа и прав на директорию

## Примеры использования

\`\`\`bash
# Отображение пользователей
./system-utility.sh -u
./system-utility.sh --users
\`\`\`

---

# Assignment 1 - System Utility Console Tool

## Overview

This assignment implements a bash console utility that processes command-line arguments and displays system information.

## Requirements

### 1. Command-line Arguments
- Support short (`-u`, `-p`, `-h`, `-l`, `-e`) and long (`--users`, `--processes`, `--help`, `--log`, `--errors`) argument forms
- Argument parsing using `getopts` or `getopt` mechanisms

### 2. Functionality

#### `-u / --users`
- Display list of users and their home directories
- Sort output alphabetically by username

#### `-p / --processes`
- Display list of running processes
- Sort output by Process ID (PID)

#### `-h / --help`
- Display help message with available options and usage examples
- Exit program after displaying help

#### `-l PATH / --log PATH`
- Redirect standard output to specified file
- Handles file access and directory permissions

#### `-e PATH / --errors PATH`
- Redirect stderr to specified file
- Handles file access and directory permissions

## Usage Examples

```bash
# Display users
./system-utility.sh -u
./system-utility.sh --users

# Display processes
./system-utility.sh -p
./system-utility.sh --processes

# Display help
./system-utility.sh -h
./system-utility.sh --help

# Log output to file
./system-utility.sh -u -l output.txt
./system-utility.sh -p --log processes.log

# Log errors to file
./system-utility.sh -u -e errors.txt

# Combined logging
./system-utility.sh -u -l users.txt -e errors.txt
```

## Implementation Details

### Code Organization
- **Argument parsing**: Uses `getopts` for robust command-line processing
- **Separate functions**: Each action (users, processes) implemented in dedicated functions
- **Error handling**: Validates file paths and directory permissions before writing
- **Output redirection**: Supports both screen and file output modes

### Error Messages
- Program checks write access to target directories
- Proper error reporting through stderr
- Graceful exit with appropriate error codes

## File Structure

```
assignment1/
├── README.md           # This file
├── system-utility.sh   # Main utility script
└── .gitkeep            # Placeholder for directory
```

## Requirements Compliance

- ✅ Argument parsing with `getopts`
- ✅ Separate functions for each action type
- ✅ Support for both short and long arguments
- ✅ File path access validation
- ✅ Directory permission checking
- ✅ Error stream filtering and handling
- ✅ Proper exit codes

## Notes

- The utility uses standard Linux commands (`awk`, `ps`, `sort`)
- User filtering includes only system users (UID >= 1000)
- Process sorting is done by PID for consistent ordering
