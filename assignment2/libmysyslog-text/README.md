# libmysyslog-text - Драйвер текстового формата

## Описание

**libmysyslog-text** - это плагин (драйвер) для библиотеки libmysyslog, который выводит сообщения в журнал в простом текстовом формате.

## Формат вывода

```
timestamp log_level process message
```

**Поля:**
- `timestamp` - Unix timestamp (количество секунд с 1 января 1970)
- `log_level` - Уровень логирования (DEBUG, INFO, WARN, ERROR, CRITICAL)
- `process` - Имя процесса, который записал сообщение
- `message` - Текст сообщения

## Примеры вывода

```
1732176000 INFO myapp Application started successfully
1732176005 WARN myapp Low memory warning
1732176010 ERROR myapp Database connection failed
1732176015 CRITICAL myapp System shutdown initiated
```

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
sudo dpkg -i libmysyslog-text_1.0.0_amd64.deb
```

**Вручную:**
```bash
make all
sudo make install
```

### Удаление

```bash
# Для deb-пакета
sudo dpkg -r libmysyslog-text

# Для ручной установки
sudo make uninstall
```

## Использование

Драйвер автоматически загружается библиотекой libmysyslog при указании типа драйвера `DRIVER_TEXT`.

### Пример из C кода

```c
#include "mysyslog.h"

int main() {
    /* Использовать текстовый драйвер */
    mysyslog("Test message",
             LOG_LEVEL_INFO,
             DRIVER_TEXT,
             FORMAT_TEXT,
             "/var/log/myapp.log");
    
    return 0;
}
```

### Пример через mysyslog-client

```bash
mysyslog-client -m "Application started" -l INFO -d text -f /var/log/app.log
```

## Технические детали

### Функция driver_write

Драйвер реализует функцию `driver_write`, которая вызывается библиотекой libmysyslog:

```c
int driver_write(const char* msg, int level, const char* path);
```

**Параметры:**
- `msg` - Сообщение для записи
- `level` - Уровень логирования (0-4)
- `path` - Путь к файлу лога

**Возвращаемое значение:**
- `0` - успех
- `-1` - ошибка

### Получение имени процесса

Драйвер читает имя процесса из `/proc/self/comm`, что обеспечивает корректное определение имени вызывающего процесса.

### Формат timestamp

Используется Unix timestamp (time_t), что упрощает парсинг и обработку логов автоматическими системами.

## Файлы проекта

```
libmysyslog-text/
├── README.md        # Этот файл
├── Makefile         # Сценарий сборки
└── text-driver.c    # Реализация драйвера
```

## Зависимости

Драйвер зависит от:
- **libmysyslog** (>= 1.0.0) - Основная библиотека логирования
- **Стандартная библиотека C** - для работы с файлами и временем

## Расположение файлов

После установки драйвер размещается в:
```
/usr/lib/mysyslog/libmysyslog-text.so
```

## Автор

**Студент:** VitalikDen0  
**Курс:** Операционные системы

## Лицензия

Образовательный проект
