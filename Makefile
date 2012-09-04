all:
	python scripts/build.py
clean:
	python scripts/clean.py
install:
	cd python; python setup.py build; sudo python setup.py install
fix_locale:
	python scripts/fix_locale.py

