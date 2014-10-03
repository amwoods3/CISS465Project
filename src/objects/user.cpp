#include "user.h"

extern const char file_name[];

std::vector<std::vector<std::string> > User::all_info;

User::User(const std::string & user, const std::string & pass)
    : user_name(user), password(pass), total_kills(0),
      total_deaths(0), num_bombs_dropped(0), row(-1)
{
    
    try {
        if (all_info.empty())
        {
            all_info = get_pieces_of_file(file_name);
        }
        find();
        if (row == -1)
        {   
            all_info.push_back(vstr());
            //put_data_to_file(all_info, file_name);
        }
    }
    catch (NOFILE e)
    {
        all_info.push_back(vstr());
    }
    
}


std::vector<std::string> User::vstr() const
{
    std::vector<std::string> ret;
    ret.push_back(user());
    ret.push_back(pass());
    ret.push_back(to_string(kills()));
    ret.push_back(to_string(deaths()));
    ret.push_back(to_string(bombs_dropped()));
    
    return ret;
}

int User::find()
{
    for (int i = 0; i < all_info.size(); ++i)
    {
        if (user() == all_info[i][0])
        {
            row = i;
            return row;
        }
    }
    row = -1;
    return row;
}

double User::KDR() const
{
    if (deaths() != 0)
        return (double) kills() / deaths();
    else
        return -1; //to represent infinity (there is no infinity)
}

void User::update_file()
{
    put_data_to_file(all_info, file_name);
}


std::string to_string(const User & u)
{
    std::vector<std::string> set = u.vstr();
    std::string ret;
    for (int i = 0; i < set.size() - 1; ++i)
    {
        ret += set[i];
        ret += SEPARATOR;
    }
    ret += set[set.size() - 1];
    return ret;
}