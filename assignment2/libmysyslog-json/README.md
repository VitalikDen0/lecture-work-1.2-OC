# libmysyslog-json - Драйвер JSON формата

## Описание

**libmysyslog-json** - это плагин (драйвер) для библиотеки libmysyslog, который выводит сообщения в журнал в формате JSON.

## Формат вывода

```json
{"timestamp": ..., "log_level": ..., "process": ..., "message": ...}
```

**Поля:**
- `timestamp` - Unix timestamp (число)
- `log_level` - Уровень логирования (строка)
- `process` - Имя процесса (строка)
- `message` - Текст сообщения (строка)

## Примеры вывода

```json
{"timestamp":1732176000,"log_level":"INFO","process":"myapp","message":"Application started successfully"}
{"timestamp":1732176005,"log_level":"WARN","process":"myapp","message":"Low memory warning"}
{"timestamp":1732176010,"log_level":"ERROR","process":"myapp","message":"Database connection failed"}
{"timestamp":1732176015,"log_level":"CRITICAL","process":"myapp","message":"System shutdown initiated"}
```

## Особенности

- Корректное экранирование специальных символов JSON
- Каждая запись на отдельной строке (NDJSON формат)
- Легко парсится автоматическими системами
- Поддержка многострочных сообщений

## Сборка и установка

### Требования

- GCC (GNU Compiler Collection)
- Make
- libmysyslog (основная библиотека)
- dpkg-deb (для создания deb-пакета)

### Сборка

```bash
make all      # Собрать shared library
make clean    # Очистить временные файлы
make deb      # Создать deb-пакет
```

### Установка

**Из deb-пакета:**
```bash
make deb
sudo dpkg -i libmysyslog-json_1.0.0_amd64.deb
```

**Вручную:**
```bash
make all
sudo make install
```

### Удаление

```bash
# Для deb-пакета
sudo dpkg -r libmysyslog-json

# Для ручной установки
sudo make uninstall
```

## Использование

Драйвер автоматически загружается библиотекой libmysyslog при указании типа драйвера `DRIVER_JSON`.

### Пример из C кода

```c
#include "mysyslog.h"

int main() {
    /* Использовать JSON драйвер */
    mysyslog("Test message",
             LOG_LEVEL_INFO,
             DRIVER_JSON,
             FORMAT_JSON,
             "/var/log/myapp.json");
    
    return 0;
}
```

### Пример через mysyslog-client

```bash
mysyslog-client -m "Application started" -l INFO -d json -f /var/log/app.json
```

## Технические детали

### Экранирование символов

Драйвер корректно экранирует следующие символы:
- `"` → `\"`
- `\` → `\\`
- `\n` → `\n`
- `\r` → `\r`
- `\t` → `\t`

### Формат NDJSON

Каждая запись в логе - это отдельный JSON объект на новой строке (Newline Delimited JSON). Это упрощает парсинг и обработку больших лог-файлов.

### Парсинг логов

Для парсинга JSON логов можно использовать:

```bash
# jq - процессор JSON
jq '.' /var/log/myapp.json

# Фильтрация по уровню
jq 'select(.log_level == "ERROR")' /var/log/myapp.json

# Python
python3 -c "import json; print(json.load(open('/var/log/myapp.json')))"
```

## Файлы проекта

```
libmysyslog-json/
├── README.md        # Этот файл
├── Makefile         # Сценарий сборки
└── json-driver.c    # Реализация драйвера
```

## Зависимости

Драйвер зависит от:
- **libmysyslog** (>= 1.0.0) - Основная библиотека логирования
- **Стандартная библиотека C** - для работы с файлами и временем

## Расположение файлов

После установки драйвер размещается в:
```
/usr/lib/mysyslog/libmysyslog-json.so
```

## Автор

**Студент:** VitalikDen0  
**Курс:** Операционные системы

## Лицензия

Образовательный проект
