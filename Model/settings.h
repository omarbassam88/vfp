#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJsonObject;
class QFile;
class QDir;

typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrorPair;

class Settings : public QObject
{
  Q_OBJECT
public:
  explicit Settings(QObject* parent, QString filename);
  void ParseJsonData();

  QString GetFilename() const { return m_filename; };
  QString GetApplicationName() const { return m_applicationName; };
  QString GetAppShortName() const { return m_appShortName; };
  QString GetHostName() const { return m_hostName; };
  quint16 GetPortNumber() const { return m_portNumber; };
  int GetLongWaitMs() const { return m_longWaitMs;}
  int GetShortWaitMs() const { return m_shortWaitMs;}
  QStringListModel& GetCommands() const { return m_modelCommands; };

signals:
  void NotifyStatusMessage(QString message);

private:
  QString m_filename;
  QString m_applicationName;
  QString m_appShortName;
  QString m_hostName;
  quint16 m_portNumber;
  int m_longWaitMs;
  int m_shortWaitMs;
  QStringListModel& m_modelCommands;

  QString ReadJsonFile();
  QString ReadJsonFromInternalResource();
  void SendErrorMessage(const QString& msg);
  JsonObjErrorPair GetJsonObject(const QString& rawJson);
  void ShowJsonParseError(QJsonParseError jsonError);
  void SetupCommands(QJsonObject jsonObject);
  QDir OpenConfigDirectory();
  void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings);
};

#endif // SETTINGS_H
