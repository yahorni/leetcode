# vim: ft=make

# https://github.com/casey/just

task := "26"
src := task + "_task.cpp"
exe := task + "_task"

default: run

create:
	cp template.cpp {{src}}

build:
	compiler.sh ./{{src}}

run:
	./{{exe}}

git:
	git add {{src}}
	git commit -m "add task {{task}}"

rm:
	rm -f ./{{exe}}

clean:
	rm -f *_task
