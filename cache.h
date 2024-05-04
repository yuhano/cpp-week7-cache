#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <sstream>
#include <iostream>
#include "hash.h"

#define CACHE_SIZE 10

class Cache
{
private:
  // Enhanced cache을 위한 Hash 함수
  Hash hash;

  // cacheStruct 내 value값의 타입을 알려주는 변수
  enum Type
  {
    INT,
    DOUBLE,
    NONE
  };

  // cache의 element
  struct cacheStruct
  {
    std::string key;
    Type type;
    void *value;

    cacheStruct *preCache;
    cacheStruct *nextCache;
    
    ~cacheStruct() // 구조체 삭제
    {
      if (this->type == INT)
      {
        delete static_cast<int *>(value);
      }
      else if (this->type == DOUBLE)
      {

        delete static_cast<double *>(value);
      }
    }
  };

  // 시작 cache값
  cacheStruct *startCache;

  // cache의 크기를 검사하는 함수
  // 만일 CACHE_SIZE보다 크면 맨 마지막 cache값을 지우는 역활을 한다.
  // 매 add 함수 호출 시에 해당 함수가 호출된다.
  void checkCacheSize();

  // cache값이 사용되었을 때, 사용한 값을 맨 위로 올리는 기능
  // 매 get 함수 호출 시 해당 함수가 사용된다.
  void update(cacheStruct *_updateCache);

public:
  Cache();
  ~Cache();
  // int를 cache에 추가한다
  void add(std::string key, int value);
  // double을 cache에 추가한다
  void add(std::string key, double value);
  // key에 해당하는 value를 cache에서 가져온다
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, int &value);
  // key에 해당하는 value를 cache에서 가져온다.
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, double &value);

  // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
  // 다음과 같이 표현된 문자열을 반환한다
  // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
  std::string toString();
};

#endif