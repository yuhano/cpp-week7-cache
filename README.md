# cpp-week7-Basic-LRU-cache

>  c++ 프로그래밍 7주차 과제

# 📖 Description

c++ 프로그래밍 7주차 과제입니다. 

Basic LRU cache 알고리즘 및 hash 함수 구현

## 🕰️ 개발 기간
24.04.15일 - 24.05.05일


## 💻 Getting Started

### 실방 방법
* cache
```
$ git clone https://github.com/yuhano/cpp-week7-cache cache
$ cd cache
$ mingw32-make
$ .\main.exe

```
### cache 크기 조절
cache.h
``` c++
#define CACHE_SIZE 10
```

## 🔧 Stack
- **Language**: c++ 

##  Project Structure

```markdown
cpp-week7
└── cache
    ├── script // task 구현
    ├── task.h, task_runner.h   // task 구현
    |    
    ├── cache.h         // linkedlist을 이용한 basic cache 구현
    ├── cache_runner.h  // cache에 값이 있는지 확인 및 task 요청 
    └── hash.h          // chaining을 이용하여 hash table 구현

```