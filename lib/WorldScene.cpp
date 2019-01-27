#include "WorldScene.h"

#include <cmath>

#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "WorldBody.h"

WorldScene::WorldScene(QObject *parent) : QGraphicsScene(parent), b2world_({1, 1})
{
    setSceneRect(-10, -10, 10000, 10000);
}

void WorldScene::Step()
{
    b2world_.Step(1, 8, 3);
    for (WorldBody& body: bodies_) {
        body.Update();
    }
}

WorldBody WorldScene::CreateBody(const b2BodyDef& bodyDef)
{
    return WorldBody(bodyDef, *this);
}

WorldBody WorldScene::CreateBody(const b2Vec2& position)
{
    return WorldBody(position, *this);
}

std::unique_ptr<WorldBody> WorldScene::CreateUPtrBody(const b2BodyDef& bodyDef)
{
    return std::make_unique<WorldBody>(bodyDef, *this);
}

std::unique_ptr<WorldBody> WorldScene::CreateUPtrBody(const b2Vec2& position)
{
    return std::make_unique<WorldBody>(position, *this);
}

void WorldScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    int step = 10;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));
    // draw horizontal grid
    qreal start = 0;
    if (start > rect.top()) {
       start -= step;
    }
    for (qreal y = start - step; y < rect.bottom(); ) {
       y += step;
       painter->drawLine(rect.left(), y, rect.right(), y);
    }
    // now draw vertical grid
    start = 0;
    if (start > rect.left()) {
       start -= step;
    }
    for (qreal x = start - step; x < rect.right(); ) {
       x += step;
       painter->drawLine(x, rect.top(), x, rect.bottom());
    }

    QString textMouse = "(%1, %2)";
    QString xpos = QString::number(mousePosition_.x());
    QString ypos = QString::number(mousePosition_.y());
    // now draw mouse position
    painter->drawText(mousePosition_, textMouse.arg(xpos).arg(ypos));
}

void WorldScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    mousePosition_ = event->scenePos();
}

b2Body*WorldScene::CreateB2Body(const b2BodyDef& bodyDef)
{
    return b2world_.CreateBody(&bodyDef);
}

void WorldScene::DestroyB2Body(b2Body* body)
{
    b2world_.DestroyBody(body);
}

void WorldScene::AddBody(WorldBody& body)
{
    addItem(&body);
    bodies_.Add(body);
}

void WorldScene::RemoveBody(WorldBody& body)
{
    bodies_.Remove(body);
}
