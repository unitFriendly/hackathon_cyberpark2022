#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <QObject>

enum TypeGroundEnum
{
    type_ground_open,                   // на открытом воздухе
    type_ground_close                   // парник или в помещении
};

enum TypeActionEnum
{
    type_action_watering,               // поливка
    type_action_losening,               // рыхление
    type_action_weeding,                // прополка
    type_action_top_dressing,           // подкормка
    type_action_formation_crown,        // формирование, образка крон
    type_action_pest_control,           // защита от вредителей
    type_action_planting_restoration,   // лечение и восстановление посадок
    type_action_preparation_for_winter  // подготовка к зиме
};

enum PhasesGrowthPlantEnum
{
    phase_growth_seeds_at_rest,         // семена в покое
    phase_growth_seed_swelling,         // набухание семян
    phase_growth_seed_germination,      // проростание семян
    phase_growth_seedlings,             // всходы
    phase_growth_leaf_and_root_growth,  // рост листьев и корней
    phase_growth_stem_and_shoot_growth, // рост стебля и боковых побегов
    phase_growth_budding,               // бутонизация
    phase_growth_bloom,                 // цветение
    phase_growth_fruit_growth,          // рост плодов
    phase_growth_fruit_ripening,        // созревание плодов
    phase_growth_plant_death,           // гибель растения
    phase_growth_recovery_after_harvest // восстановление после сбора плодов
};

class CommonData : public QObject
{
    Q_OBJECT
public:
    explicit CommonData(QObject *parent = nullptr);

signals:

};

#endif // COMMONDATA_H
