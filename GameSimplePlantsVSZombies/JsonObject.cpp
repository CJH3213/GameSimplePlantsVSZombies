#include "JsonObject.h"
#include <stdexcept>
#include <algorithm>

size_t JsonValue::SkipObj(size_t off) const
{
	int count = 0;		// ��¼�����Ÿ���

	for (size_t i = off; i < mValue.size(); ++i)
	{
		if (mValue[i] == '{')
			++count;
		else if (mValue[i] == '}')
		{
			--count;
			if (count == 0)
				return i;  // �����һ����ŵ�λ��
		}
	}

	return std::string::npos;  // ���û���ҵ�ƥ����һ����ţ�����npos
}

size_t JsonValue::SkipArray(size_t off) const
{
	int count = 0;		// ��¼�����Ÿ���

	for (size_t i = off; i < mValue.size(); ++i)
	{
		if (mValue[i] == '[')
			++count;
		else if (mValue[i] == ']')
		{
			--count;
			if (count == 0)
				return i;  // �����һ����ŵ�λ��
		}
	}

	return std::string::npos;  // ���û���ҵ�ƥ����ҷ����ţ�����npos
}

size_t JsonValue::SkipString(size_t off) const
{
	size_t count = 0;

	for (size_t i = off; i < mValue.size(); ++i)
	{
		if (mValue[i] == '\"')
		{
			// ת������Ų���
			if (i > 0 && mValue[i - 1] == '\\')
				continue;

			if (++count == 2)
				return i;
		}
	}

	return std::string::npos;
}

size_t JsonValue::SkipWhiteSpace(size_t off) const
{
	// �����հ��ַ����ո񡢻س������С�ˮƽ�Ʊ���ֱ�Ʊ���ҳ
	return mValue.find_first_not_of(" \r\n\t\v\f", off);
}

JsonValue::JsonValue() :
	mValue()
{
}

JsonValue::JsonValue(std::string_view value) :
	mValue(value)
{
}

bool JsonValue::GetBool() const
{
	// ���ַ���ת��ΪСд
	std::string str( mValue.substr(0, 5));
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return std::tolower(c);
		});

	if (mValue == "true")
		return true;
	else if (mValue == "false")
		return false;
	else
		throw std::invalid_argument("Json Value Is Not Bool Type");
}

int JsonValue::GetInt() const
{
	return std::stoi(std::string(mValue));
}

double JsonValue::GetDouble() const
{
	return std::stod(std::string(mValue));
}

std::string JsonValue::GetString() const
{
	if (mValue[0] == '\"')	// ȥ��˫����
		return std::string(mValue.substr(1, mValue.size() - 2));
	else
		return std::string(mValue);
}

std::unordered_map<std::string, JsonValue> JsonValue::GetObjs() const
{
	std::unordered_map<std::string, JsonValue> objs;

	size_t beginPos = mValue.find('{');
	if (beginPos == std::string::npos)
		throw std::invalid_argument("Json Value Is Not Object Type");

	size_t valueEndPos = beginPos;
	while (valueEndPos != std::string::npos)
	{
		// ÿһ��ѭ������һ��Json�����ֵ��

		// Ѱ������
		size_t quoteLPos = mValue.find('\"', valueEndPos + 1);
		size_t quoteRPos = SkipString(quoteLPos);
		// ������������ȡΪkey
		if (quoteRPos != std::string::npos)
		{
			std::string key(mValue.substr(quoteLPos + 1, quoteRPos - quoteLPos - 1));

			// Ѱ��ð��
			size_t colonPos = mValue.find(':', quoteRPos + 1);
			// �����ո�
			size_t valueBeginPos = mValue.find_first_not_of(' ', colonPos + 1);
			// ����ֵ����
			switch (mValue[valueBeginPos])
			{
			case '{':
				valueEndPos = SkipObj(valueBeginPos); break;
			case '[':
				valueEndPos = SkipArray(valueBeginPos); break;
			case '\"':
				valueEndPos = SkipString(valueBeginPos); break;
			default:	// �����������ͣ����͡����㡢��������ֵ
				size_t pos = mValue.find_first_of(" ,}", valueBeginPos + 1);
				valueEndPos = pos == std::string::npos ? std::string::npos : pos - 1;
				break;
			}
			// ��ȡ����value��������
			std::string_view value = mValue.substr(valueBeginPos, valueEndPos - valueBeginPos + 1);
			objs.emplace(key, JsonValue(value));
		}
		else
		{
			// ��ȡ����ʧ�ܣ���Ϊ�Ѿ���ȡ��ֵ�����
			// �˳���ֵ�ԵĽ���
			break;
		}

	}

	return objs;
	// ����ʱ�������ڹ���ֲ�����objsʱ�Ȼ���ת��return�ټ�����ȥ����
	// ԭ���ֲ�������Ҫ���죬��returnʱ��������������ֵ����Ȼ�������ֲ�����
	// RVO������������ص���һ����������ʱ����Ķ���ֱ�ӰѸ���ʱ�����쵽����ֵ�ϣ�ʡȥһ�ο���/�ƶ�
	// NRVO��ָ�����ֵ���ʱ���󣨱��������objs��������
	// ����������C++11���ϣ���������ֵ���أ������ƶ����壬��Ȼ�������ͬ�������������ƶ���ȥ��
	// ע�⣺���ϼ���ֻ���Ż��������Ǳ�֤�����Խ��ⲿ������Ϊ�������ò�������ʵ����ͬЧ��
}

std::vector<JsonValue> JsonValue::GetArray() const
{
	std::vector<JsonValue> objs;

	size_t beginPos = mValue.find('[');
	if (beginPos == std::string::npos)
		throw std::invalid_argument("Json Value Is Not Array Type");

	size_t valueEndPos = beginPos;
	while (valueEndPos != std::string::npos)
	{
		// ���޳��հ��ַ�
		size_t valueBeginPos = SkipWhiteSpace(valueEndPos + 1);

		// ����ֵ����
		switch (mValue[valueBeginPos])
		{
		case '{':
			valueEndPos = SkipObj(valueBeginPos); break;
		case '[':
			valueEndPos = SkipArray(valueBeginPos); break;
		case '\"':
			valueEndPos = SkipString(valueBeginPos); break;
		default:	// �����������ͣ����͡����㡢��������ֵ
			size_t pos = mValue.find_first_of(" ,}", valueBeginPos + 1);
			valueEndPos = pos == std::string::npos ? std::string::npos : pos - 1;
			break;
		}

		if (valueEndPos != std::string::npos)
		{
			std::string_view obj = mValue.substr(valueBeginPos, valueEndPos - valueBeginPos + 1);
			objs.emplace_back(JsonValue(obj));

			// ������λ���������ţ��Է�Ӱ���´��޳��հ��ַ�
			valueEndPos = mValue.find(',', valueEndPos+1);
		}
		else
		{
			break;
		}
	}

	return objs;
}
