#! bin/sh

set -xe

g++ -Wall -Wextra -ggdb -o runnable main.cpp

./runnable

# clang++ -Wall -Wextra --target=wasm32 -o wasm.o -c ./webm/render_web.cpp
# wasm-ld -m wasm32 --no-entry --export-all -allow-undefined -o ./webm/wasm.wasm ./webm/wasm.o

clang++ \
  -Wall -Wextra \
  --target=wasm32 \
  -nostdlib \
  -fno-exceptions \
  -fno-rtti \
  -c webm/render_web.cpp \
  -o webm/wasm.o

wasm-ld \
  --no-entry \
  --allow-undefined \
  webm/wasm.o \
  -o webm/wasm.wasm


# good to know
# This below converts files that are returned by ls with ppm extension to png!
# ls | grep ppm | sed 's/.ppm//' | xargs -Ixx convert xx.ppm xx.png

