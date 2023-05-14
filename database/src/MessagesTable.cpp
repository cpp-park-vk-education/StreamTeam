#include "MessagesTable.hpp"

MessagesTable::MessagesTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json MessagesTable::addMessage(const json &info) const
{
    std::vector<std::string> columnsWithoutDefault(messagesTableColumns);
    columnsWithoutDefault.erase(columnsWithoutDefault.begin() + 3);

    json request = {{"INTO", messagesTableName},
                    {"columns", columnsWithoutDefault},
                    {"VALUES", {info["id_room"], info["id_user"], info["message"]}}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getMessageInfo(response["result"]);
    }

    return response;
}

json MessagesTable::deleteMessage(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json MessagesTable::updateMessage(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

json MessagesTable::getMessageInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {messagesTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}

json MessagesTable::getAuthorId(const size_t id) const
{
    json request = {{"SELECT", {"id_user"}},
                    {"FROM", {messagesTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};
    json response = client->select(request);

    return response;
}
