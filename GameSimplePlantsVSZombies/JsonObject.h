#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class JsonValue
{
private:
	//std::string mKey;
	std::string_view mValue;

	// ����JsonObj��������㻨���ŵ�λ��
	size_t SkipObj(size_t off = 0) const;
	// ����JsonArray
	size_t SkipArray(size_t off = 0) const;
	// �����ַ���
	size_t SkipString(size_t off = 0) const;
	// �����հ��ַ�
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

