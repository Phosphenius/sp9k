# TODO: Place o and d files in dedicated dirs
VERSION ?= $(shell git describe --long 2>/dev/null | sed 's/\([^-]*-g\)/r\1/;s/-/./g')
ASSETDIR ?= $(shell pwd)

CXXFLAGS += -Wall -Werror -pedantic -Wextra -std=c++17 -Wduplicated-cond \
						-Wduplicated-branches -Wlogical-op -Wnull-dereference \
						-Wold-style-cast -Wuseless-cast -DVERSION=\"$(VERSION)\" \
						-DASSETDIR=\"$(ASSETDIR)\" -g # -Wshadow
LDLIBS += -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS += -I include -MMD -MP

ifeq ($(VERSION),)
		VERSION := $(shell printf "r%s.%s" "$$(git rev-list --count HEAD)" \
				"$$(git rev-parse --short HEAD)")
endif

SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEP := $(patsubst %.cpp, %.d, $(SRC))

OBJDIR = .objs

DESTDIR ?=
PREFIX ?= /usr/local
BINDIR ?= /bin

.PHONY: clean install uninstall install-bin uninstall-bin install-doc \
		uninstall-doc install-license uninstall-license install-launcher \
		uninstall-launcher install-man uninstall-man install-% \
		uninstall-assets release debug

sp9k : $(OBJ)
	$(CXX) $(LDFLAGS) -o sp9k $(OBJ) $(LOADLIBES) $(LDLIBS)

release : CXXFLAGS += -O3 -DNDEBUG
release : ASSETDIR = $(DESTDIR)$(PREFIX)/share/sp9k/
release : sp9k

debug : CXXFLAGS += -Og -ggdb
debug : sp9k

-include $(DEP)

install : install-bin install-gfx install-fonts install-license install-man \
		install-doc install-launcher

install-bin: sp9k
	install -d $(DESTDIR)$(PREFIX)$(BINDIR)/
	install -m 755 $< $(DESTDIR)$(PREFIX)$(BINDIR)/

install-%: % 
	install -d $(DESTDIR)$(PREFIX)/share/sp9k/$<
	install -m 644 -t $(DESTDIR)$(PREFIX)/share/sp9k/$< $</*

install-license: LICENSE
	install -d $(DESTDIR)$(PREFIX)/share/licenses/sp9k/
	install -m 644 $< $(DESTDIR)$(PREFIX)/share/licenses/sp9k/

install-man: sp9k.1.gz
	install -d $(DESTDIR)$(PREFIX)/share/man/man1/
	install -m 644 $< $(DESTDIR)$(PREFIX)/share/man/man1/

sp9k.1.gz : sp9k.1
	gzip -f -k $<

install-launcher: sp9k.desktop
	install -d $(DESTDIR)$(PREFIX)/share/applications/
	install -m 644 $< $(DESTDIR)$(PREFIX)/share/applications/

install-doc: README.md
	install -d $(DESTDIR)$(PREFIX)/share/doc/sp9k/
	install -m 644 $< $(DESTDIR)$(PREFIX)/share/doc/sp9k/

uninstall : uninstall-bin uninstall-man uninstall-doc uninstall-assets \
		uninstall-launcher uninstall-license

uninstall-bin :
	rm -f $(DESTDIR)$(PREFIX)$(BINDIR)/sp9k

uninstall-man:
	rm -f $(DESTDIR)$(PREFIX)/share/man/man1/sp9k.1.gz

uninstall-doc:
	rm -rf $(DESTDIR)$(PREFIX)/share/doc/sp9k/

uninstall-license:
	rm -rf $(DESTDIR)$(PREFIX)/share/licenses/sp9k/

uninstall-assets:
	rm -rf $(DESTDIR)$(PREFIX)/share/sp9k/

uninstall-launcher:
	rm -f $(DESTDIR)$(PREFIX)/share/applications/sp9k.desktop

clean :
	-rm sp9k sp9k.1.gz $(OBJ) $(DEP)
