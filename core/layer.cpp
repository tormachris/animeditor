#include "layer.h"

#include <QList>

namespace SchMatrix {

Layer::Layer(QObject *parent) : QSequentialAnimationGroup(parent) {}

QList<Keyframe *> Layer::keyframes() {
  QList<Keyframe *> keyframes;

  for (int i = 0; i < animationCount(); ++i) {
    auto anim = animationAt(i);
    if (qobject_cast<Keyframe *>(anim))
      keyframes.append(static_cast<Keyframe *>(anim));
  }

  return keyframes;
}

Keyframe *Layer::currentKeyframe() {
  auto anim = currentAnimation();

  if (qobject_cast<Keyframe *>(anim))
    return static_cast<Keyframe *>(anim);
  else
    return static_cast<Keyframe *>(animationAt(indexOfAnimation(anim) - 1));
}

Keyframe *Layer::nextKeyframe() {
  if (animationCount() < 2) return nullptr;

  auto keys = keyframes();
  auto idx = keys.indexOf(currentKeyframe());

  if (idx == keys.size() - 1) return nullptr;

  return keys[idx + 1];
}

Keyframe *Layer::prevKeyframe() {
  if (animationCount() < 2) return nullptr;

  auto keys = keyframes();
  auto idx = keys.indexOf(currentKeyframe());

  if (idx == 0) return nullptr;

  return keys[idx - 1];
}

}  // namespace SchMatrix
