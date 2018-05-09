#include "DecoratorNodeModel.hpp"

DecoratorNodeModel::DecoratorNodeModel(QString decorator_ID,
                                       const ParameterWidgetCreators &parameters):
    BehaviorTreeNodeModel("Decorator", decorator_ID, parameters )
{
    auto style = this->nodeStyle();
    style.NormalBoundaryColor = QColor(255,210,0);
    this->setNodeStyle(style);
}