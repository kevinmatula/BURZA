.PHONY: build
cook:
	cmake -S . -B build
	cmake --build build

eat:
	cd build && ./BURZA
