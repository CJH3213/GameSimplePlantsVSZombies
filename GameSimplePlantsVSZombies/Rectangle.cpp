#include "Rectangle.h"

Rectangle::Rectangle(const Vector2& center, const Vector2& size)
{
    mCenter = center;
    mSize = size;
}

Rectangle::Rectangle()
{
    Rectangle(Vector2(0, 0), Vector2(0, 0));
}

Vector2 Rectangle::GetTopLeftPoint() const
{
    return mCenter - mSize / 2;
}

Vector2 Rectangle::GetTopRightPoint() const
{
    return Vector2(mCenter.x + mSize.x / 2, mCenter.y - mSize.y / 2);
}

Vector2 Rectangle::GetBottomLeftPoint() const
{
    return Vector2(mCenter.x - mSize.x / 2, mCenter.y + mSize.y / 2);
}

Vector2 Rectangle::GetBottomRightPoint() const
{
    return mCenter + mSize / 2;
}

Vector2 Rectangle::GetCenterPoint() const
{
    return mCenter;
}

Vector2 Rectangle::GetLeftCenterPoint() const
{
    return Vector2(mCenter.x-mSize.x/2, mCenter.y);
}

Vector2 Rectangle::GetRightCenterPoint() const
{
    return Vector2(mCenter.x + mSize.x / 2, mCenter.y);
}

Vector2 Rectangle::GetTopCenterPoint() const
{
    return Vector2(mCenter.x, mCenter.y - mCenter.y/2);
}

Vector2 Rectangle::GetBottomCenterPoint() const
{
    return Vector2(mCenter.x, mCenter.y + mCenter.y / 2);
}

bool Rectangle::IsIntersect(const Rectangle& rect) const
{
    Vector2 blp1 = GetBottomLeftPoint();
    Vector2 trp1 = GetTopRightPoint();
    Vector2 blp2 = rect.GetBottomLeftPoint();
    Vector2 trp2 = rect.GetTopRightPoint();

    return Math::Max(blp1.x, blp2.x) <= Math::Min(trp1.x, trp2.x) &&
        Math::Min(blp1.y, blp2.y) >= Math::Max(trp1.y, trp2.y);
}

bool Rectangle::IsInside(Rectangle& rect) const
{
    Vector2 blp1 = GetBottomLeftPoint();
    Vector2 trp1 = GetTopRightPoint();
    Vector2 blp2 = rect.GetBottomLeftPoint();
    Vector2 trp2 = rect.GetTopRightPoint();

    return blp1.x >= blp2.x && blp1.y <= blp2.y &&
        trp1.x <= trp2.x && trp1.y >= trp2.y;
}

bool Rectangle::IsSame(Rectangle& rect) const
{
    return (mCenter==rect.mCenter) && 
        (mSize == rect.mSize);
}

bool Rectangle::IsIntersect(const Vector2& pos) const
{
    Vector2 tlp = GetTopLeftPoint();
    Vector2 brp = GetBottomRightPoint();

    // 要大于等于左上角点且小于不等于右下角点
    return pos.x >= tlp.x && pos.x < brp.x &&
        pos.y >= tlp.y && pos.y < brp.y;
}
