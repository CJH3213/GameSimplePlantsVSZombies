#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class JsonValue
{
private:
	//std::string mKey;
	std::string_view mValue;

	// 跳过JsonObj，即最外层花括号的位置
	size_t SkipObj(size_t off = 0) const;
	// 跳过JsonArray
	size_t SkipArray(size_t off = 0) const;
	// 跳过字符串
	size_t SkipString(size_t off = 0) const;
	// 跳过空白字符
	size_t SkipWhiteSpace(size_t off = 0) const;

public:
	JsonValue();
	JsonValue(std::string_view value);

	bool GetBool() const;
	int GetInt() const;
	double GetDouble() const;
	std::string GetString() const;
	std::unordered_map<std::string, JsonValue> GetObjs() const;
	std::vector<JsonValue> GetArray() const;

};

