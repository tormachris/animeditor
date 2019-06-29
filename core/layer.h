#ifndef LAYER_H
#define LAYER_H

#include <QHash>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include <QString>
#include "core_global.h"
#include "keyframe.h"

namespace SchMatrix {

class CORESHARED_EXPORT Layer : public QSequentialAnimationGroup {
  Q_OBJECT

 public:
  explicit Layer(QObject *parent = nullptr, QString name = "layer",
                 int zOrder = 0);
  QList<QAbstractAnimation *> animations() const;
  QList<QPauseAnimation *> pauses() const;
  QList<Keyframe *> keyframes() const;
  Keyframe *currentKeyframe() const;
  Keyframe *nextKeyframe() const;
  Keyframe *prevKeyframe() const;

  QString getName() const;
  int getZOrder() const;
  void setName(const QString &name);
  void setZOrder(const int &zOrder);

  // pause garbage collection
  void deleteEmptyPauses();

  QAbstractAnimation *animationAtMsec(int msec) const;

 private:
  QString name;
  int zOrder;
};

}  // namespace SchMatrix

#endif  // LAYER_H
