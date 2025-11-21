# Makefile for libmysyslog - Main logging library
#
# Targets:
#   all   - Build the shared library
#   clean - Remove build artifacts
#   deb   - Create Debian package
#
# Author: VitalikDen0
# Course: Operating Systems

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2
LDFLAGS = -shared -ldl

# Library name and version
LIBNAME = libmysyslog
VERSION = 1.0.0
SOVERSION = 1

# Output files
LIBSO = $(LIBNAME).so.$(VERSION)
LIBSONAME = $(LIBNAME).so.$(SOVERSION)
LIBLINK = $(LIBNAME).so

# Source files
SOURCES = mysyslog.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = mysyslog.h

# Installation directories
PREFIX = /usr
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include

# Debian package directories
DEB_DIR = debian
DEB_PKG_NAME = $(LIBNAME)_$(VERSION)_amd64
DEB_PKG = $(DEB_PKG_NAME).deb

# Default target
.PHONY: all
all: $(LIBSO)

# Compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link shared library
$(LIBSO): $(OBJECTS)
	$(CC) $(LDFLAGS) -Wl,-soname,$(LIBSONAME) -o $@ $^
	ln -sf $(LIBSO) $(LIBSONAME)
	ln -sf $(LIBSONAME) $(LIBLINK)

# Clean build artifacts
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(LIBSO) $(LIBSONAME) $(LIBLINK)
	rm -rf $(DEB_DIR) $(DEB_PKG)

# Create Debian package
.PHONY: deb
deb: all
	# Create package directory structure
	mkdir -p $(DEB_DIR)/DEBIAN
	mkdir -p $(DEB_DIR)$(LIBDIR)
	mkdir -p $(DEB_DIR)$(INCLUDEDIR)
	
	# Copy files
	cp $(LIBSO) $(DEB_DIR)$(LIBDIR)/
	cp $(HEADERS) $(DEB_DIR)$(INCLUDEDIR)/
	
	# Create symlinks in package
	cd $(DEB_DIR)$(LIBDIR) && ln -sf $(LIBSO) $(LIBSONAME)
	cd $(DEB_DIR)$(LIBDIR) && ln -sf $(LIBSONAME) $(LIBLINK)
	
	# Create control file
	echo "Package: $(LIBNAME)" > $(DEB_DIR)/DEBIAN/control
	echo "Version: $(VERSION)" >> $(DEB_DIR)/DEBIAN/control
	echo "Section: libs" >> $(DEB_DIR)/DEBIAN/control
	echo "Priority: optional" >> $(DEB_DIR)/DEBIAN/control
	echo "Architecture: amd64" >> $(DEB_DIR)/DEBIAN/control
	echo "Maintainer: VitalikDen0 <vitalik0denisov2016@gmail.com>" >> $(DEB_DIR)/DEBIAN/control
	echo "Description: MySyslog extensible logging library" >> $(DEB_DIR)/DEBIAN/control
	echo " Main library for the MySyslog logging system with support" >> $(DEB_DIR)/DEBIAN/control
	echo " for dynamically loaded drivers." >> $(DEB_DIR)/DEBIAN/control
	
	# Build package
	dpkg-deb --build $(DEB_DIR) $(DEB_PKG)
	@echo "Package created: $(DEB_PKG)"

# Install target (for manual installation)
.PHONY: install
install: all
	install -d $(DESTDIR)$(LIBDIR)
	install -d $(DESTDIR)$(INCLUDEDIR)
	install -m 0755 $(LIBSO) $(DESTDIR)$(LIBDIR)/
	ln -sf $(LIBSO) $(DESTDIR)$(LIBDIR)/$(LIBSONAME)
	ln -sf $(LIBSONAME) $(DESTDIR)$(LIBDIR)/$(LIBLINK)
	install -m 0644 $(HEADERS) $(DESTDIR)$(INCLUDEDIR)/
	ldconfig

# Uninstall target
.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/$(LIBSO)
	rm -f $(DESTDIR)$(LIBDIR)/$(LIBSONAME)
	rm -f $(DESTDIR)$(LIBDIR)/$(LIBLINK)
	rm -f $(DESTDIR)$(INCLUDEDIR)/$(HEADERS)
	ldconfig

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all       - Build the shared library (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  deb       - Create Debian package"
	@echo "  install   - Install library system-wide"
	@echo "  uninstall - Remove installed library"
	@echo "  help      - Show this help message"
