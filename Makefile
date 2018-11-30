
SRC			=	$(wildcard src/*/*.cpp)

SHARED_OBJ		=	$(patsubst src/%.cpp, build/shared/%.o, $(SRC))

STATIC_OBJ		=	$(patsubst src/%.cpp, build/static/%.o, $(SRC))

TESTS_SRC		=	$(wildcard tests/tests-*.cpp)

SHARED_LIB		=	libfor_libcxx.so

STATIC_LIB		=	libfor_libcxx-static.a

TESTS			=	for_libcxx-tests

CPPFLAGS		=	-isystem include -isystem lib/for_libc/include -isystem lib/for_libc/include/x86_64 -Ilib/meta/include
CXXFLAGS		=	-Wall -Wextra -nostdinc -nostdlib -fno-builtin -fno-rtti -fno-exceptions -O3 -std=c++17 -DFOR_LIBCXX_NO_EXCEPTIONS

build/shared/%.o:	src/%.cpp
			@mkdir -p $(shell dirname $@)
			$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) -fPIC $<

build/static/%.o:	src/%.cpp
			@mkdir -p $(shell dirname $@)
			$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

all:			$(SHARED_LIB) $(STATIC_LIB)

for_libc:
			$(MAKE) -C lib/for_libc all libut.a

$(STATIC_LIB):		for_libc $(STATIC_OBJ)
			ar rcs $(STATIC_LIB) $(STATIC_OBJ)

$(SHARED_LIB):		for_libc $(SHARED_OBJ)
			$(CXX) -shared -o $(SHARED_LIB) $(SHARED_OBJ)

$(TESTS):		$(STATIC_LIB) $(TESTS_LIB)
			$(CXX) $(TESTS_SRC) $(CPPFLAGS) -Ilib/for_libc/lib/ut/include -Itests/ -o $(TESTS) -Llib/for_libc -lut -lfor_libc-static $(CXXFLAGS)

tests:			$(TESTS)

clean:
			$(MAKE) -C lib/for_libc clean
			@$(RM) -r build $(STATIC_LIB) $(SHARED_LIB) $(TESTS)

re:			clean all

.PHONY:			all clean re
