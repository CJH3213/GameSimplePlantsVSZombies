#include "BoxCollider.h"
#include "TransformComponent.h"

ComponentBase* BoxCollider::Clone() const
{
    BoxCollider* newComp = new BoxCollider();
    newComp->mOffset = mOffset;
    newComp->mSize = mSize;

    return newComp;
}

Rectangle BoxCollider::GetBounds()
{   
    return Rectangle(GetTransform()->GetPosition() + mOffset, mSize);
}


