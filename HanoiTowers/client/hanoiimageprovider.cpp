/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiclient.h"
#include "hanoiimageprovider.h"
#include "localuser.h"

#include <QThread>
#include <QThreadPool>

HanoiImageProvider::HanoiImageProvider(const QHash<QString, QSharedPointer<LocalUser> > *cache) {
    _pool = new QThreadPool();
    _cache = cache;
}

void HanoiImageProvider::stop() {
    _cache = nullptr;
}

HanoiImageProvider::~HanoiImageProvider() {
    _pool->deleteLater();
}

QQuickImageResponse *HanoiImageProvider::requestImageResponse(const QString &id,
                                                              const QSize &requestedSize) {

    AsyncImageResponse *response = new AsyncImageResponse(id, requestedSize, _cache);
    _pool->start(response);
    return response;

}

AsyncImageResponse::AsyncImageResponse(const QString &id, const QSize &requestedSize,
                                       const QHash<QString, QSharedPointer<LocalUser> > *cache)
    : m_id(id), m_requestedSize(requestedSize), m_texture(0), _cache(cache) {
    setAutoDelete(false);
}

QQuickTextureFactory *AsyncImageResponse::textureFactory() const {
    return m_texture;
}

void AsyncImageResponse::run() {
    if (!_cache) {
        emit finished();
        return;
    }

    auto ids = m_id.split(":");
    QByteArray imageData;

    if (ids.size() && _cache->contains(ids[0])) {
        imageData = _cache->value(ids[0])->avatarData();

    }

    QImage image;
    if (imageData.size()) {
        image = QImage::fromData(imageData);
    } else {
        image = QImage(":/img/DefaultAvatar");
    }

    if (m_requestedSize.isValid())
        image = image.scaled(m_requestedSize);

    m_texture = QQuickTextureFactory::textureFactoryForImage(image);
    emit finished();
}
