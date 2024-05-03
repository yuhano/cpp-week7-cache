#ifndef CACHED_RUNNER_H
#define CACHED_RUNNER_H

#include "cache.h"
#include "task_runner.h"
#include <string>

class CachedRunner
{
private:
  Cache &cache;

  int hit = 0;
  int miss = 0;

  // 함수명
  enum Type
  {
    MULTIPLY,
    PALINDROME
  };

  // 함수명 + 파일명 형식의 string 값 생성기
  // 예제) multiply(resources/multiply_3.txt)
  std::string generateKey(Type type, std::string fileName);

public:
  CachedRunner(Cache &cache);

  // 파일의 숫자를 전부 곱하여 반환한다
  double multiply(std::string filename);

  // 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
  int palindrome(std::string filename);

  // 캐시에 히트한 횟수를 반환한다
  int hits();

  // 캐시에 미스한 횟수를 반환한다
  int misses();
};

#endif