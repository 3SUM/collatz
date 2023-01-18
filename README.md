# Collatz
Inspired by the Veritasium video on the Collatz conjecture

Multi-threaded `C++` program to check Collatz sequence. Program runs with total number
of concurrent threads supported via `std::thread::hardware_concurrency()`. Checks
the sequence up to `LIMIT` in `~3mins`.

### Usage

```shell
make
./collatz
```