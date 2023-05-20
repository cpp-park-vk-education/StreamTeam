#include "PostgreConnection.hpp"

PostgreConnection::PostgreConnection(std::string config_path)
{
    Config cfg;
    cfg.readFile(config_path.c_str());

    try
    {
        dbname = static_cast<std::string>(cfg.lookup("dbname"));
    }
    catch (...)
    {
        dbname = "";
        std::cerr << "No 'dbname' setting in configuration file." << std::endl;
    }

    try
    {
        user = static_cast<std::string>(cfg.lookup("user"));
    }
    catch (...)
    {
        user = "";
        std::cerr << "No 'user' setting in configuration file." << std::endl;
    }

    try
    {
        password = static_cast<std::string>(cfg.lookup("password"));
    }
    catch (...)
    {
        password = "postgres";
        std::cerr << "No 'password' setting in configuration file. 'password' is setted by default to 'postgres'." << std::endl;
    }

    try
    {
        host = static_cast<std::string>(cfg.lookup("host"));
    }
    catch (...)
    {
        host = "127.0.0.1";
        std::cerr << "No 'host' setting in configuration file. 'host' is setted by default to '127.0.0.1'." << std::endl;
    }

    try
    {
        port = static_cast<std::string>(cfg.lookup("port"));
    }
    catch (...)
    {
        port = "5432";
        std::cerr << "No 'port' setting in configuration file. 'port' is setted by default to '5432'." << std::endl;
    }
}

PostgreConnection::PostgreConnection(
    std::string dbname, std::string user, std::string password, std::string host, std::string hostaddr, std::string port)
    : dbname(dbname), user(user), password(password), host(host), hostaddr(hostaddr), port(port) {}

std::map<std::string, std::string> PostgreConnection::reformat() const
{
    std::map<std::string, std::string> result;
    result[STATUS_FIELD] = SUCCESS_STATUS;
    std::string connectionParams = "dbname=" + dbname + " ";
    connectionParams += "user=" + user + " ";

    if (dbname.empty() || user.empty())
    {
        result[STATUS_FIELD] = ERROR_STATUS;
        result[PARAMS_FIELD] = "";
        return result;
    }

    if (!password.empty())
    {
        connectionParams += "password=" + password + " ";
    }

    if (!host.empty())
    {
        connectionParams += "host=" + host + " ";
    }
    else if (!hostaddr.empty())
    {
        connectionParams += "hostaddr=" + hostaddr + " ";
    }

    if (!port.empty())
    {
        connectionParams += "port=" + port + " ";
    }

    result[PARAMS_FIELD] = connectionParams;

    return result;
}