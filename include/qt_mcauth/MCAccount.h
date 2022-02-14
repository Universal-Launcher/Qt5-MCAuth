#pragma once

#include <QPixmap>
#include <QString>
#include <QUrl>
#include <QVector>
#include <optional>

struct MCInfo {
  QString id;
  QString state;
  QUrl url;
};

struct MinecraftSkin : public MCInfo {
  QString variant;
  QString alias;
};

struct MinecraftCapes : public MCInfo {
  QString alias;
};

struct MCAccount {
  QString id;
  QString username;
  QString accessToken;
  QVector<MinecraftSkin> skins;
  QVector<MinecraftCapes> capes;
  std::optional<QPixmap> currentSkin;
};
