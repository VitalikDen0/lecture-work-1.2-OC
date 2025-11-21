# Makefile for libmysyslog-json - JSON format driver
#
# Targets:
#   all   - Build the shared library driver
#   clean - Remove build artifacts
#   deb   - Create Debian package
#
# Author: VitalikDen0
# Course: Operating Systems

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2
LDFLAGS = -shared

# Library name and version
LIBNAME = libmysyslog-json
VERSION = 1.0.0

# Output file
LIBSO = $(LIBNAME).so

# Source files
SOURCES = json-driver.c
OBJECTS = $(SOURCES:.c=.o)

# Installation directories
PREFIX = /usr
LIBDIR = $(PREFIX)/lib/mysyslog

# Debian package directories
DEB_DIR = debian
DEB_PKG_NAME = $(LIBNAME)_$(VERSION)_amd64
DEB_PKG = $(DEB_PKG_NAME).deb

# Default target
.PHONY: all
all: $(LIBSO)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link shared library
$(LIBSO): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Clean build artifacts
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(LIBSO)
	rm -rf $(DEB_DIR) $(DEB_PKG)

# Create Debian package
.PHONY: deb
deb: all
	# Create package directory structure
	mkdir -p $(DEB_DIR)/DEBIAN
	mkdir -p $(DEB_DIR)$(LIBDIR)
	
	# Copy files
	cp $(LIBSO) $(DEB_DIR)$(LIBDIR)/
	
	# Create control file
	echo "Package: $(LIBNAME)" > $(DEB_DIR)/DEBIAN/control
	echo "Version: $(VERSION)" >> $(DEB_DIR)/DEBIAN/control
	echo "Section: libs" >> $(DEB_DIR)/DEBIAN/control
	echo "Priority: optional" >> $(DEB_DIR)/DEBIAN/control
	echo "Architecture: amd64" >> $(DEB_DIR)/DEBIAN/control
	echo "Depends: libmysyslog (>= 1.0.0)" >> $(DEB_DIR)/DEBIAN/control
	echo "Maintainer: VitalikDen0 <vitalik0denisov2016@gmail.com>" >> $(DEB_DIR)/DEBIAN/control
	echo "Description: MySyslog JSON format driver" >> $(DEB_DIR)/DEBIAN/control
	echo " Logging driver that outputs messages in JSON format." >> $(DEB_DIR)/DEBIAN/control
	
	# Build package
	dpkg-deb --build $(DEB_DIR) $(DEB_PKG)
	@echo "Package created: $(DEB_PKG)"

# Install target
.PHONY: install
install: all
	install -d $(DESTDIR)$(LIBDIR)
	install -m 0755 $(LIBSO) $(DESTDIR)$(LIBDIR)/

# Uninstall target
.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/$(LIBSO)

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all       - Build the driver library (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  deb       - Create Debian package"
	@echo "  install   - Install driver system-wide"
	@echo "  uninstall - Remove installed driver"
	@echo "  help      - Show this help message"
