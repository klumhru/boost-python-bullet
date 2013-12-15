CC="ccache gcc"

test:
	nosetests tests.py

build:
	python setup.py build

force-build:
	python setup.py build --force

install:
	python setup.py install