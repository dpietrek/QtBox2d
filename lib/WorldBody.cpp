#include "WorldBody.h"

#include <QPainter>
#include <QtMath>

#include "WorldFixture.h"
#include "WorldCircleFixture.h"
#include "WorldPolygonFixture.h"
#include "WorldScene.h"

WorldBody::WorldBody(const b2BodyDef& bodyDef, WorldScene& scene, QGraphicsItem *parent)
    : QGraphicsItem(parent), b2body_(nullptr), scene_(scene)
{
    Create(bodyDef);
}

WorldBody::WorldBody(const b2Vec2& position, WorldScene& scene, QGraphicsItem* parent)
    : QGraphicsItem(parent), b2body_(nullptr), scene_(scene)
{
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    Create(bodyDef);
}

WorldBody::~WorldBody()
{
    Delete();
}

void WorldBody::AddFixture(WorldFixture& fixture)
{
    fixtures_.Add(fixture);
}

void WorldBody::RemoveFixture(WorldFixture& fixture)
{
    fixtures_.Remove(fixture);
}

void WorldBody::Update()
{
    setPos(b2body_->GetPosition().x, b2body_->GetPosition().y);
    setRotation(qDegreesToRadians(b2body_->GetAngle()));
}

WorldCircleFixture WorldBody::CreateCircleFixture(float32 radius,
                                                  const b2FixtureParams& params,
                                                  const b2Filter& filter)
{
    return WorldCircleFixture(radius, params, filter, *this);
}

WorldPolygonFixture WorldBody::CreatePolygonFixture(const std::vector<b2Vec2>& vertices,
                                                    const b2FixtureParams& params,
                                                    const b2Filter& filter)
{
    return WorldPolygonFixture(vertices, params, filter, *this);
}

std::unique_ptr<WorldFixture> WorldBody::CreateCircleUPtrFixture(float32 radius,
                                                                 const b2FixtureParams& params,
                                                                 const b2Filter& filter)
{
    return std::make_unique<WorldCircleFixture>(radius, params, filter, *this);
}

std::unique_ptr<WorldFixture> WorldBody::CreatePolygonUPtrFixture(const std::vector<b2Vec2>& vertices,
                                                                  const b2FixtureParams& params,
                                                                  const b2Filter& filter)
{
    return std::make_unique<WorldPolygonFixture>(vertices, params, filter, *this);
}

void WorldBody::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    for(const WorldFixture& fixture: fixtures_) {
        painter->save();
        painter->setBrush(QBrush(QColor(Qt::yellow)));
        painter->drawRect(fixture.boundingRect());
        painter->restore();
        painter->save();
        fixture.Paint(painter);
        painter->restore();
    }
}

QRectF WorldBody::boundingRect() const
{
    if (fixtures_.size() == 0)
        return {0, 0, 0, 0};
    WorldFixture& f = *fixtures_.begin();
    QRectF rect = f.boundingRect();
    for(const WorldFixture& fixture: fixtures_) {
        rect = rect.united(fixture.boundingRect());
    }
    return rect;
}

b2Fixture* WorldBody::CreateB2Fixture(const b2FixtureDef& fixtureDef)
{
    return b2body_->CreateFixture(&fixtureDef);
}

void WorldBody::DestroyB2Fixture(b2Fixture* fixture)
{
    b2body_->DestroyFixture(fixture);
}

void WorldBody::Create(const b2BodyDef& bodyDef)
{
    if (b2body_)
        return;
    b2body_ = scene_.CreateB2Body(bodyDef);
    scene_.AddBody(*this);
}

void WorldBody::Delete()
{
    if (b2body_)
        scene_.DestroyB2Body(b2body_);
    scene_.RemoveBody(*this);
}
