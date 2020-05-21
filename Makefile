# TODO: Place o and d files in dedicated dirs
VERSION ?= $(shell git describe --tags --long 2>/dev/null | sed 's/\([^-]*-g\)/r\1/;s/\(.*\)-/\1./')
ASSETDIR ?= $(shell pwd)

CXXFLAGS += -Wall -Werror -pedantic -Wextra -std=c++17 -Wduplicated-cond \
						-Wduplicated-branches -Wlogical-op -Wnull-dereference \
						-Wold-style-cast -Wuseless-cast -DVERSION=\"$(VERSION)\" \
						-DASSETDIR=\"$(ASSETDIR)\" -g # -Wshadow
LDLIBS += -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS += -I include -MMD -MP

ifeq ($(VERSION),)
		VERSION := $(shell printf "r%s.%s" "$$(git rev-list --count HEAD 2>/dev/null)" \
				"$$(git rev-parse --short HEAD 2>/dev/null)")
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
		uninstall-assets release debug log install-metainfo uninstall-metainfo validate

sp9k : $(OBJ)
	$(CXX) $(LDFLAGS) -o sp9k $(OBJ) $(LOADLIBES) $(LDLIBS)

release : CXXFLAGS += -O3 -DNDEBUG
release: VERSION = $(shell git describe --tags 2> /dev/null)
release : sp9k

debug : CXXFLAGS += -Og -ggdb
debug : sp9k

-include $(DEP)

validate:
	desktop-file-validate net.phosphenius.sp9k.desktop
	appstreamcli validate net.phosphenius.sp9k.metainfo.xml

install : install-bin install-gfx install-fonts install-license install-man \
		install-doc install-launcher install-metainfo

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

install-launcher: net.phosphenius.sp9k.desktop
	install -d $(DESTDIR)$(PREFIX)/share/applications/
	install -m 644 $< $(DESTDIR)$(PREFIX)/share/applications/

install-doc: README.md
	install -d $(DESTDIR)$(PREFIX)/share/doc/sp9k/
	install -m 644 $< $(DESTDIR)$(PREFIX)/share/doc/sp9k/

install-metainfo: net.phosphenius.sp9k.metainfo.xml
# metainfo files must be located in /usr/share/metainfo
ifeq ($(PREFIX), /usr)
	install -d $(DESTDIR)$(PREFIX)/share/metainfo/
	install -m 644 $< $(DESTDIR)$(PREFIX)/share/metainfo/
else
	@echo "Omitting installation of metainfo"
endif

uninstall : uninstall-bin uninstall-man uninstall-doc uninstall-assets \
		uninstall-launcher uninstall-license uninstall-metainfo

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
	rm -f $(DESTDIR)$(PREFIX)/share/applications/net.phosphenius.sp9k.desktop

uninstall-metainfo:
ifeq ($(PREFIX), /usr)
	rm -f $(DESTDIR)$(PREFIX)/share/metainfo/net.phosphenius.sp9k.metainfo.xml
endif

log:
	journalctl -fq $(realpath sp9k)

clean :
	-rm sp9k sp9k.1.gz $(OBJ) $(DEP)
