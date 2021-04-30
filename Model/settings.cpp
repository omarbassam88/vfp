#include "settings.h"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStringListModel>
#include <QMessageBox>
#include <QJsonArray>
#include <QStandardPaths>
#include <utility>

static const int PW_CMD_INDEX = 5;
static auto RESOURCE_PREFIX = QStringLiteral(":/json");

Settings::Settings(QObject* parent, QString filename)
    : QObject(parent)
    , m_filename(filename)
    , m_modelCommands(*new QStringListModel(this))
{

}

void
Settings::ParseJsonData()
{
    QString raw_json = ReadJsonFile();
    if (raw_json.size() == 0)
        return;
    auto json_result = GetJsonObject(raw_json);
    auto json_error = json_result.second;
    if (json_error.error != QJsonParseError::NoError) {
        ShowJsonParseError(json_error);
    }
    auto json_obj = json_result.first;
    m_applicationName = json_obj["applicationName"].toString();
    m_appShortName = json_obj["appShortName"].toString();
    m_hostName = json_obj["hostName"].toString();
    m_portNumber = json_obj["port"].toInt();
    m_shortWaitMs = json_obj["tcpShortWaitMs"].toInt();
    m_longWaitMs = json_obj["tcpLongWaitMs"].toInt();
    SetupCommands(json_obj);

}




QString
Settings::ReadJsonFile()
{
    auto default_settings = ReadJsonFromInternalResource();
    QDir config_dir = OpenConfigDirectory();
    auto path = config_dir.filePath(m_filename);
    QFile std_file(path);
    if (std_file.exists()) {
        if (!std_file.open(QFile::ReadOnly | QFile::Text)) {
            SendErrorMessage("Could not Open " + path);
            return default_settings;
        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    }
    else {
        WriteDefaultsToStdConfigFile(std_file, default_settings);
        return default_settings;
    }

}

QDir
Settings::OpenConfigDirectory()
{
    QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if (!config_dir.exists()) {
        QDir dir;
        dir.mkpath(config_dir.path());
    }
    qDebug("%s", qPrintable(config_dir.canonicalPath()));
    return config_dir;
}

void
Settings::WriteDefaultsToStdConfigFile(QFile& stdConfigFile, const QString& settings)
{
    int length = settings.length();
    if (stdConfigFile.open(QFile::WriteOnly | QFile::Text)) {
        SendErrorMessage("Could not open file to write - " + stdConfigFile.fileName());
    }
    auto bytes_written = stdConfigFile.write(qPrintable(settings), length);
    if (bytes_written != length) {
        SendErrorMessage("Could not write the settings to - " + stdConfigFile.fileName());
        if (!stdConfigFile.remove()) {
            SendErrorMessage("Couldn't remove configuration file. Please Delete Manually " + stdConfigFile.fileName());
        }
    }
    stdConfigFile.close();
}

JsonObjErrorPair
Settings::GetJsonObject(const QString& rawJson)
{
    QJsonParseError json_parse_error;
    QJsonDocument json_doc =
            QJsonDocument::fromJson(rawJson.toUtf8(), &json_parse_error);

    QJsonObject json_obj = json_doc.object();
    return std::make_pair(json_obj, json_parse_error);
}



QString
Settings::ReadJsonFromInternalResource()
{
    QDir res_dir(RESOURCE_PREFIX);
    if (!res_dir.exists()) {
        SendErrorMessage("Internal resource path missing " +
                         res_dir.canonicalPath());
        return "";
    }
    auto path = res_dir.filePath(m_filename);
    QFile res_file(path);
    if (!res_file.open(QFile::ReadOnly | QFile::Text)) {
        SendErrorMessage("Could not open internal resource " + path);
        return "";
    }
    QString settings = res_file.readAll();
    return settings;
}

void
Settings::SendErrorMessage(const QString& msg)
{
    emit NotifyStatusMessage(msg);
}

void Settings::ShowJsonParseError(QJsonParseError jsonError)
{
    QString msg = tr("Error parsing Json settings file.\n");
    msg.append(jsonError.errorString());
    QMessageBox::critical(0,tr("VFP"), msg);
}

void Settings::SetupCommands(QJsonObject jsonObject)
{
    QJsonArray cmd_array = jsonObject["commands"].toArray();
    QStringList cmd_list;
    for (auto cmd: cmd_array ) {;
        cmd_list.append(cmd.toString());
    }
    m_modelCommands.setStringList(cmd_list);

    auto index = m_modelCommands.index(PW_CMD_INDEX);
    auto test_cmd = m_modelCommands.data(index);

    if (PW_CMD_INDEX < cmd_list.size()) {
        m_pwCommand = cmd_list[PW_CMD_INDEX];
    }
    else {
        emit NotifyStatusMessage("Error Getting Pulse Width Command");
    }
}
