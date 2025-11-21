# Assignment 2: MySyslog - Extensible Logging System

## Описание проекта

MySyslog - это расширяемая система логирования на языке C, состоящая из нескольких компонентов:
- Основная библиотека с поддержкой плагинов
- Драйверы для различных форматов логирования
- Клиентское приложение для тестирования
- Демон для автоматического логирования

## Структура проекта

```
assignment2/
├── README.md                    # Этот файл
├── Makefile                     # Главный Makefile для сборки всех компонентов
├── libmysyslog/                 # Основная библиотека логирования
│   ├── README.md
│   ├── Makefile
│   ├── mysyslog.h
│   └── mysyslog.c
├── libmysyslog-text/            # Драйвер текстового формата
│   ├── README.md
│   ├── Makefile
│   └── text-driver.c
├── libmysyslog-json/            # Драйвер JSON формата
│   ├── README.md
│   ├── Makefile
│   └── json-driver.c
├── mysyslog-client/             # Тестовое клиентское приложение
│   ├── README.md
│   ├── Makefile
│   └── client.c
├── mysyslog-daemon/             # Демон автоматического логирования
│   ├── README.md
│   ├── Makefile
│   ├── daemon.c
│   └── mysyslog.cfg.example
├── mysyslog-meta/               # Метапакет для установки всех компонентов
│   └── DEBIAN/
│       └── control
└── repository/                  # Локальный репозиторий deb-пакетов
```

## Компоненты системы

### 1. libmysyslog - Основная библиотека

**Описание:** Расширяемая библиотека с поддержкой динамической загрузки драйверов через `dlopen/dlsym/dlclose`.

**Основная функция:**
```c
int mysyslog(const char* msg, int level, int driver, int format, const char* path);
```

**Уровни логирования:**
- DEBUG (0)
- INFO (1)
- WARN (2)
- ERROR (3)
- CRITICAL (4)

### 2. libmysyslog-text - Драйвер текстового формата

**Формат вывода:**
```
timestamp log_level process message
```

**Пример:**
```
1439482969 ERROR example-app this is an error
```

### 3. libmysyslog-json - Драйвер JSON формата

**Формат вывода:**
```json
{"timestamp": ..., "log_level": ..., "process": ..., "message": ...}
```

**Пример:**
```json
{"timestamp":1439482969,"log_level":"ERROR","process":"example-app","message":"this is an error"}
```

### 4. mysyslog-client - Клиентское приложение

Консольное приложение для тестирования библиотеки с поддержкой аргументов командной строки через `getopt`.

**Использование:**
```bash
mysyslog-client -m "Test message" -l INFO -d text -f /var/log/mysyslog.log
```

**Аргументы:**
- `-m, --message` - Сообщение для записи в лог
- `-l, --level` - Уровень логирования (DEBUG/INFO/WARN/ERROR/CRITICAL)
- `-d, --driver` - Используемый драйвер (text/json)
- `-f, --file` - Путь к файлу лога
- `-h, --help` - Справка

### 5. mysyslog-daemon - Демон логирования

Системный демон, запускающийся автоматически при старте системы через `systemd`.

**Конфигурация:** `/etc/mysyslog/mysyslog.cfg`

**Управление:**
```bash
sudo systemctl start mysyslog-daemon
sudo systemctl stop mysyslog-daemon
sudo systemctl status mysyslog-daemon
sudo systemctl enable mysyslog-daemon  # Автозапуск
```

## Сборка проекта

### Требования

- GCC (GNU Compiler Collection)
- Make
- json-c library (для JSON драйвера)
- dpkg-deb (для создания deb-пакетов)
- systemd (для демона)

**Установка зависимостей (Debian/Ubuntu/AstraLinux):**
```bash
sudo apt-get update
sudo apt-get install build-essential libjson-c-dev dpkg-dev
```

### Полная сборка всех компонентов

```bash
cd assignment2
make all        # Собрать все компоненты
make clean      # Очистить временные файлы
make deb        # Создать все deb-пакеты
make repo       # Создать репозиторий из пакетов
```

### Сборка отдельных компонентов

```bash
make libmysyslog          # Основная библиотека
make libmysyslog-text     # Текстовый драйвер
make libmysyslog-json     # JSON драйвер
make mysyslog-client      # Клиент
make mysyslog-daemon      # Демон
```

## Установка из репозитория

### 1. Настройка репозитория на клиенте

```bash
# Добавить репозиторий в sources.list
echo "deb [trusted=yes] file:///path/to/assignment2/repository ./" | \
    sudo tee /etc/apt/sources.list.d/mysyslog.list

# Обновить список пакетов
sudo apt-get update
```

### 2. Установка метапакета

```bash
# Установить все компоненты сразу
sudo apt-get install mysyslog-meta

# Или установить компоненты по отдельности
sudo apt-get install libmysyslog libmysyslog-text libmysyslog-json
sudo apt-get install mysyslog-client mysyslog-daemon
```

