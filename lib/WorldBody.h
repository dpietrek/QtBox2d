#ifndef WORLDBODY_H
#define WORLDBODY_H

#include <memory>

#include <QGraphicsItem>

#include <Box2D/Box2D.h>

#include "ListRef.h"
#include "WorldFixture.h"

class WorldScene;
class WorldCircleFixture;
class WorldPolygonFixture;

class WorldBody : public QGraphicsItem
{
    friend class WorldFixture;
public:
    explicit WorldBody(const b2BodyDef& bodyDef, WorldScene& scene, QGraphicsItem  *parent = nullptr);
    explicit WorldBody(const b2Vec2& position, WorldScene& scene, QGraphicsItem  *parent = nullptr);
    ~WorldBody() override;

    void AddFixture(WorldFixture& fixture);
    void RemoveFixture(WorldFixture& fixture);

    void Update();

    WorldCircleFixture CreateCircleFixture(float32 radius,
                                     const b2FixtureParams& params,
                                     const b2Filter& filter = b2Filter());
    WorldPolygonFixture CreatePolygonFixture(const std::vector<b2Vec2>& vertices,
                                      const b2FixtureParams& params,
                                      const b2Filter& filter = b2Filter());

    std::unique_ptr<WorldFixture> CreateCircleUPtrFixture(float32 radius,
                                                          const b2FixtureParams& params,
                                                          const b2Filter& filter = b2Filter());
    std::unique_ptr<WorldFixture> CreatePolygonUPtrFixture(const std::vector<b2Vec2>& vertices,
                                                           const b2FixtureParams& params,
                                                           const b2Filter& filter = b2Filter());


    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

    QRectF boundingRect() const override;

private:
    b2Fixture* CreateB2Fixture(const b2FixtureDef& fixtureDef);
    void DestroyB2Fixture(b2Fixture* fixture);
    void Create(const b2BodyDef& bodyDef);
    void Delete();

private:
    b2Body* b2body_;
    WorldScene& scene_;
    ListRef<WorldFixture> fixtures_;
};

#endif // WORLDBODY_H
