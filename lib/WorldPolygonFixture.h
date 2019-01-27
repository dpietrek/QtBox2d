#ifndef WORLDPOLYGONFIXTURE_H
#define WORLDPOLYGONFIXTURE_H

#include <vector>

#include <QPolygonF>

#include "WorldFixture.h"

class WorldPolygonFixture : public WorldFixture
{
public:
    WorldPolygonFixture(const std::vector<b2Vec2>& vertices,
                        const b2FixtureParams& params,
                        const b2Filter& filter,
                        WorldBody& body);
    WorldPolygonFixture(const std::vector<b2Vec2>& vertices,
                        const b2FixtureParams& params,
                        WorldBody& body);

    void Paint(QPainter* painter) const override;
    QRectF boundingRect() const override;

    QPolygonF CreatePolygon() const;

private:
    b2Shape* CreateShape(const std::vector<b2Vec2>& vertices) const;
    b2FixtureDef CreateFixtureDef(const std::vector<b2Vec2>& vertices,
                                  const b2FixtureParams& params,
                                  const b2Filter& filter = b2Filter()) const;

private:
    QPolygonF polygon_;
};

#endif // WORLDPOLYGONFIXTURE_H
