# CMake compile & run tests

### Individual builds and tests

```shell
rm -rf build output .cache 
cmake --preset debug
ctest --test-dir build --output-on-failure -R "^task1py$"
cmake --build build --target task1c   && ctest --test-dir build --output-on-failure -R "^task1c$"
cmake --build build --target task1cpp && ctest --test-dir build --output-on-failure -R "^task1cpp$"
cmake --build build --target task2    && ctest --test-dir build --output-on-failure -R "^task2$"
cmake --build build --target task3    && ctest --test-dir build --output-on-failure -R "^task3$"
```

### All at once

```shell
rm -rf build output .cache
cmake --preset debug
cmake --build build
ctest --test-dir build --output-on-failure
```

### VSCode

**Debug using GUI steps (code-server/vscode)**

- press `F1` > type `CMake: Select Configure Preset` -> select `debug`
- press `F1` > type `CMake: Delete Cache and Reconfigure`
- press `F1` > type `CMake: Set Build Target` -> select `all` or a single target
- press `F1` > type `CMake: Build`
- press `F1` > type `Testing: Focus on Test Explorer View` -> run/debug any of the tests via buttons

# Direct compile & run

```shell
rm -rf build output .cache
mkdir -p build output
python src/task1.test.py
gcc -std=c11 src/task1.test.c -o build/task1c       && ./build/task1c
g++ -std=c++20 src/task1.test.cpp -o build/task1cpp && ./build/task1cpp
g++ -std=c++20 src/task2.main.cpp -o build/task2    && ./build/task2   
g++ -std=c++20 src/task3*.cpp -o build/task3        && ./build/task3
```