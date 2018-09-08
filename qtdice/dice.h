#ifndef DICE_H
#define DICE_H

#include <QString>
#include <QRegularExpression>

class dice : public QObject {
    Q_OBJECT

public:
    dice(QObject *parent = nullptr);
    Q_INVOKABLE QString interpret_text(QString text);

private:
    int eval_dice(QString text);

    //members
    QString m_dice_regex_pattern;
    QString m_dice_repeat_pattern;
    QString m_dice_add_pattern;
    QString m_dice_subtract_pattern;
    QRegularExpression m_dice_regex;
    QRegularExpression m_dice_repeat_regex;
    QRegularExpression m_dice_add_regex;
    QRegularExpression m_dice_subtract_regex;
};
#endif // DICE_H
