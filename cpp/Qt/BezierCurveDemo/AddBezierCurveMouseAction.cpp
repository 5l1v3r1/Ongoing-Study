#include "AddBezierCurveMouseAction.h"

#include "../../DesignPatterns/Singleton.h"
#include "BezierCurve.h"


bool AddBezierCurveMouseAction::mouseDoubleClickEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);

    Q_ASSERT(event != nullptr);
    if (event->button() != Qt::LeftButton)
        return false;

    auto bezierCurve = Singleton<DecoratedBezierCurve>::GetInstancePtr();

    if (bezierCurve->hitTest(event->pos()))
    {
        bezierCurve->removePoint(event->pos());
        return true;
    }
    else
    {
        return bezierCurve->addPoint(event->pos());
    }
}
