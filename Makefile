all: build run

run:
	./build/pog

.PHONY: build
.SILENT:
build:
	@cmake --build ./build --target=pog
	@cp ./build/compile_commands.json .

gen:
	cd ./build && cmake .. -G "Unix Makefiles"
