#ifndef HASH_H
#define HASH_H

#include <string>
#include <sstream>
#include <iostream>

class Hash
{
private:
    const int CacheSize;

    struct hashStruct
    {
        int hashValue = -1;
        void *cacheStructPoint = NULL;
        hashStruct *nextHash = NULL;
    };
    hashStruct **arrHash;

public:
    Hash(int CacheSize);
    ~Hash();

    // key에 해당하는 value를 cacheStruct형식으로 가져온다.
    // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
    bool get(std::string key, void *&cacheStruct);

    // key에 해당하는 value를 cacheStruct형식으로 가져온다.
    // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
    void del(std::string key);

    // cacheStruct을 hash에 추가한다
    void add(std::string key, void *cacheStruct);

    // hash 함수를 생성하는 알고리즘
    // 범위: 0 ~ positive int range
    // 입력: 함수명 + 파일명 형식의 string 값 생성기
    // 입력 예제) multiply(resources/multiply_3.txt)
    static int generateHash(std::string strKey)
    {
        unsigned int hash = 0;
        for (int i = 0; i < strKey.size(); ++i)
        {
            hash = 65599 * hash + (int)strKey[i];
        }
        int a = static_cast<int>(hash);
        int b = a >= 0 ? a : a * -1;
        return b;
    }
};

#endif