# libmysyslog - Основная библиотека логирования

## Описание

**libmysyslog** - это расширяемая библиотека логирования на языке C, которая позволяет выводить данные в журнал в различных форматах через динамически подключаемые драйверы (plugins).

Библиотека использует POSIX API для динамической загрузки (`dlopen`, `dlsym`, `dlclose`), что позволяет добавлять новые форматы логирования без перекомпиляции основной библиотеки.

## Особенности

- Поддержка 5 уровней логирования (DEBUG, INFO, WARN, ERROR, CRITICAL)
- Динамическая загрузка драйверов во время выполнения
- Расширяемая архитектура (легко добавить новые форматы)
- Поддержка нескольких путей поиска драйверов (локальные и системные)
- Соответствие GNU C Coding Standards

## API

### Основная функция

```c
int mysyslog(const char* msg, int level, int driver, int format, const char* path);
```

**Параметры:**
- `msg` - Сообщение для записи в лог
- `level` - Уровень логирования (0-4)
- `driver` - Тип драйвера (DRIVER_TEXT или DRIVER_JSON)
- `format` - Формат вывода (FORMAT_TEXT или FORMAT_JSON)
- `path` - Путь к файлу лога

**Возвращаемое значение:**
- `0` - успех
- `-1` - ошибка

### Уровни логирования

```c
#define LOG_LEVEL_DEBUG    0  // Отладочные сообщения
#define LOG_LEVEL_INFO     1  // Информационные сообщения
#define LOG_LEVEL_WARN     2  // Предупреждения
#define LOG_LEVEL_ERROR    3  // Ошибки
#define LOG_LEVEL_CRITICAL 4  // Критические ошибки
```

### Типы драйверов

```c
#define DRIVER_TEXT 0  // Драйвер текстового формата
#define DRIVER_JSON 1  // Драйвер JSON формата
```

### Вспомогательные функции

```c
const char* get_level_name(int level);  // Получить имя уровня логирования
void* load_driver(int driver);          // Загрузить драйвер
void unload_driver(void* handle);       // Выгрузить драйвер
```

## Пример использования

### Простой пример

```c
#include "mysyslog.h"

int main() {
    /* Записать сообщение в текстовом формате */
    mysyslog("Application started", 
             LOG_LEVEL_INFO,
             DRIVER_TEXT,
             FORMAT_TEXT,
             "/var/log/myapp.log");
    
    /* Записать ошибку в JSON формате */
    mysyslog("Database connection failed",
             LOG_LEVEL_ERROR,
             DRIVER_JSON,
             FORMAT_JSON,
             "/var/log/myapp.json");
    
    return 0;
}
```

### Компиляция

```bash
gcc -o myapp myapp.c -lmysyslog -ldl
```

## Сборка и установка

### Требования

- GCC (GNU Compiler Collection)
- Make
- dpkg-deb (для создания deb-пакета)

### Сборка библиотеки

```bash
make all      # Собрать shared library
make clean    # Очистить временные файлы
make deb      # Создать deb-пакет
```

### Установка

**Из deb-пакета:**
```bash
make deb
sudo dpkg -i libmysyslog_1.0.0_amd64.deb
```

**Вручную:**
```bash
make all
sudo make install
```

### Удаление

```bash
# Для deb-пакета
sudo dpkg -r libmysyslog

# Для ручной установки
sudo make uninstall
```

## Архитектура

### Динамическая загрузка драйверов

Библиотека использует следующий подход для загрузки драйверов:

1. **dlopen()** - Загрузка shared library драйвера
2. **dlsym()** - Получение указателя на функцию `driver_write`
3. **Вызов функции** - Запись данных в лог
4. **dlclose()** - Выгрузка драйвера

### Пути поиска драйверов

Библиотека ищет драйверы в следующем порядке:

1. **Локальный путь:** `./libmysyslog-text.so` или `./libmysyslog-json.so`
2. **Системный путь:** `/usr/lib/mysyslog/libmysyslog-*.so`

### Интерфейс драйвера

Каждый драйвер должен реализовывать функцию:

```c
int driver_write(const char* msg, int level, const char* path);
```

**Параметры:**
- `msg` - Сообщение для записи
- `level` - Уровень логирования
- `path` - Путь к файлу лога

## Файлы проекта

```
libmysyslog/
├── README.md         # Этот файл
├── Makefile          # Сценарий сборки
├── mysyslog.h        # Заголовочный файл
└── mysyslog.c        # Реализация библиотеки
```

## Зависимости

Библиотека требует:
- **libdl** - Для динамической загрузки
- **Драйверы** - libmysyslog-text или libmysyslog-json (устанавливаются отдельно)

## Разработка собственных драйверов

Для создания собственного драйвера:

1. Создайте файл с реализацией функции `driver_write`
2. Скомпилируйте в shared library
3. Разместите в `/usr/lib/mysyslog/`
4. Добавьте поддержку нового типа в `mysyslog.h` и `mysyslog.c`

## Тестирование

Библиотеку можно протестировать с помощью:
- **mysyslog-client** - Клиентское приложение для тестов
- **mysyslog-daemon** - Демон для автоматического логирования

## Автор

**Студент:** VitalikDen0  
**Курс:** Операционные системы

## Лицензия

Образовательный проект
