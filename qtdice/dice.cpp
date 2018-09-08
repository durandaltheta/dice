#include <cstdlib>
#include <time.h>
#include <vector>
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


        int sum = 0;
        std::vector<int> totalSumList;
        int totalSum = 0;

        //retval = QString::number(sum+mod);


        for(int c = 0; c < repeat; c++) {

            std::vector<int> diceRolls = eval_dice(text);

            for(unsigned int i = 0; i < diceRolls.size(); i++)
            {
                sum += diceRolls[i];
            }

            retval += "\n"+QString::number(sum);

            retval += "=";
            for (unsigned int d = 0; d < diceRolls.size(); d++)
            {
                if(d!=0)retval += "+";
                retval += QString::number(diceRolls[d]);
            }
            if(mod > 0) {
                sum += mod;
                retval += "+" + QString::number(mod);
            } else if(mod < 0) {
                sum -= mod;
                retval += QString::number(mod);
            }

            if(repeat > 1)
            {
                totalSum += sum;
                totalSumList.push_back(sum);
            }
        }

        if (repeat > 1)
        {
            retval+= "\n--\n"+QString::number(totalSum)+"=";

            for (int e = 0; e < totalSumList.size(); e++)
            {
                if(e!=0)retval += "+";
                retval += QString::number(totalSumList[e]+mod);
            }
        }

    } else {
        retval = "?";
    }
    return retval;
}

std::vector<int> dice::eval_dice(QString text) {
    int dpos = text.indexOf("d");
    int a = 1;
    int b = text.mid(dpos+1,text.length()-1).toInt();

    if(text.mid(0,dpos) != "") {
        a = text.mid(0,dpos).toInt();
    }

    //int sum = 0;
    std::vector<int> diceRolls;

    for(int c = 0; c < a; c++) {
        diceRolls.push_back((rand() % b + 1));
        //sum += rand() % b + 1;
    }

    return diceRolls;
}
