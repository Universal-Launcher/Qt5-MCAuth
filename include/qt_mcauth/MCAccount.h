#pragma once

#include <QString>
#include <QUrl>
#include <QVector>

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
};
