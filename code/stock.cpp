#include "stock.h"

Stock::~Stock()
{
}

bool Stock::operator>(const Stock& st) const
{
    if (sym() > st.sym())
        return true;
    else if (sym() < st.sym())
        return false;
    else
        return (dt() > st.dt());

}

bool Stock::operator>=(const Stock& st) const
{
    if (sym() > st.sym())
        return true;
    else if (sym() < st.sym())
        return false;
    else
        return (dt() >= st.dt());
}

bool Stock::operator==(const Stock& st) const
{
    return (sym() == st.sym() && dt() == st.dt());
}

bool Stock::operator<=(const Stock& st) const
{
    if (sym() < st.sym())
        return true;
    else if (sym() > st.sym())
        return false;
    else
        return (dt() < st.dt());
}

bool Stock::operator<(const Stock& st) const
{
    if (sym() < st.sym())
        return true;
    else if (sym() > st.sym())
        return false;
    else
        return (dt() <= st.dt());
}
