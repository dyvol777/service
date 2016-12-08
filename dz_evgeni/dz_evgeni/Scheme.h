#pragma once

#include <QObject>
#include <QGraphicsPolygonItem>
#include "Pancer.h"

class Scheme : public QGraphicsPolygonItem
{

public:
	Scheme(tree&);
	~Scheme();
};
