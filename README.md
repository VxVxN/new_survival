## Install sfml tools

``` bash
sudo apt-get install libsfml-dev
```

## Compile and execute

``` bash
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
```