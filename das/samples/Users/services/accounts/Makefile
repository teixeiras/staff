# This file generated by staff_codegen
# For more information please visit: http://code.google.com/p/staff/

INTERFACES := Accounts.h
COMPONENT := staff.samples.das.services
CODEGEN_WSDLS := staff.samples.das.services.Accounts.wsdl

PLATFORM ?= $(shell uname -m)
ifeq ($(shell uname -o 2>/dev/null),Msys)
  OS := MINGW
else
  OS := $(shell uname -s)
endif

ifeq ($(OS),Darwin)
  LIBPREFIX = lib
  LIBEXT = .dylib
  LDLIB = -dynamiclib -Wl,-dylib_install_name -Wl,
  CXXFLAGS += -fPIC
  LDFLAGS += -fPIC
else
ifeq (,$(filter $(OS),MINGW WINSDK))
  LIBPREFIX =
  LIBEXT = .dll
  LDLIB = -shared -Wl,-soname,
  CC = gcc
  export STAFF_HOME := $(subst :,,$(subst \,/,/$(STAFF_HOME)))
ifeq ($(OS),MINGW)
  CFLAGS += -DAXIS2_SKIP_INT_TYPEDEFS
  CXXFLAGS += -DAXIS2_SKIP_INT_TYPEDEFS
endif
else
  LIBPREFIX = lib
  LIBEXT = .so
  LDLIB = -shared -Wl,-soname,
  CXXFLAGS += -fPIC
  LDFLAGS += -fPIC
endif
endif


SRCDIR = src/
OBJDIR = obj/$(PLATFORM)/
OUTDIR = out/$(PLATFORM)/

ifneq ($(DEBUG),)
  CXXFLAGS += -D_DEBUG -g -O0
  LDFLAGS += -g -O0
endif

ifneq ($(STAFF_HOME),)
  CXXFLAGS += -I$(STAFF_HOME)/include
  LDFLAGS += -L$(STAFF_HOME)/lib
  STAFF_CODEGEN = $(STAFF_HOME)/bin/staff_codegen
  INSTALLDIR = $(STAFF_HOME)/components/
else
  STAFF_CODEGEN = staff_codegen
  INSTALLDIR = /usr/lib/staff/components/
endif


TARGETNAME = $(LIBPREFIX)$(COMPONENT)$(LIBEXT)

LDFLAGS += -lstaffutils -lstaffcommon -lstaffcomponent
LDFLAGS += $(LDLIB)$(TARGETNAME)

DATASOURCES = Users.datasources
DATATYPES = Role.datatypes
DATASOURCESPATH = ../../datasources/multiple/datasources/

CODEGEN_WSDLS_OUT := $(patsubst %,$(OUTDIR)%,$(CODEGEN_WSDLS))
CODEGEN_INTERFACES := $(patsubst %.h,$(SRCDIR)%.h,$(INTERFACES))
CODEGEN_HEADERS := $(patsubst %.h,%Wrapper.h,$(CODEGEN_INTERFACES)) $(SRCDIR)ComponentImpl.h
CODEGEN_SOURCES := $(patsubst %.h,%Wrapper.cpp,$(CODEGEN_INTERFACES)) $(SRCDIR)ComponentImpl.cpp
CODEGEN_HEADERS += $(patsubst %.datasources,$(SRCDIR)%Proxy.h,$(DATASOURCES)) $(patsubst %.datatypes,$(SRCDIR)%Proxy.h,$(DATATYPES)) $(SRCDIR)ServiceFactory.h
CODEGEN_SOURCES += $(patsubst %.datasources,$(SRCDIR)%Proxy.cpp,$(DATASOURCES)) $(patsubst %.datatypes,$(SRCDIR)%Proxy.cpp,$(DATATYPES)) $(SRCDIR)ServiceFactory.cpp
CODEGEN_DATASOURCE_HEADERS := $(patsubst %.datasources,$(SRCDIR)%.h,$(DATASOURCES)) $(patsubst %.datatypes,$(SRCDIR)%.h,$(DATATYPES))
CODEGEN_FILES := $(CODEGEN_HEADERS) $(CODEGEN_SOURCES) $(CODEGEN_DATASOURCE_HEADERS) $(CODEGEN_WSDLS_OUT)

