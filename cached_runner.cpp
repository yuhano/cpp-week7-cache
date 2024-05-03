#include "cached_runner.h"

CachedRunner::CachedRunner(Cache &cache) : cache(cache)
{
}

double CachedRunner::multiply(std::string filename)
{
    double _result;
    bool isContain = cache.get(generateKey(MULTIPLY, filename), _result);

    if (isContain)
    {
        hit++;
    }
    else
    {
        miss++;
        _result = TaskRunner::multiply(filename);
        cache.add(generateKey(MULTIPLY, filename), _result);
    }

    return _result;
}

int CachedRunner::palindrome(std::string filename)
{
    int _result;
    bool isContain = cache.get(generateKey(PALINDROME, filename), _result);

    if (isContain)
    {
        hit++;
    }
    else
    {
        miss++;
        _result = TaskRunner::palindrome(filename);
        cache.add(generateKey(PALINDROME, filename), _result);
    }

    return _result;
}

int CachedRunner::hits() { return hit; }

int CachedRunner::misses() { return miss; }

std::string CachedRunner::generateKey(Type type, std::string fileName)
{
    switch (type)
    {
    case MULTIPLY:
        return "multiply(" + fileName + ")";
        break;

    case PALINDROME:
        return "palindrome(" + fileName + ")";
        break;
    default:
        return "";
        break;
    }
}