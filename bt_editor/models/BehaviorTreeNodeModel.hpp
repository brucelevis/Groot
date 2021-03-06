#pragma once

#include <QObject>
#include <QLabel>
#include <QFile>
#include <QLineEdit>
#include <QFormLayout>
#include <QEvent>
#include <nodes/NodeDataModel>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <QSvgRenderer>
#include "bt_editor/bt_editor_base.h"
#include "bt_editor/utils.h"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;

class BehaviorTreeDataModel : public NodeDataModel
{
    Q_OBJECT

public:
  BehaviorTreeDataModel(const TreeNodeModel &parameters );

  ~BehaviorTreeDataModel() override;

public:

  virtual NodeType nodeType() const = 0;

  virtual std::pair<QString,QColor> caption() const;

  virtual QString captionIicon() const { return QString(); }

  virtual void setInstanceName(const QString& name);

public:

  void initWidget();

  NodeDataType dataType(PortType , PortIndex ) const final;

  std::shared_ptr<NodeData> outData(PortIndex port) final;

  void setInData(std::shared_ptr<NodeData>, int) final {}

  const QString& registrationName() const;

  QString name() const final { return registrationName(); }

  const QString& instanceName() const;

  std::vector<TreeNodeModel::Param> getCurrentParameters() const;

  QWidget *embeddedWidget() final { return _main_widget; }

  QWidget *parametersWidget() { return _params_widget; }

  QJsonObject save() const override;

  void restore(QJsonObject const &) override;

  void lock(bool locked);

  void setParameterValue(const QString& label, const QString& value);

  int UID() const { return _uid; }

  bool eventFilter(QObject *obj, QEvent *event) override;


public slots:

  void updateNodeSize();


protected:
  QFrame*  _main_widget;
  QFrame*  _params_widget;

  QLineEdit* _line_edit_name;

  std::map<QString, QWidget*> _params_map;
  int16_t _uid;

  QFormLayout* _form_layout;
  QVBoxLayout* _main_layout;
  QLabel* _caption_label;
  QFrame* _caption_logo_left;
  QFrame* _caption_logo_right;


private:
  const QString _registration_name;
  QString _instance_name;
  QSvgRenderer* _icon_renderer;


signals:

  void parameterUpdated(QString, QWidget*);

  void instanceNameChanged();

};
