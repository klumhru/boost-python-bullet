CC="ccache gcc"

all: build install

test:
	nosetests test_linear_math
	nosetests test_collision

build:
	python setup.py build

force-build:
	python setup.py build --force

install:
	python setup.py install

dev: build-mp install test

build-mp:
	CC='ccache gcc' python setup.py build --force -j
