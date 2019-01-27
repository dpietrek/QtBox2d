#ifndef WORLDFIXTURE_H
#define WORLDFIXTURE_H

#include <QRect>

#include <Box2D/Box2D.h>

class QPainter;
class WorldBody;

struct b2FixtureParams
{
    float32 friction;
    float32 restitution;
    float32 denstity;
};

class WorldFixture
{
public:
    explicit WorldFixture(const b2FixtureDef& fitureDef, WorldBody& body);
    virtual ~WorldFixture();

    virtual void Paint(QPainter* painter) const = 0;
    virtual QRectF boundingRect() const = 0;

private:
    void Create(const b2FixtureDef& fixtureDef);
    void Delete();

protected:
    b2Fixture* b2fixture_;

private:
    WorldBody& body_;
};

#endif // WORLDFIXTURE_H
