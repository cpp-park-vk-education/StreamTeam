#include "UsersTable.hpp"

UsersTable::UsersTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json UsersTable::addUser(const json &info) const
{
    json request = info;
    json response = client->insert(request);
    return response;
}

json UsersTable::deleteUser(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json UsersTable::updateUser(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

bool UsersTable::checkUserByID(const size_t id) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {"users"}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    if (response["status"] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

bool UsersTable::checkUserByEmail(const std::string &email) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {"users"}},
                    {"WHERE", {"email='" + email + "'"}}};

    json response = client->select(request);

    if (response["status"] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

bool UsersTable::checkUserByUsername(const std::string &username) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {"users"}},
                    {"WHERE", {"username='" + username + "'"}}};

    json response = client->select(request);

    if (response["status"] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

json UsersTable::getUserInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {"users"}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}

json UsersTable::getUserIdByEmail(const std::string &email) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {"users"}},
                    {"WHERE", {"email='" + email + "'"}}};

    json response = client->select(request);
    return response;
}

json UsersTable::getUserIdByUsername(const std::string &username) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {"users"}},
                    {"WHERE", {"username='" + username + "'"}}};

    json response = client->select(request);
    return response;
}

json UsersTable::getUserPassword(const size_t id) const
{
    json request = {{"SELECT", {"password"}},
                    {"FROM", {"users"}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}