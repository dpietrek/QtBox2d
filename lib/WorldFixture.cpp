#include "WorldFixture.h"

#include "WorldBody.h"

WorldFixture::WorldFixture(const b2FixtureDef& fixtureDef, WorldBody& body)
    : b2fixture_(nullptr), body_(body)
{
    Create(fixtureDef);
    delete fixtureDef.shape;
}

WorldFixture::~WorldFixture()
{
    Delete();
}

QRectF WorldFixture::boundingRect() const
{
    b2AABB aabb = b2fixture_->GetAABB(0);

    QRectF rect = QRectF(QPointF(aabb.lowerBound.x, aabb.lowerBound.y),
                         QPointF(aabb.upperBound.x, aabb.upperBound.y));

    rect = rect.marginsAdded(QMarginsF(5,5,5,5));
    return rect;
}

void WorldFixture::Create(const b2FixtureDef& fixtureDef)
{
    if (b2fixture_)
        return;
    b2fixture_ = body_.CreateB2Fixture(fixtureDef);
    body_.AddFixture(*this);
}

void WorldFixture::Delete()
{
    if (b2fixture_)
        body_.DestroyB2Fixture(b2fixture_);
    body_.RemoveFixture(*this);
}
