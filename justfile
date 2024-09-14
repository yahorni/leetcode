# vim: ft=make

# https://github.com/casey/just

set dotenv-load

src := "tasks/${LAST_TASK}.cpp"
exe := "${LAST_TASK}_task"

default: build run

create:
	cp template.cpp {{src}}

edit:
	${EDITOR:-nvim} {{src}}

build:
	# to check compilation process with clang: clangd --check=<file>
	g++ \
		--std=c++20 \
		-g -O0 \
		-Wall -Wextra -pedantic \
		-fsanitize=undefined \
		-fsanitize=address \
		-fsanitize=signed-integer-overflow \
		-o {{exe}} {{src}} -I./helpers/

run:
	./{{exe}}

git:
	git add -u
	git add {{src}}
	git commit -m "add task ${LAST_TASK}"

rm:
	rm -f ./{{exe}}

clean:
	rm -f *_task
