#include "signinwindow.h"
#include "ui_signinwindow.h"
#include "user.hpp"
#include "session.hpp"

#include <QMessageBox>

using json = nlohmann::json_abi_v3_11_2::json;

SignInWindow::SignInWindow(QWidget *parent, MainWindow *main) :
    QDialog(parent),
    mainwind(main),
    ui(new Ui::SignInWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sign in");
}

SignInWindow::~SignInWindow()
{
    delete ui;
}

void SignInWindow::on_buttonBox_accepted()
{
    std::string name = ui->lineEditName->text().toStdString();
    std::string email = ui->lineEditEmail->text().toStdString();
    std::string password = ui->lineEditPassword->text().toStdString();

    json data = {
        {"method", "create"},
        {"data",
            {
                {"username", name},
                {"name", email},
                {"password", password}
            }
        }
    };

// Преобразуем json в строку
    std::string jsonString = data.dump();
    std::cout << "Request: " << jsonString << std::endl;
    auto session = Session::getInstance();
    session->Send(jsonString, [this, name, email, password](const json& answer) {
        if (answer["status"] == "ok") {
            // Здесь обработчик запроса

            std::shared_ptr<User> user(new User);
            user->SetName(email);
            user->SetPassword(password);
            user->SetId(answer["result"][0]["id"]);
            user->SetName(name);

            mainwind->Authenticate(user);
            accept();
            close();

        }
        else
            QMessageBox::warning(this, "Sign in error", "Coud not create Account");
    });
}


void SignInWindow::on_buttonBox_rejected()
{
    reject();
}

