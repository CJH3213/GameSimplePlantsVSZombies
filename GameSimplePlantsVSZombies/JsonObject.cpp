#include "JsonObject.h"
#include <stdexcept>
#include <algorithm>

size_t JsonValue::SkipObj(size_t off) const
{
	int count = 0;		// 记录左花括号个数

	for (size_t i = off; i < mValue.size(); ++i)
	{
		if (mValue[i] == '{')
			++count;
		else if (mValue[i] == '}')
		{
			--count;
			if (count == 0)
				return i;  // 返回右花括号的位置
		}
	}

	return std::string::npos;  // 如果没有找到匹配的右花括号，返回npos
}

size_t JsonValue::SkipArray(size_t off) const
{
	int count = 0;		// 记录左花括号个数

	for (size_t i = off; i < mValue.size(); ++i)
	{
		if (mValue[i] == '[')
			++count;
		else if (mValue[i] == ']')
		{
			--count;
			if (count == 0)
				return i;  // 返回右花括号的位置
		}
	}

	return std::string::npos;  // 如果没有找到匹配的右方括号，返回npos
}

size_t JsonValue::SkipString(size_t off) const
{
	size_t count = 0;

	for (size_t i = off; i < mValue.size(); ++i)
	{
		if (mValue[i] == '\"')
		{
			// 转义的引号不算
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
	// 跳过空白字符：空格、回车、换行、水平制表、垂直制表、换页
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
	// 将字符串转换为小写
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
	if (mValue[0] == '\"')	// 去除双引号
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
		// 每一轮循环处理一个Json对象键值对

		// 寻找引号
		size_t quoteLPos = mValue.find('\"', valueEndPos + 1);
		size_t quoteRPos = SkipString(quoteLPos);
		// 将引号内容提取为key
		if (quoteRPos != std::string::npos)
		{
			std::string key(mValue.substr(quoteLPos + 1, quoteRPos - quoteLPos - 1));

			// 寻找冒号
			size_t colonPos = mValue.find(':', quoteRPos + 1);
			// 跳过空格
			size_t valueBeginPos = mValue.find_first_not_of(' ', colonPos + 1);
			// 跳过值内容
			switch (mValue[valueBeginPos])
			{
			case '{':
				valueEndPos = SkipObj(valueBeginPos); break;
			case '[':
				valueEndPos = SkipArray(valueBeginPos); break;
			case '\"':
				valueEndPos = SkipString(valueBeginPos); break;
			default:	// 跳过其他类型：整型、浮点、布尔、空值
				size_t pos = mValue.find_first_of(" ,}", valueBeginPos + 1);
				valueEndPos = pos == std::string::npos ? std::string::npos : pos - 1;
				break;
			}
			// 提取对象value部分内容
			std::string_view value = mValue.substr(valueBeginPos, valueEndPos - valueBeginPos + 1);
			objs.emplace(key, JsonValue(value));
		}
		else
		{
			// 提取引号失败，认为已经读取键值对完毕
			// 退出键值对的解析
			break;
		}

	}

	return objs;
	// 调试时发现了在构造局部对象objs时先会跳转到return再继续回去运行
	// 原本局部对象先要构造，在return时拷贝到函数返回值对象，然后析构局部对象
	// RVO技术：如果返回的是一个函数内临时构造的对象，直接把该临时对象构造到返回值上，省去一次拷贝/移动
	// NRVO：指有名字的临时对象（比如这里的objs）被返回
	// 复制消除：C++11以上，若函数按值返回，则尝试移动语义，虽然内外对象不同，但是内容是移动过去的
	// 注意：以上技术只是优化，并不是保证，可以将外部对象作为函数引用参数传入实现相同效果
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
		// 先剔除空白字符
		size_t valueBeginPos = SkipWhiteSpace(valueEndPos + 1);

		// 跳过值内容
		switch (mValue[valueBeginPos])
		{
		case '{':
			valueEndPos = SkipObj(valueBeginPos); break;
		case '[':
			valueEndPos = SkipArray(valueBeginPos); break;
		case '\"':
			valueEndPos = SkipString(valueBeginPos); break;
		default:	// 跳过其他类型：整型、浮点、布尔、空值
			size_t pos = mValue.find_first_of(" ,}", valueBeginPos + 1);
			valueEndPos = pos == std::string::npos ? std::string::npos : pos - 1;
			break;
		}

		if (valueEndPos != std::string::npos)
		{
			std::string_view obj = mValue.substr(valueBeginPos, valueEndPos - valueBeginPos + 1);
			objs.emplace_back(JsonValue(obj));

			// 将结束位置移至逗号，以防影响下次剔除空白字符
			valueEndPos = mValue.find(',', valueEndPos+1);
		}
		else
		{
			break;
		}
	}

	return objs;
}
