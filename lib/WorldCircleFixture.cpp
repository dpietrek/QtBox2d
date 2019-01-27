#include "WorldCircleFixture.h"

#include <QPainter>

#include "Box2D/Box2D.h"

WorldCircleFixture::WorldCircleFixture(float32 radius,
                                       const b2FixtureParams& params,
                                       const b2Filter& filter,
                                       WorldBody& body)
    : WorldFixture(CreateFixtureDef(radius, params, filter), body)
{
    ellipse_ = CreateEllipse();
}

WorldCircleFixture::WorldCircleFixture(float32 radius,
                                       const b2FixtureParams& params,
                                       WorldBody& body)
    : WorldFixture(CreateFixtureDef(radius, params), body)
{
    ellipse_ = CreateEllipse();
}

void WorldCircleFixture::Paint(QPainter* painter) const
{
    float32 radius = b2fixture_->GetShape()->m_radius;

    QPointF center = ellipse_.center();
    QPointF right = {center.x() + radius, 0};
    painter->drawEllipse(ellipse_);
    painter->drawLine(center, right);
}

QRectF WorldCircleFixture::boundingRect() const
{
    return ellipse_.marginsAdded({2, 2, 2, 2});
}

QRectF WorldCircleFixture::CreateEllipse() const
{
    float32 radius = b2fixture_->GetShape()->m_radius;
    return QRectF(0, 0, radius, radius);
}

b2Shape* WorldCircleFixture::CreateShape(float32 radius) const
{
    b2Shape* shape = new b2CircleShape();
    shape->m_radius = radius;
    return shape;
}

b2FixtureDef WorldCircleFixture::CreateFixtureDef(float32 radius,
                                                  const b2FixtureParams& params,
                                                  const b2Filter& filter) const
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = CreateShape(radius);
    fixtureDef.friction = params.friction;
    fixtureDef.restitution = params.restitution;
    fixtureDef.density = params.denstity;
    fixtureDef.filter = filter;

    return fixtureDef;
}
