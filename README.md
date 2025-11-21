# Операционные системы - Практические задания

## Обзор проекта

Этот репозиторий содержит практические задания для курса "Операционные системы". Проект начинается с BASH скриптов, а потом расширятся на программы на C, демонстрируя различные концепции системного программирования.

## Настоящее состояние

На данный момент завершено **Задание 1** с 6 последовательными commits:

- BASH системная утилита с полным определением функционала: обработка аргументов, вывод пользователей и процессов, логирование в файлы
- Комплексная документация на Markdown
- Настроенные .gitignore и README погавкам

---


# Operating Systems Course - Practice Assignments

## Project Overview

This repository contains practical assignments for an Operating Systems course. The project is structured to include both BASH scripts and C language programs demonstrating various system-level programming concepts.

## Project Structure

```
lecture-work-1.2-OC/
├── assignment1/          # BASH scripting assignment
│   ├── README.md         # Assignment 1 documentation
│   ├── system-utility.sh # Main BASH utility script
│   └── .gitkeep          # Directory marker
├── assignment2/          # C programming assignment (foundation)
│   └── .gitkeep          # Directory marker
├── .gitignore            # Git ignore patterns
└── README.md             # This file
```

## Assignments

### Assignment 1: BASH System Utility

**Location:** `assignment1/`

**Description:** A console utility written in BASH that demonstrates:
- Command-line argument parsing using `getopts`
- System information retrieval (users and processes)
- File I/O and error handling
- Output redirection to files
- Proper documentation with Markdown

**Key Features:**
- Display system users with home directories (sorted alphabetically)
- Display running processes (sorted by PID)
- Help functionality
- Logging to file with error handling
- Directory permission validation

**Usage:**
```bash
cd assignment1
./system-utility.sh -u          # Show users
./system-utility.sh -p          # Show processes
./system-utility.sh -h          # Show help
./system-utility.sh -u -l output.txt  # Log users to file
```

For detailed information, see [assignment1/README.md](assignment1/README.md)

### Assignment 2: C Programming Foundation

**Location:** `assignment2/`

**Status:** Setup phase

**Description:** Foundation for C programming assignments covering:
- System calls and libraries
- Process management
- Inter-process communication
- File operations
- Signals and event handling

## Learning Objectives

These assignments aim to provide hands-on experience with:

1. **Shell Scripting**
   - Bash syntax and features
   - Command piping and redirection
   - Parameter expansion and substitution
   - Error handling strategies

2. **System Programming** (Upcoming)
   - System calls and libraries
   - Process creation and management
   - File descriptor manipulation
   - Signal handling

3. **Best Practices**
   - Code organization and modularity
   - Documentation standards (Markdown)
   - Version control with Git
   - Error handling and validation
   - Proper project structure

## Repository Standards

### Git Conventions
- Commits are organized into logical units
- Each commit message clearly describes the changes
- Multiple commits per assignment for granular history
- Use of `.gitignore` to exclude unnecessary files

### Code Quality
- Comments explaining complex logic
- Consistent indentation and style
- Error handling for edge cases
- Input validation before processing
- Clear variable and function naming

### Documentation
- README.md in each assignment directory
- Inline code comments for clarity
- Usage examples in documentation
- Requirements compliance checklist

## Getting Started

### Prerequisites
- Bash shell (sh/bash)
- Standard Unix utilities (awk, ps, sort, etc.)
- Git for version control
- Text editor or IDE

### Cloning the Repository
```bash
git clone https://github.com/VitalikDen0/lecture-work-1.2-OC.git
cd lecture-work-1.2-OC
```

### Running Assignments

**Assignment 1:**
```bash
cd assignment1
bash system-utility.sh --help
bash system-utility.sh --users
bash system-utility.sh --processes -l output.txt
```

## Commit History

The repository maintains a clean history with descriptive commits:

- **Commit 1:** Create directory structure with assignment1 and assignment2 folders
- **Commit 2:** Add assignment2 directory to project structure
- **Commit 3:** Implement main BASH script with argument parsing using getopts
- **Commit 4:** Add comprehensive README for Assignment 1
- **Commit 5:** Add .gitignore file with common patterns
- **Commit 6:** Add main project README

## Author

**Student:** VitalikDen0

**Course:** Operating Systems (lecture-work-1.2-OC)

## References

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Unix/Linux System Programming](https://www.gnu.org/software/bash/manual/)
- [Git Documentation](https://git-scm.com/doc)
- [Markdown Guide](https://www.markdownguide.org/)

## License

This project is for educational purposes as part of an Operating Systems course.

---

**Last Updated:** 2025-11-21
