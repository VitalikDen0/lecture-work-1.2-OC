#!/bin/bash

# System Utility - Console tool for system information display
# Author: VitalikDen0
# Description: Displays users, processes, or help information with optional logging

# Initialize variables
LOG_FILE=""
ERROR_FILE=""
OUTPUT_MODE="screen"  # screen or file

# Display help message
show_help() {
    cat << 'EOF'
Usage: system-utility.sh [OPTIONS]

Options:
  -u, --users              Display list of users and their home directories (sorted alphabetically)
  -p, --processes          Display list of running processes (sorted by PID)
  -h, --help              Display this help message
  -l, --log PATH          Log output to specified file
  -e, --errors PATH       Log errors to specified file

Examples:
  ./system-utility.sh -u
  ./system-utility.sh -p -l output.txt
  ./system-utility.sh -u -l users.txt -e errors.txt
EOF
}

# Function to display users
display_users() {
    if [ "$OUTPUT_MODE" = "file" ]; then
        awk -F':' '$3 >= 1000 {print $1, $6}' /etc/passwd | sort >> "$LOG_FILE" 2>> "$ERROR_FILE"
    else
        awk -F':' '$3 >= 1000 {print $1, $6}' /etc/passwd | sort
    fi
}

# Function to display processes
display_processes() {
    if [ "$OUTPUT_MODE" = "file" ]; then
        ps aux | sort -k 2 -n >> "$LOG_FILE" 2>> "$ERROR_FILE"
    else
        ps aux | sort -k 2 -n
    fi
}

# Main argument parsing with getopts
while getopts "uphle:-:" opt; do
    case $opt in
        u) ACTION="users" ;;
        p) ACTION="processes" ;;
        h) show_help; exit 0 ;;
        l) LOG_FILE="$OPTARG"; OUTPUT_MODE="file" ;;
        e) ERROR_FILE="$OPTARG" ;;
        -)
            case "${OPTARG}" in
                users) ACTION="users" ;;
                processes) ACTION="processes" ;;
                help) show_help; exit 0 ;;
                log) LOG_FILE="${!OPTIND}"; OPTIND=$((OPTIND + 1)); OUTPUT_MODE="file" ;;
                errors) ERROR_FILE="${!OPTIND}"; OPTIND=$((OPTIND + 1)) ;;
                *) echo "Unknown option: $OPTARG"; show_help; exit 1 ;;
            esac
            ;;
        *) echo "Invalid option: $opt"; show_help; exit 1 ;;
    esac
done

# Verify file paths if logging is enabled
if [ "$OUTPUT_MODE" = "file" ]; then
    if [ -z "$LOG_FILE" ]; then
        echo "Error: Log file path required with -l option" >&2
        exit 1
    fi
    
    # Check if log file directory is writable
    LOG_DIR=$(dirname "$LOG_FILE")
    if [ ! -w "$LOG_DIR" ]; then
        echo "Error: Cannot write to directory $LOG_DIR" >&2
        exit 1
    fi
fi

if [ -n "$ERROR_FILE" ]; then
    ERROR_DIR=$(dirname "$ERROR_FILE")
    if [ ! -w "$ERROR_DIR" ]; then
        echo "Error: Cannot write to directory $ERROR_DIR" >&2
        exit 1
    fi
fi

# Execute action based on argument
case "${ACTION}" in
    users) display_users ;;
    processes) display_processes ;;
    *) echo "No action specified. Use -h for help."; exit 1 ;;
esac
