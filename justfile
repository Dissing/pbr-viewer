
build:
    cd build && ninja

format:
    find src/ -iname *.h -o -iname *.cpp | xargs clang-format-14 -style=file -i

run:
    build/viewer
