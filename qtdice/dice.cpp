#include <cstdlib>
#include <time.h>
#include "dice.h"

dice::dice(QObject *parent) : QObject(parent) {
    m_dice_regex_pattern = "[0-9]*d([2468]|10|12|20|100)((\\+[0-9]+)|(\\-[0-9]+))?(r[0-9]+)?";
    m_dice_repeat_pattern = "r[0-9]+";
    m_dice_add_pattern = "\\+[0-9]+";
    m_dice_subtract_pattern = "\\-[0-9]+";

    m_dice_regex.setPattern(m_dice_regex_pattern);
    m_dice_repeat_regex.setPattern(m_dice_repeat_pattern);
    m_dice_add_regex.setPattern(m_dice_add_pattern);
    m_dice_subtract_regex.setPattern(m_dice_subtract_pattern);
}

QString dice::interpret_text(QString text) {
    QString retval = "";

    if(m_dice_regex.match(text).hasMatch()) {
        int repeat = 1, mod = 0;

        if(m_dice_repeat_regex.match(text).hasMatch()) {
            int rpos = text.indexOf("r");

            if(rpos != -1) {
                repeat = text.mid(rpos+1,1).toInt();
                text = text.mid(0,rpos);
            }
        }

        int mod_pos = -1;
        bool neg = false;
        if(m_dice_add_regex.match(text).hasMatch()) {
            mod_pos = text.indexOf("+");
        } else if(m_dice_subtract_regex.match(text).hasMatch()) {
            mod_pos = text.indexOf("-");
            neg = true;
        }

        if(mod_pos != -1) {
            mod = text.mid(mod_pos+1,text.length()-(mod_pos+1)).toInt();
            if(neg) {
                mod = -mod;
            }
            text = text.mid(0,mod_pos);
        }

        retval = QString::number(eval_dice(text)+mod);
        for(int c = 1; c < repeat; c++) {
            retval += "\n"+QString::number(eval_dice(text)+mod);
        }
    } else {
        retval = "?";
    }
    return retval;
}

int dice::eval_dice(QString text) {
    int dpos = text.indexOf("d");
    int a = 1;
    int b = text.mid(dpos+1,text.length()-1).toInt();

    if(text.mid(0,dpos) != "") {
        a = text.mid(0,dpos).toInt();
    }

    int sum = 0;
    for(int c = 0; c < a; c++) {
        sum += rand() % b + 1;
    }

    return sum;
}
