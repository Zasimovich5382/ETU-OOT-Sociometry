#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <QString>

class Exception {
public:
   Exception() {printError();}
   Exception(const QString& msg) : msg (msg) {printError();}
  ~Exception( ) {}
   QString getMessage( ) const {return(msg);}
   void printError() {std::cout << getMessage().toStdString() << std::endl;}

private:
   QString msg;
};


class FileNotOpenedException: public Exception {
private:
   std::string file_name;

public:
    FileNotOpenedException(QString file_name): Exception("File is not opened:" + file_name) {}
};

class WrongFileDataException: public Exception {
private:
   std::string file_name;

public:
    WrongFileDataException(QString file_name): Exception("File " + file_name + " has unparsable data") {}
};


#endif // EXCEPTIONS_H
