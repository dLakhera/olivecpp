#! bin/sh

set -xe

g++ -Wall -Wextra -ggdb -o runnable main.cpp

./runnable

# good to know
# This below converts files that are returned by ls with ppm extension to png!
# ls | grep ppm | sed 's/.ppm//' | xargs -Ixx convert xx.ppm xx.png