NON_CODEGEN_SOURCES := $(filter-out $(CODEGEN_SOURCES),$(wildcard $(SRCDIR)*.cpp))
SOURCES := $(CODEGEN_SOURCES) $(NON_CODEGEN_SOURCES)
OBJECTS := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SOURCES))

.NOTPARALLEL: $(CODEGEN_FILES)

# == make ===========================================
make: "$(OBJDIR)" "$(OUTDIR)" $(OUTDIR)$(TARGETNAME)

all: make

# link
$(OUTDIR)$(TARGETNAME): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(OUTDIR)$(TARGETNAME) $(LDFLAGS)

# compile
$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NON_CODEGEN_SOURCES): $(CODEGEN_FILES)

$(SRCDIR)%Wrapper.h $(SRCDIR)%Wrapper.cpp:: $(SRCDIR)%.h
	$(STAFF_CODEGEN) -u -tcomponent -c$(SRCDIR) $(INTERFACES)

$(SRCDIR)ComponentImpl.h $(SRCDIR)ComponentImpl.cpp:: $(CODEGEN_INTERFACES)
	$(STAFF_CODEGEN) -u -tcomponent -c$(SRCDIR) $(INTERFACES)

$(SRCDIR)%Proxy.h $(SRCDIR)%Proxy.cpp: $(SRCDIR)%.h
	$(STAFF_CODEGEN) -tserviceproxy -c$(SRCDIR) $(patsubst $(SRCDIR)%,%,$(CODEGEN_DATASOURCE_HEADERS))

$(SRCDIR)%.h: $(DATASOURCESPATH)%.datasources
	$(STAFF_CODEGEN) -pdasdatasource -tinterface -i$(DATASOURCESPATH) -o$(SRCDIR) $(DATASOURCES)

$(SRCDIR)%.h: $(DATASOURCESPATH)%.datatypes
	$(STAFF_CODEGEN) -pdasdatasource -tinterface -i$(DATASOURCESPATH) -o$(SRCDIR) $(DATATYPES)

$(SRCDIR)ServiceFactory.h $(SRCDIR)ServiceFactory.cpp:: $(patsubst %,$(DATASOURCESPATH)%,$(DATASOURCES))
	$(STAFF_CODEGEN) -tserviceproxy -c$(SRCDIR) $(CODEGEN_DATASOURCE_HEADERS)

$(OUTDIR)staff.samples.das.services.Accounts.wsdl: $(SRCDIR)Accounts.h
	$(STAFF_CODEGEN) -twsdl $(patsubst $(SRCDIR)%,%,$<) -i$(SRCDIR) -o$(OUTDIR)

# == install ========================================
install: "$(INSTALLDIR)$(COMDIR)$(COMPONENT)/"
	cp -f $(OUTDIR)$(TARGETNAME) $(INSTALLDIR)$(COMDIR)$(COMPONENT)/
	cp -f $(OUTDIR)staff.samples.das.services.Accounts.wsdl $(INSTALLDIR)$(COMDIR)$(COMPONENT)/

# == uninstall ======================================
uninstall:
	rm -f $(INSTALLDIR)$(COMDIR)$(COMPONENT)/$(TARGETNAME)
	rm -f $(INSTALLDIR)$(COMDIR)$(COMPONENT)/staff.samples.das.services.Accounts.wsdl
	test ! -d $(INSTALLDIR)$(COMDIR)$(COMPONENT) || rmdir $(INSTALLDIR)$(COMDIR)$(COMPONENT)

# == clean ==========================================
clean:
	rm -f $(OUTDIR)$(TARGETNAME) $(OBJECTS) $(CODEGEN_FILES)
	-test ! -d $(OBJDIR) || rmdir -p $(OBJDIR)
	-test ! -d $(OUTDIR) || rmdir -p $(OUTDIR)

# == mkdir ==========================================
"%/":
	@[ -z "$@" -o -d "$@" ] || mkdir -p $@ && chmod g+w $@
