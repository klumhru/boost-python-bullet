CC="ccache gcc"

all: build install

test:
	nosetests test_linear_math
	nosetests test_collision

build:
	python setup.py build

clean:
	python setup.py clean

rebuild: clean force-build install test

force-build:
	python setup.py build --force -j

install:
	python setup.py install

dev: build-mp install test

build-mp:
	CC='ccache gcc' python setup.py build --force -j

test-hello:
	nosetests test_hello

dev-hello: build-mp install test-hello
