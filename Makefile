.PHONY: build
do:
	cmake -S . -B build
	cmake --build build

run:
	cd build && ./BURZA
