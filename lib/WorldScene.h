#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <list>
#include <memory>
#include <functional>

#include <QGraphicsScene>

#include <Box2D/Box2D.h>

#include "ListRef.h"

class WorldBody;

class WorldScene : public QGraphicsScene
{
    Q_OBJECT
    friend class WorldBody;
public:
    explicit WorldScene(QObject *parent = nullptr);

    void Step();

    WorldBody CreateBody(const b2BodyDef& bodyDef);
    WorldBody CreateBody(const b2Vec2& position);
    std::unique_ptr<WorldBody> CreateUPtrBody(const b2BodyDef& bodyDef);
    std::unique_ptr<WorldBody> CreateUPtrBody(const b2Vec2& position);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    b2Body* CreateB2Body(const b2BodyDef& bodyDef);
    void DestroyB2Body(b2Body* body);
    void AddBody(WorldBody& body);
    void RemoveBody(WorldBody& body);

private:
    b2World b2world_;
    ListRef<WorldBody> bodies_;
    QPointF mousePosition_;
};

#endif // WORLDSCENE_H
