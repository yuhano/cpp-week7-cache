# 코드에서 사용된 문법 정리

## construct

### construct 과정에서 배열 생성 방법

``` c++
// hash.h
class Hash
{
private:
    struct hashStruct
    {
        int hashValue = -1;
        void *cacheStructPoint = NULL;
        hashStruct *nextHash = NULL;
    };
    hashStruct **arrHash; // 포인터 배열
}

hash.cpp
Hash::Hash(int CacheSize) : CacheSize(CacheSize) // cache의 define을 통해 선언된 경우
{
    arrHash = new hashStruct *[CacheSize]; // 배열 선언 이후 초기화
    for (int i = 0; i < CacheSize; ++i)
    {
        arrHash[i] = NULL;
    }
};
```

### reference 연결
선언과 동시에 초기화를 진행해야지, 동일한 cache값을 보게 된다.
``` c++
class CachedRunner
{
private:
  Cache &cache;

public:
  CachedRunner(Cache &cache);
}
// CachedRunner.cpp
CachedRunner::CachedRunner(Cache &cache) : cache(cache)
{
}
```
