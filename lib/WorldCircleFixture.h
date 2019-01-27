#ifndef WORLDCIRCLEFIXTURE_H
#define WORLDCIRCLEFIXTURE_H

#include "WorldFixture.h"

class WorldCircleFixture : public WorldFixture
{
public:
    WorldCircleFixture(float32 radius,
                       const b2FixtureParams& params,
                       const b2Filter& filter,
                       WorldBody& body);
    WorldCircleFixture(float32 radius,
                       const b2FixtureParams& params,
                       WorldBody& body);

    void Paint(QPainter* painter) const override;
    QRectF boundingRect() const override;

    QRectF CreateEllipse() const;

private:
    b2Shape* CreateShape(float32 radius) const;
    b2FixtureDef CreateFixtureDef(float32 radius,
                                  const b2FixtureParams& params,
                                  const b2Filter& filter = b2Filter()) const;

private:
    QRectF ellipse_;
};

#endif // WORLDCIRCLEFIXTURE_H
