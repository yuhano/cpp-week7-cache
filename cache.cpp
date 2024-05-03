#include "cache.h"

Cache::Cache()
{
    // cache construct 호출 시, null 값을 새로 생성한다.
    // 타입은 비어 있는 None 값을 넣는다.
    startCache = new cacheStruct;
    startCache->type = NONE;
    startCache->nextCache = NULL;
    startCache->preCache = NULL;
}

Cache::~Cache()
{
    // cache을 순차적으로 메모리 해제
    cacheStruct *_curCache = startCache;

    while (_curCache != NULL)
    {
        cacheStruct *temp = _curCache->nextCache;
        delete _curCache;
        _curCache = temp;
    }
}

void Cache::add(std::string key, int value)
{
    int *_tmpValue = new int(value); // int 값을 메모리 할당

    cacheStruct *_tmpStruct = new cacheStruct;
    _tmpStruct->key = key;
    _tmpStruct->value = _tmpValue;
    _tmpStruct->type = INT;

    _tmpStruct->nextCache = startCache; // 새롭게 선언된 구조체의 다음 캐시 주소를 startcache주소로 설정
    _tmpStruct->preCache = NULL;        // 새롭게 선언된 구조체의 이전 캐시 주소를 null로 설정

    startCache->preCache = _tmpStruct;  // 구)시작cache 값의 이전값 ==> 신) 새로운 값
    startCache = _tmpStruct;            // 구)시작cache 값 ==> 신) 새로운 값 주소값
    checkCacheSize();
}

void Cache::add(std::string key, double value)
{
    double *_tmpValue = new double(value); // double 값을 메모리 할당

    cacheStruct *_tmpStruct = new cacheStruct;
    _tmpStruct->key = key;
    _tmpStruct->value = _tmpValue;
    _tmpStruct->type = DOUBLE;

    _tmpStruct->nextCache = startCache; // 새롭게 선언된 구조체의 다음 캐시 주소를 startcache주소로 설정
    _tmpStruct->preCache = NULL;        // 새롭게 선언된 구조체의 이전 캐시 주소를 null로 설정

    startCache->preCache = _tmpStruct;  // 구)시작cache 값의 이전값 ==> 신) 새로운 값
    startCache = _tmpStruct;            // 구)시작cache 값 ==> 신) 새로운 값 주소값
    checkCacheSize();
}

bool Cache::get(std::string key, int &value)
{
    cacheStruct *_findCache = startCache;
    while (_findCache != NULL)
    {
        if (_findCache->key == key && _findCache->type == INT)  
        {
            update(_findCache); // 가져온 값 맨 앞으로 이동
            value = *(int *)_findCache->value; // value 값 대입

            return true;
        }
        _findCache = _findCache->nextCache;
    }

    return false;
}

bool Cache::get(std::string key, double &value)
{
    cacheStruct *_findCache = startCache;

    while (_findCache != NULL)
    {
        if (_findCache->key == key && _findCache->type == DOUBLE)
        {
            update(_findCache); // 가져온 값 맨 앞으로 이동
            value = *(double *)_findCache->value; // value 값 대입

            return true;
        }
        _findCache = _findCache->nextCache;
    }

    return false;
}

void Cache::checkCacheSize()
{
    cacheStruct *_curCache = startCache;
    int count = 0;

    while (_curCache->nextCache != NULL) // 함수 크기 측정
    {
        _curCache = _curCache->nextCache;
        count += 1;
    }

    if (count == CACHE_SIZE) // cache의 크기가 cache_size와 같으면 맨 마지막 값을 삭제
    {
        (_curCache->preCache)->nextCache = NULL;
        delete _curCache;
    }
}

void Cache::update(cacheStruct *_updateCache)
{
    if (_updateCache == startCache) // 찾으려는 값이 맨 앞이면 함수 종료
        return;
    if (_updateCache->preCache) // 찾으려는 값의 이전 값이 있으면 앞뒤로 이어주기
    {
        _updateCache->preCache->nextCache = _updateCache->nextCache;
    }
    if (_updateCache->nextCache) // 찾으려는 값의 다음 값이 있으면 앞뒤로 이어주기
    {
        _updateCache->nextCache->preCache = _updateCache->preCache;
    }
    _updateCache->nextCache = startCache; // 업데이트 하려는 cache의 다음값을 startcache 주소값으로 변경
    if (startCache)
    {
        startCache->preCache = _updateCache; 
    }
    startCache = _updateCache; // startcache의 주소를 찾으려는 주소로 변경
    _updateCache->preCache = NULL; // 찾으려는 값의 이전 주소값을 NULL로 변경
}

std::string Cache::toString()
{
    std::string result;

    cacheStruct *_current = startCache;

    while (_current != NULL)
    {
        if (_current->type == NONE)     // 초기화 변수(NONE) 값이면 건너뛰기
        {
            _current = _current->nextCache;
            continue;
        }

        result += "[";
        result += _current->key;  // key 출력
        result += ": ";
        if (_current->type == INT)   // int 출력
        {
            result += std::to_string(*(int *)_current->value);
        }
        else if (_current->type == DOUBLE)
        {
            std::ostringstream stream;
            stream.precision(5);
            stream << std::scientific << (*(double *)_current->value); // 지수 형태로 출력
            result += stream.str();
        }
        result += "] -> ";
        _current = _current->nextCache;
    }
    if (!result.empty())
    {
        result.erase(result.size() - 4); // 마지막 " -> " 지우기
    }
    result += "\n";
    return result;
}
