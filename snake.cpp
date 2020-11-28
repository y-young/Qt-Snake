/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "snake.h"

#include <QPainter>
#include <QTimer>
#include <QtDebug>

Snake::Snake(QWidget *parent, Heading h, QString c)
    : QWidget(parent)
{
    for(int i = -direction[h][0]*SIZE; i != 0; i+=direction[h][0]) {
        body.push_back(QPoint(i,0));
    }
    heading = h;
    color = QColor(c);
}
void Snake::draw(QPainter *painter)
{
    painter->setBrush(color);
    for(int i = body.size() - 1; i >= 0; --i) {
        QPoint p = body[i];
        painter->drawRect(p.rx(), p.ry(), SIZE, SIZE);
    }
}
void Snake::setHeading(Heading newHeading) {
    if(direction[heading][0] + direction[newHeading][0] == 0  || direction[heading][1] + direction[newHeading][1] == 0) {
        return;
    }
    heading = newHeading;
}
void Snake::keyEvent1(int key) {
    switch(key) {
    case Qt::Key_Up:
        setHeading(UP);
        break;
    case Qt::Key_Down:
        setHeading(DOWN);
        break;
    case Qt::Key_Left:
        setHeading(LEFT);
        break;
    case Qt::Key_Right:
        setHeading(RIGHT);
        break;
    }
}
void Snake::keyEvent2(int key) {
    switch(key) {
    case Qt::Key_W:
        setHeading(UP);
        break;
    case Qt::Key_S:
        setHeading(DOWN);
        break;
    case Qt::Key_A:
        setHeading(LEFT);
        break;
    case Qt::Key_D:
        setHeading(RIGHT);
        break;
    }
}
void Snake::grow() {
    QPoint tail = body.front();
    int dx, dy;
    if(body.size() > 1) {
        QPoint beforeTail = body.at(1);
        dx = tail.rx() - beforeTail.rx();
        dy = tail.ry() - beforeTail.ry();

    } else {
        dx = direction[heading][0];
        dy = direction[heading][1];
    }
    tail.setX(tail.rx() + dx);
    tail.setY(tail.ry() + dy);
    body.push_front(tail);
}

void Snake::move() {
    QPoint head = body.back();
    body.pop_front();
    head.setX(head.rx() + direction[heading][0]);
    head.setY(head.ry() + direction[heading][1]);
    body.push_back(head);
}
QPoint Snake::head() {
    return body.back();
}