## Использование

### Клиентское приложение

```bash
# Записать сообщение с уровнем ERROR в текстовом формате
mysyslog-client -m "Database connection failed" -l ERROR -d text -f /var/log/app.log

# Записать сообщение в JSON формате
mysyslog-client -m "User logged in" -l INFO -d json -f /var/log/app.json

# Критическая ошибка
mysyslog-client -m "Out of memory" -l CRITICAL -d text -f /var/log/critical.log
```

### Демон

```bash
# Запустить демон
sudo systemctl start mysyslog-daemon

# Проверить статус
sudo systemctl status mysyslog-daemon

# Просмотреть логи демона
sudo journalctl -u mysyslog-daemon -f

# Просмотреть созданные логи
tail -f /var/log/mysyslog/daemon.log
```

### Конфигурация демона

Файл `/etc/mysyslog/mysyslog.cfg`:
```ini
# MySyslog Daemon Configuration
path=/var/log/mysyslog/daemon.log
format=text
driver=text
interval=5
```

## Архитектура и технические детали

### Динамическая загрузка драйверов

Библиотека использует POSIX API для динамической загрузки:
- `dlopen()` - Загрузка shared library
- `dlsym()` - Получение указателя на функцию
- `dlclose()` - Выгрузка библиотеки

### Обработка сигналов в демоне

Демон корректно обрабатывает системные сигналы:
- `SIGTERM` - Корректное завершение
- `SIGHUP` - Перечитывание конфигурации
- `SIGINT` - Прерывание (при отладке)

### Стандарты кодирования

Код следует GNU C Coding Standards:
- Отступы: 2 пробела
- Максимальная длина строки: 80 символов
- Комментарии в стиле `/* ... */`
- Имена функций: `lowercase_with_underscores`

## Зависимости пакетов

```
mysyslog-meta
    └─ libmysyslog
    └─ libmysyslog-text
    └─ libmysyslog-json
    └─ mysyslog-client (depends on libmysyslog)
    └─ mysyslog-daemon (depends on libmysyslog, libmysyslog-text, libmysyslog-json)
```

## Тестирование

### Тест клиента

```bash
# Создать тестовый лог-файл
mkdir -p /tmp/mysyslog-test

# Записать несколько сообщений
mysyslog-client -m "Test DEBUG" -l DEBUG -d text -f /tmp/mysyslog-test/test.log
mysyslog-client -m "Test INFO" -l INFO -d text -f /tmp/mysyslog-test/test.log
mysyslog-client -m "Test ERROR" -l ERROR -d json -f /tmp/mysyslog-test/test.json

# Проверить содержимое
cat /tmp/mysyslog-test/test.log
cat /tmp/mysyslog-test/test.json
```

### Тест демона

```bash
# Запустить демон
sudo systemctl start mysyslog-daemon

# Подождать 30 секунд
sleep 30

# Проверить созданные логи
sudo cat /var/log/mysyslog/daemon.log

# Остановить демон
sudo systemctl stop mysyslog-daemon
```

## Структура deb-пакетов

Каждый компонент создает отдельный deb-пакет:

1. **libmysyslog** - Основная библиотека
2. **libmysyslog-text** - Драйвер текстового формата
3. **libmysyslog-json** - Драйвер JSON формата
4. **mysyslog-client** - Клиентское приложение
5. **mysyslog-daemon** - Системный демон
6. **mysyslog-meta** - Метапакет для установки всех компонентов

## Ссылки на изученные материалы

- [Git ignore patterns](https://git-scm.com/docs/gitignore)
- [C .gitignore template](https://github.com/github/gitignore/blob/main/C.gitignore)
- [Markdown Guide](https://guides.github.com/features/mastering-markdown/)
- [GNU C Coding Standards](https://www.gnu.org/prep/standards/html_node/Writing-C.html)
- [dlopen examples](https://github.com/skuhl/sys-prog-examples/tree/master/linking-types-example)
- [Makefile tutorial](https://github.com/skuhl/sys-prog-examples/blob/master/make-example/Makefile)
- [getopt example](https://gist.github.com/thaim/7895785)
- [Daemon example](https://github.com/jirihnidek/daemon/blob/master/src/daemon.c)
- [Simple logging](https://gist.github.com/fclairamb/7441750)
- [Structured logger](https://github.com/briandowns/struCtured-logger)
- [Deb package tutorial](https://github.com/gl0v4nnl/Deb-package-simple-example)
- [AstraLinux repository guide](https://wiki.astralinux.ru/pages/viewpage.action?pageId=61575159)

## Автор

**Студент:** VitalikDen0  
**Курс:** Операционные системы

## Лицензия

Образовательный проект в рамках курса "Операционные системы"

---

**Последнее обновление:** 2025-11-21
