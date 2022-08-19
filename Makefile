all: build run

run:
	./build/pog

.PHONY: build
.SILENT:
build:
	@cmake --build ./build --target=pog
	@cp ./build/compile_commands.json .

install:
	@cmake --build ./build --target=install --config=Release
	@cp ./build/compile_commands.json .

gen:
	mkdir -p ./build && cd ./build && cmake .. -G "Unix Makefiles" -D CMAKE_INSTALL_PREFIX=stage

clean:
	rm -rf build
