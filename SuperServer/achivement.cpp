#include "achivement.h"

QMap<actionAchivement, QVector<int>>* Achivement::mapAchivement = new QMap<actionAchivement, QVector<int>>(
        {
            {actionAchivement::waterTheFlower, {1}},
            {actionAchivement::addPlant, {10}}
        });

Achivement::Achivement()
{

}
