#include "hash.h"

Hash::Hash(int CacheSize) : CacheSize(CacheSize)
{
    arrHash = new hashStruct *[CacheSize];
    for (int i = 0; i < CacheSize; ++i)
    {
        arrHash[i] = NULL;
    }
};

Hash::~Hash()
{
    // hash을 순차적으로 메모리 해제
    for (int i = 0; i < CacheSize; i++)
    {
        hashStruct *_curHash = arrHash[i];
        while (_curHash != NULL)
        {
            hashStruct *temp = _curHash->nextHash;
            delete _curHash;
            _curHash = temp;
        }
    }
}

bool Hash::get(std::string key, void *&_cacheStruct)
{
    int _hashValue = generateHash(key);
    hashStruct *_indexHashStruct = arrHash[_hashValue % CacheSize];

    while (_indexHashStruct) 
    {
        if (_indexHashStruct->hashValue == _hashValue)
        {
            _cacheStruct = _indexHashStruct->cacheStructPoint;
            return true;
        }
        _indexHashStruct = _indexHashStruct->nextHash;
    }
    return false;
}

void Hash::del(std::string key)
{
    int _hashValue = generateHash(key);
    hashStruct *_curHash = arrHash[_hashValue % CacheSize];
    hashStruct *_preHash = NULL; // _preHash를 NULL로 초기화

    // 이미 _curHash 값은 NULL이 아닌 가정
    // _curHash가 무조건 존재한다는 가정
    while (_curHash != NULL)
    {
        if (_curHash->hashValue == _hashValue) // 키를 찾음
        {
            break;
        }

        _preHash = _curHash; // 이전 해시 노드로 이동
        _curHash = _curHash->nextHash;
    }

    if (_curHash == NULL) // 키를 찾지 못한 경우
    {
        return; // 아무런 작업을 하지 않고 함수 종료
    }

    if (_preHash == NULL) // _curHash가 시작 지점에 있는 경우
    {
        arrHash[_hashValue % CacheSize] = _curHash->nextHash; // 연결 리스트의 첫 번째 노드를 다음 노드로 바꿔줌
    }
    else // _curHash가 시작 지점이 아닌 경우
    {
        _preHash->nextHash = _curHash->nextHash; // 이전 노드의 다음 노드를 현재 노드의 다음 노드로 바꿔줌
    }

    delete _curHash; // 삭제할 노드 삭제
}

void Hash::add(std::string key, void *_cacheStruct)
{
    int _hashValue = generateHash(key);
    hashStruct *_indexHashStruct = arrHash[_hashValue % CacheSize];

    hashStruct *_newHash = new hashStruct;
    _newHash->cacheStructPoint = _cacheStruct;
    _newHash->hashValue = _hashValue;
    _newHash->nextHash = NULL;

    if (_indexHashStruct) // _indexHashStruct != null
    {
        while (_indexHashStruct->nextHash != NULL)
        {
            _indexHashStruct = _indexHashStruct->nextHash;
        }
        _indexHashStruct->nextHash = _newHash;
    }
    else
    {
        arrHash[_hashValue % CacheSize] = _newHash;
    }
}
