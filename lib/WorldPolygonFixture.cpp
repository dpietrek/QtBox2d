#include "WorldPolygonFixture.h"

#include <QPainter>

#include "Box2D/Box2D.h"

WorldPolygonFixture::WorldPolygonFixture(const std::vector<b2Vec2>& vertices,
                                         const b2FixtureParams& params,
                                         const b2Filter& filter,
                                         WorldBody& body)
    : WorldFixture(CreateFixtureDef(vertices, params, filter), body)
{
    polygon_ = CreatePolygon();
}

WorldPolygonFixture::WorldPolygonFixture(const std::vector<b2Vec2>& vertices,
                                         const b2FixtureParams& params,
                                         WorldBody& body)
    : WorldFixture(CreateFixtureDef(vertices, params), body)
{
    polygon_ = CreatePolygon();
}

void WorldPolygonFixture::Paint(QPainter* painter) const
{
    painter->drawPolygon(polygon_);
}

QRectF WorldPolygonFixture::boundingRect() const
{
    return polygon_.boundingRect().marginsAdded({2, 2, 2, 2});
}

QPolygonF WorldPolygonFixture::CreatePolygon() const
{
    const b2PolygonShape* polygon = dynamic_cast<const b2PolygonShape*>(b2fixture_->GetShape());
    int count = static_cast<int>(polygon->m_count);

    QVector<QPointF> points;
    for(int i = 0; i < count; i++) {
        b2Vec2 p = polygon->m_vertices[i];
        QPointF point(p.x, p.y);
        points.push_back(point);
    }

    return QPolygonF(points);
}

b2Shape* WorldPolygonFixture::CreateShape(const std::vector<b2Vec2>& vertices) const
{
    b2PolygonShape* shape = new b2PolygonShape();
    shape->Set(vertices.data(), static_cast<int>(vertices.size()));
    return shape;
}

b2FixtureDef WorldPolygonFixture::CreateFixtureDef(const std::vector<b2Vec2>& vertices,
                                                   const b2FixtureParams& params,
                                                   const b2Filter& filter) const
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = CreateShape(vertices);
    fixtureDef.friction = params.friction;
    fixtureDef.restitution = params.restitution;
    fixtureDef.density = params.denstity;
    fixtureDef.filter = filter;

    return fixtureDef;
}
